//
//  MenuScene.cpp
//  Carrier
//
//  Created by pig on 14-10-9.
//
//

#include "MenuScene.h"

CCScene *MenuScene::scene()
{
    CCScene *scene = CCScene::create();
    
    MenuScene *menuScene = MenuScene::create();
    scene->addChild(menuScene);
    
    return scene;
}

bool MenuScene::init()
{
    if (!CCLayer::init()) {
        return false;
    }
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    
    mLevelLayer = LevelLayer::create();
    mLevelLayer->setPosition(origin);
    this->addChild(mLevelLayer);
    
    return true;
}