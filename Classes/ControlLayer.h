//
//  ControlLayer.h
//  Map
//
//  Created by pig on 14-9-13.
//
//

#ifndef __Map__ControlLayer__
#define __Map__ControlLayer__

#include "cocos2d.h"
#include "MapLayer.h"
#include "Man.h"
#include "Box.h"

USING_NS_CC;

class ControlLayer : public cocos2d::CCLayer {
private:
    CCPoint beginPoint;
    CCPoint endPoint;
    
protected:
    void reloadMap();
    
    //CCTouchDelegate
    void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
    void ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent);
    void ccTouchesCancelled(CCSet *pTouches, CCEvent *pEvent);
    
    void doMoveLogic(CCPoint beginPoint, CCPoint endPoint);
    MoveDirection directionWithTouchPorints(CCPoint beginPoint, CCPoint endPoint);
    MoveCheckCode shouldMoveManWithDirection(Man *man, MoveDirection direction);
    MoveCheckCode shouldMoveBoxWithDirection(Box *box, MoveDirection direction);
    void taskFinished();
    
public:
    MapLayer *mapLayer;
    Man *man;
    
public:
    virtual bool init();
    CREATE_FUNC(ControlLayer);
};

#endif /* defined(__Map__ControlLayer__) */
