//
//  LevelScene.cpp
//  Carrier
//
//  Created by pig on 14-10-9.
//
//

#include "LevelScene.h"

CCScene *LevelScene::scene()
{
    CCScene *scene = CCScene::create();
    
    LevelScene *levelScene = LevelScene::create();
    scene->addChild(levelScene);
    
    return scene;
}

bool LevelScene::init()
{
    if (!CCLayer::init()) {
        return false;
    }
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    
    CCSprite *sprite = CCSprite::create("HelloWorld.png");
    sprite->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    this->addChild(sprite, 0);
    
    return true;
}
