//
//  MenuScene.h
//  Carrier
//
//  Created by pig on 14-10-9.
//
//

#ifndef __Carrier__MenuScene__
#define __Carrier__MenuScene__

#include "cocos2d.h"
#include "LevelLayer.h"

USING_NS_CC;

class MenuScene : public cocos2d::CCLayer, public LevelLayerDelegate {
private:
    LevelLayer *mLevelLayer;
    //todo setting
    
public:
    static cocos2d::CCScene *scene();
    
    virtual bool init();
    CREATE_FUNC(MenuScene);
    
    //LevelLayerDelegate
    virtual void didLevelSelected(Level *level);
    
    //setting callback
    void menuSettingCallback(CCObject *pSender);
};

#endif /* defined(__Carrier__MenuScene__) */
