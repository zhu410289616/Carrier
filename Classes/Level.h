//
//  Level.h
//  Map
//
//  Created by pig on 14-9-13.
//
//

#ifndef __Map__Level__
#define __Map__Level__

#include "cocos2d.h"

USING_NS_CC;

class Level : public cocos2d::CCObject {
public:
    unsigned int mNumber;
    CCString *mMapName;
    CCString *mBackgroundMusic;
    CCString *mPushEffect;
    CCString *mFinishEffect;
    
public:
    virtual bool initWithLevelNumber(unsigned int levelNumber);
    virtual bool initWithDictionary(CCDictionary *dict);
    static Level *create(unsigned int levelNumber);
    static Level *create(CCDictionary *dict);
};

#endif /* defined(__Map__Level__) */
