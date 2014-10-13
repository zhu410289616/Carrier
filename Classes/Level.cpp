//
//  Level.cpp
//  Map
//
//  Created by pig on 14-9-13.
//
//

#include "Level.h"

Level *Level::create(unsigned int levelNumber)
{
    Level *level = new Level();
    if (level->initWithLevelNumber(levelNumber)) {
        level->autorelease();
        return level;
    }
    CC_SAFE_RELEASE(level);
    return NULL;
}

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

bool Level::initWithLevelNumber(unsigned int levelNumber)
{
    this->mNumber = levelNumber;
    this->mMapName = CCString::createWithFormat("map_%d.tmx", levelNumber);
    return true;
}

bool Level::initWithDictionary(cocos2d::CCDictionary *dict)
{
    std::string key = "level";
    CCString *value = (CCString *)dict->objectForKey(key);
    this->mNumber = value->uintValue();
    
    key = "map";
    value = (CCString *)dict->objectForKey(key);
    this->mMapName = CCString::create(value->m_sString);
    
    key = "background_music";
    value = (CCString *)dict->objectForKey(key);
    this->mBackgroundMusic = CCString::create(value->m_sString);
    
    key = "push_effect";
    value = (CCString *)dict->objectForKey(key);
    this->mPushEffect = CCString::create(value->m_sString);
    
    key = "finish_effect";
    value = (CCString *)dict->objectForKey(key);
    this->mFinishEffect = CCString::create(value->m_sString);
    
    return true;
}
