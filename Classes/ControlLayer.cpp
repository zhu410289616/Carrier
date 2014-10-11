//
//  ControlLayer.cpp
//  Map
//
//  Created by pig on 14-9-13.
//
//

#include "ControlLayer.h"
#include "LevelManager.h"

bool ControlLayer::init()
{
    if (!CCLayer::init()) {
        return false;
    }
    
    this->setTouchEnabled(true);
    
    return true;
}

void ControlLayer::setDelegate(ControlLayerDelegate *delegate)
{
    this->mDelegate = delegate;
}

#pragma mark CCTouchDelegate method

void ControlLayer::ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent)
{
    CCTouch *touch = (CCTouch *)pTouches->anyObject();
    CCPoint nodePoint = convertTouchToNodeSpace(touch);
    this->mBeginPoint = nodePoint;
}

void ControlLayer::ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent)
{
    CCTouch *touch = (CCTouch *)pTouches->anyObject();
    CCPoint nodePoint = convertTouchToNodeSpace(touch);
    this->mEndPoint = nodePoint;
    
    this->doMoveLogic(this->mBeginPoint, this->mEndPoint);
}

void ControlLayer::ccTouchesCancelled(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent)
{
    this->mBeginPoint = CCPointZero;
    this->mEndPoint = CCPointZero;
}

#pragma mark do move logic

void ControlLayer::doMoveLogic(cocos2d::CCPoint beginPoint, cocos2d::CCPoint endPoint)
{
    MoveDirection direction = this->directionWithTouchPorints(beginPoint, endPoint);
    if (MoveDirectionUnknow != direction) {
        //检测某个方向能否移动
        MoveCheckCode checkCode = this->shouldMoveWithDirection(direction);
        if (MoveCheckCodeNone == checkCode) {
            this->man->setFaceDirection(direction);
        } else if (MoveCheckCodeMoveMan == checkCode) {
            this->man->move(direction);
        } else if (MoveCheckCodeMoveManAndBox == checkCode) {
            //todo 移动box，man
            //移动箱子，并调整原有元素位置
            CCPoint nextPosition = this->nextPositionWithDirection(direction, man->getPosition());
            //box被移走，重置balloon的状态
            Balloon *balloon = mapLayer->balloonWithPosition(nextPosition);
            if (balloon) {
                balloon->setExistBox(false);
            }
            Box *box = mapLayer->boxWithPosition(nextPosition);
            box->move(direction);
            this->man->move(direction);
        } else if (MoveCheckCodeMoveBox2Balloon == checkCode) {
            //
            CCPoint nextPosition = this->nextPositionWithDirection(direction, man->getPosition());
            CCPoint nextNextPosition = this->nextPositionWithDirection(direction, nextPosition);
            //box被移走，重置balloon的状态
            Balloon *balloon = mapLayer->balloonWithPosition(nextPosition);
            if (balloon) {
                balloon->setExistBox(false);
            }
            balloon = mapLayer->balloonWithPosition(nextNextPosition);
            balloon->setExistBox(true);
            Box *box = mapLayer->boxWithPosition(nextPosition);
            box->move(direction);
            this->man->move(direction);
            //todo 使用action，移动完成后检测是否通关
            if (this->isTaskDone()) {
                this->taskFinished();
            }
        }
    }//if
}

MoveDirection ControlLayer::directionWithTouchPorints(cocos2d::CCPoint beginPoint, cocos2d::CCPoint endPoint)
{
    MoveDirection direction = MoveDirectionUnknow;
    if (!beginPoint.equals(endPoint)) {
        float offsetX = endPoint.x - beginPoint.x;
        float offsetY = endPoint.y - beginPoint.y;
        if (fabsf(offsetX) >= fabsf(offsetY)) {
            //以x移动为准
            if (offsetX > kTileSizeWidth) {
                direction = MoveDirectionRight;
            } else if (offsetX < -kTileSizeWidth) {
                direction = MoveDirectionLeft;
            }
        } else {
            if (offsetY > kTileSizeWidth) {
                direction = MoveDirectionUp;
            } else if (offsetY < -kTileSizeWidth) {
                direction = MoveDirectionDown;
            }
        }
    }
    CCLOG("directionWithTouchPorints direction: %d", direction);
    return direction;
}

