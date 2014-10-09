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
    ControlLayer *controlLayer;
    //todo quit
    
public:
    virtual bool init();
    CREATE_FUNC(GameScene);
    
    static cocos2d::CCScene *scene();
};

#endif /* defined(__Carrier__GameScene__) */
