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

class ControlLayerDelegate {
    
public:
    virtual void didTaskFinished() = 0;
};

class ControlLayer : public cocos2d::CCLayer {
private:
    MapLayer *mMapLayer;
    Man *mMan;
    
    ControlLayerDelegate *mDelegate;
    
    CCPoint mBeginPoint;
    CCPoint mEndPoint;
    
public:
    virtual bool init();
    CREATE_FUNC(ControlLayer);
    
    void setMapLayer(MapLayer *mapLayer);
    void setMan(Man *man);
    void setDelegate(ControlLayerDelegate *delegate);
    
protected:
    //CCTouchDelegate
    void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
    void ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent);
    void ccTouchesCancelled(CCSet *pTouches, CCEvent *pEvent);
    
    void doMoveLogic(CCPoint beginPoint, CCPoint endPoint);
    MoveDirection directionWithTouchPorints(CCPoint beginPoint, CCPoint endPoint);
    CCPoint nextPositionWithDirection(MoveDirection direction, CCPoint currentPosition);
    MoveCheckCode shouldMoveWithDirection(MoveDirection direction);
    MoveCheckCode shouldMoveOfManWithPosition(CCPoint nextPosition);
    MoveCheckCode shouldMoveOfBoxWithPosition(CCPoint nextPosition);
    
    void taskFinished();
};

#endif /* defined(__Map__ControlLayer__) */