CCPoint ControlLayer::nextPositionWithDirection(MoveDirection direction, cocos2d::CCPoint currentPosition)
{
    int posx = currentPosition.x;
    int posy = currentPosition.y;
    switch (direction) {
        case MoveDirectionUp:
        {
            posy += kTileSizeHeight;
        }
            break;
        case MoveDirectionDown:
        {
            posy -= kTileSizeHeight;
        }
            break;
        case MoveDirectionLeft:
        {
            posx -= kTileSizeWidth;
        }
            break;
        case MoveDirectionRight:
        {
            posx += kTileSizeWidth;
        }
            break;
            
        default:
            break;
    }
    return ccp(posx, posy);
}

MoveCheckCode ControlLayer::shouldMoveWithDirection(MoveDirection direction)
{
    MoveCheckCode checkCode = MoveCheckCodeNone;
    CCPoint nextPosition = this->nextPositionWithDirection(direction, man->getPosition());
    checkCode = this->shouldMoveOfManWithPosition(nextPosition);
    if (MoveCheckCodeMoveMan == checkCode) {
        //只移动man
    } else if (MoveCheckCodeCheckBox == checkCode) {
        //man的下一个位置是box，继续检测box后面的一个位置可否移动
        CCPoint nextNextPosition = this->nextPositionWithDirection(direction, nextPosition);
        checkCode = this->shouldMoveOfBoxWithPosition(nextNextPosition);
    }
    return checkCode;
}

/**
 *  检测下一个移动坐标位置
 *  1. 如果下一个是地面，则可以移动man
 *  2. 如果下一个是箱子，则继续检测箱子后面的一个位置
 *  3. 如果是其他元素，则不允许移动，只改变man的方向
 *
 *  @param nextPosition 下一个需要到达的坐标位置
 *
 *  @return 返回检测结果
 */
MoveCheckCode ControlLayer::shouldMoveOfManWithPosition(cocos2d::CCPoint nextPosition)
{
    MoveCheckCode checkCode = MoveCheckCodeNone;
    
    //1.先检测red wall碰撞
    int redWallTileId = mapLayer->tileIdOfRedWallWithPosition(nextPosition);
    CCLOG("shouldMoveOfManWithPosition nextPosition: (%f, %f), redWallTileId: %d", nextPosition.x, nextPosition.y, redWallTileId);
    
    if (redWallTileId > 0) {
        return MoveCheckCodeNone;
    }
    
    //2.检测box碰撞
    if (redWallTileId <= 0) {
        Box *checkBox = mapLayer->boxWithPosition(nextPosition);
        if (NULL == checkBox) {
            //todo MoveCheckCodeMoveMan
            checkCode = MoveCheckCodeMoveMan;
        } else {
            //todo MoveCheckCodeCheckBox
            checkCode = MoveCheckCodeCheckBox;
        }
    }
    
    CCLog("shouldMoveOfManWithPosition checkCode: %u", checkCode);
    return checkCode;
}

MoveCheckCode ControlLayer::shouldMoveOfBoxWithPosition(cocos2d::CCPoint nextPosition)
{
    MoveCheckCode checkCode = MoveCheckCodeNone;
    
    //1.先检测red wall碰撞
    int redWallTileId = mapLayer->tileIdOfRedWallWithPosition(nextPosition);
    CCLOG("shouldMoveOfBoxWithPosition nextPosition: (%f, %f), redWallTileId: %d", nextPosition.x, nextPosition.y, redWallTileId);
    
    if (redWallTileId > 0) {
        return MoveCheckCodeNone;
    }
    
    //2.检测box碰撞
    if (redWallTileId <= 0) {
        //todo MoveCheckCodeMoveManAndBox
        Box *checkBox = mapLayer->boxWithPosition(nextPosition);
        if (NULL == checkBox) {
            checkCode = MoveCheckCodeMoveManAndBox;
            //如果不是box，继续检测是否是balloon
            Balloon *checkBalloon = mapLayer->balloonWithPosition(nextPosition);
            if (NULL == checkBalloon) {
                //非泡泡
            } else {
                //移动box到balloon的位置
                checkCode = MoveCheckCodeMoveBox2Balloon;
            }
        }
    }
    
    CCLog("shouldMoveOfBoxWithPosition checkCode: %u", checkCode);
    return checkCode;
}

bool ControlLayer::isTaskDone()
{
    bool isFinished = true;
    
    CCObject *object;
    CCARRAY_FOREACH(mapLayer->balloons, object) {
        Balloon *balloonObject = (Balloon *)object;
        if (!balloonObject->isExistBox()) {
            isFinished = false;
            break;
        }
    }
    
    return isFinished;
}

void ControlLayer::taskFinished()
{
    CCLog("ControlLayer::taskFinished...");
    
    if (this->mDelegate) {
        this->mDelegate->didTaskFinished();
    }
}