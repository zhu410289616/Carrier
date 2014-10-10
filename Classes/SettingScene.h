//
//  SettingScene.h
//  Carrier
//
//  Created by pig on 14-10-10.
//
//

#ifndef __Carrier__SettingScene__
#define __Carrier__SettingScene__

#include "cocos2d.h"

USING_NS_CC;

class SettingScene : public cocos2d::CCLayer {
private:
    
public:
    static cocos2d::CCScene *scene();
    
    virtual bool init();
    CREATE_FUNC(SettingScene);
    
    //back callback
    void menuBackCallback(CCObject *pSender);
};

#endif /* defined(__Carrier__SettingScene__) */
