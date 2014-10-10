//
//  GameScene.h
//  Carrier
//
//  Created by pig on 14-9-13.
//
//

#ifndef __Carrier__GameScene__
#define __Carrier__GameScene__

#include "cocos2d.h"
#include "ControlLayer.h"

class GameScene : public cocos2d::CCLayer {
private:
    MapLayer *mMapLayer;
    ControlLayer *mControlLayer;
    //todo quit
    
public:
//    static cocos2d::CCScene *scene();
    static cocos2d::CCScene *scene(Level *pLevel);
    
    GameScene();
    ~GameScene();
    
    virtual bool init();
    virtual bool initWithLevel(Level *pLevel);
    CREATE_FUNC(GameScene);
    static GameScene *create(Level *pLevel);
    
    //back callback
    void menuBackCallback(CCObject *pSender);
};

#endif /* defined(__Carrier__GameScene__) */
