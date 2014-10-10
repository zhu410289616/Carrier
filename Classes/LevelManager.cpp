//
//  LevelManager.cpp
//  Map
//
//  Created by pig on 14-9-13.
//
//

#include "LevelManager.h"
#include "GameConstants.h"

static LevelManager *instance = NULL;

LevelManager *LevelManager::sharedInstance()
{
    if (!instance) {
        instance = new LevelManager();
        instance->init();
    }
    return instance;
}

LevelManager::LevelManager()
{
    mCurrentLevel = NULL;
}

LevelManager::~LevelManager()
{
//    CC_SAFE_RELEASE_NULL(mCurrentLevel);
}

bool LevelManager::init()
{
    //从缓存中读取历史关卡
    unsigned int defaultLevel = 1;
    defaultLevel = CCUserDefault::sharedUserDefault()->getIntegerForKey(kLevelNumberKey, defaultLevel);
    
    //
    mCurrentLevel = Level::create(defaultLevel);
//    mCurrentLevel->retain();
    
    return true;
}

void LevelManager::setCurrentLevel(unsigned int levelNumber)
{
    mCurrentLevel = Level::create(levelNumber);
//    mCurrentLevel->retain();
    
    CCUserDefault::sharedUserDefault()->setIntegerForKey(kLevelNumberKey, levelNumber);
}

Level *LevelManager::getCurrentLevel()
{
    return mCurrentLevel;
}

bool LevelManager::shouldGotoPrevLevel()
{
    return true;
}

bool LevelManager::shouldGotoNextLevel()
{
    return true;
}

Level *LevelManager::prevLevel()
{
    return mCurrentLevel;
}

Level *LevelManager::nextLevel()
{
    return mCurrentLevel;
}
