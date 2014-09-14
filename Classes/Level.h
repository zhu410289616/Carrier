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
private:
    
public:
    unsigned int number;
    CCString *mapName;
    CCString *backgroundMusic;
    CCString *pushEffect;
    CCString *finishEffect;
    
public:
    virtual bool init();
    virtual bool initWithDictionary(CCDictionary *dict);
    CREATE_FUNC(Level);
    static Level *create(CCDictionary *dict);
};

#endif /* defined(__Map__Level__) */
