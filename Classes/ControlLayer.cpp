//
//  ControlLayer.cpp
//  Map
//
//  Created by pig on 14-9-13.
//
//

#include "ControlLayer.h"

bool ControlLayer::init()
{
    if (!CCLayer::init()) {
        return false;
    }
    
    this->setTouchEnabled(true);
    
    return true;
}

#pragma mark CCTouchDelegate method

void ControlLayer::ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent)
{
    CCTouch *touch = (CCTouch *)pTouches->anyObject();
    CCPoint nodePoint = convertTouchToNodeSpace(touch);
    this->beginPoint = nodePoint;
}

void ControlLayer::ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent)
{
    CCTouch *touch = (CCTouch *)pTouches->anyObject();
    CCPoint nodePoint = convertTouchToNodeSpace(touch);
    this->endPoint = nodePoint;
    
    this->doMoveLogic(this->beginPoint, this->endPoint);
}

void ControlLayer::ccTouchesCancelled(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent)
{
    this->beginPoint = CCPointZero;
    this->endPoint = CCPointZero;
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
            //todo
            //移动箱子，并调整原有元素位置
            this->man->move(direction);
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
    int tileId = mapLayer->tileIdWithPosition(nextPosition);
    CCLOG("nextPosition.x: %f, nextPosition.y: %f, tileId: %d", nextPosition.x, nextPosition.y, tileId);
    switch (tileId) {
        case ElementTypeNone:
        case ElementTypeGreenRoad:
        {
            return MoveCheckCodeMoveMan;
        }
            break;
        case ElementTypeBox:
        {
            return MoveCheckCodeCheckBox;
        }
            break;
            
        default:
            break;
    }
    return checkCode;
}

MoveCheckCode ControlLayer::shouldMoveOfBoxWithPosition(cocos2d::CCPoint nextPosition)
{
    MoveCheckCode checkCode = MoveCheckCodeNone;
    int tileId = mapLayer->tileIdWithPosition(nextPosition);
    CCLOG("nextPosition.x: %f, nextPosition.y: %f, tileId: %d", nextPosition.x, nextPosition.y, tileId);
    switch (tileId) {
        case ElementTypeNone:
        case ElementTypeGreenRoad:
        {
            return MoveCheckCodeMoveManAndBox;
        }
            break;
            
        default:
            break;
    }
    return checkCode;
}

void ControlLayer::taskFinished()
{
    /**
     *  通关，检测下一个关卡，并刷新地图
     */
//    Level *nextLevel = LevelManager::create();
}