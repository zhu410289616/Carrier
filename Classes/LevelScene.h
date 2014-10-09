//
//  LevelScene.h
//  Carrier
//
//  Created by pig on 14-10-9.
//
//

#ifndef __Carrier__LevelScene__
#define __Carrier__LevelScene__

#include "cocos2d.h"

USING_NS_CC;

class LevelScene : public cocos2d::CCLayer {
private:
    
public:
    virtual bool init();
    CREATE_FUNC(LevelScene);
    
    static cocos2d::CCScene *scene();
};

#endif /* defined(__Carrier__LevelScene__) */
