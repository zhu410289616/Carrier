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
        
        MoveCheckCode checkCode = this->shouldMoveManWithDirection(this->man, direction);
        checkCode = mapLayer->shouldMoveWithNextPosition(man->positionWithDirection(direction));
        
//        MoveCheckCode checkCode = this->shouldMoveManWithDirection(this->man, direction);
        if (MoveCheckCodeNone) {
            this->man->setFaceDirection(direction);
        } else if (MoveCheckCodeMoveMan == checkCode) {
//            this->man->stopAllActions();
            this->man->move(direction);
        } else if (MoveCheckCodeMoveManAndBox == checkCode) {
//            this->man->stopAllActions();
            this->man->move(direction);
            //todo move box
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

MoveCheckCode ControlLayer::shouldMoveManWithDirection(Man *man, MoveDirection direction)
{
    MoveCheckCode checkCode = MoveCheckCodeFailed;
    
    //todo
    CCPoint nextPosition = man->positionWithDirection(direction);
    CCLOG("nextPosition.x: %f, nextPosition.y: %f", nextPosition.x, nextPosition.y);
    int tileId = mapLayer->tileIdWithPosition(nextPosition);
    CCLOG("man->getPositionX(): %f, man->getPositionY(): %f, tileId: %d", man->getPositionX(), man->getPositionY(), tileId);
    switch (tileId) {
        case 3:
        {
            return MoveCheckCodeNone;
        }
            break;
        case 11:
        {
            return MoveCheckCodeMoveBox;
        }
            break;
            
        default:
            break;
    }
    
    checkCode = MoveCheckCodeMoveMan;
    
    return checkCode;
}

MoveCheckCode ControlLayer::shouldMoveBoxWithDirection(Box *box, MoveDirection direction)
{
    MoveCheckCode checkCode = MoveCheckCodeFailed;
    
    //todo
    CCPoint nextPosition = box->positionWithDirection(direction);
    CCLOG("nextPosition.x: %f, nextPosition.y: %f", nextPosition.x, nextPosition.y);
    int tileId = mapLayer->tileIdWithPosition(nextPosition);
    CCLOG("man->getPositionX(): %f, man->getPositionY(): %f, tileId: %d", man->getPositionX(), man->getPositionY(), tileId);
    
    switch (tileId) {
        case 0:
        {
            return MoveCheckCodeMoveBox;
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