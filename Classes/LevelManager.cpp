//
//  LevelManager.cpp
//  Map
//
//  Created by pig on 14-9-13.
//
//

#include "LevelManager.h"

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
    //test
    unsigned int defaultLevel = 1;
    
    currentLevel = Level::create();
    currentLevel->number = defaultLevel;
    currentLevel->mapName = CCString::createWithFormat("map_%d.tmx", defaultLevel);
    
    return true;
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
