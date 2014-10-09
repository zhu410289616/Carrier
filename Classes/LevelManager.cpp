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

bool LevelManager::init()
{
    //从缓存中读取历史关卡
    unsigned int defaultLevel = 1;
    defaultLevel = CCUserDefault::sharedUserDefault()->getIntegerForKey(kLevelNumberKey, defaultLevel);
    
    //
    currentLevel = Level::create(defaultLevel);
    
    return true;
}

void LevelManager::setCurrentLevel(unsigned int levelNumber)
{
    currentLevel = Level::create(levelNumber);
    currentLevel->mapName = CCString::createWithFormat("map_%d.tmx", levelNumber);
    
    CCUserDefault::sharedUserDefault()->setIntegerForKey(kLevelNumberKey, levelNumber);
}

Level *LevelManager::getCurrentLevel()
{
    return currentLevel;
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
    return currentLevel;
}

Level *LevelManager::nextLevel()
{
    return currentLevel;
}
