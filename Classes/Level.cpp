//
//  Level.cpp
//  Map
//
//  Created by pig on 14-9-13.
//
//

#include "Level.h"

Level *Level::create(cocos2d::CCDictionary *dict)
{
    Level *level = new Level();
    if (level->initWithDictionary(dict)) {
        level->autorelease();
        return level;
    }
    CC_SAFE_RELEASE(level);
    return NULL;
}

bool Level::init()
{
    return true;
}

bool Level::initWithDictionary(cocos2d::CCDictionary *dict)
{
    std::string key = "level";
    CCString *value = (CCString *)dict->objectForKey(key);
    number = value->uintValue();
    
    key = "map";
    value = (CCString *)dict->objectForKey(key);
    mapName = CCString::create(value->m_sString);
    
    key = "background_music";
    value = (CCString *)dict->objectForKey(key);
    backgroundMusic = CCString::create(value->m_sString);
    
    key = "push_effect";
    value = (CCString *)dict->objectForKey(key);
    pushEffect = CCString::create(value->m_sString);
    
    key = "finish_effect";
    value = (CCString *)dict->objectForKey(key);
    finishEffect = CCString::create(value->m_sString);
    
    return true;
}
