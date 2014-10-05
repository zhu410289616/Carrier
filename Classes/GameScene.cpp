//
//  GameScene.cpp
//  Carrier
//
//  Created by pig on 14-9-13.
//
//

#include "GameScene.h"
#include "LevelManager.h"

CCScene *GameScene::scene()
{
    CCScene *scene = CCScene::create();
    
    GameScene *gameLayer = GameScene::create();
    scene->addChild(gameLayer);
    
    return scene;
}

bool GameScene::init()
{
    if (!CCLayer::init()) {
        return false;
    }
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    
    //提高效率
//    CCSpriteFrameCache *frameCache = CCSpriteFrameCache::sharedSpriteFrameCache();
//    frameCache->addSpriteFramesWithFile("");
    
    CCSprite *sprite = CCSprite::create("HelloWorld.png");
    sprite->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    this->addChild(sprite, 0);
    
    //关卡
    Level *currentLevel = LevelManager::sharedInstance()->currentLevel;
    CCLOG("currentLevel->mapName: %s", currentLevel->mapName->m_sString.c_str());
    
    //根据关卡初始化地图
    MapLayer *mapLayer = MapLayer::create(currentLevel);
    mapLayer->setPosition(0, 0);
    this->addChild(mapLayer);
    
    //初始化搬运工
    Man *man = Man::create();//todo
    CCPoint point = mapLayer->positionWithTileCoordinate(ccp(5, 7));
    man->setPosition(ccp(point.x + 2, point.y + 2));
    man->setAnchorPoint(ccp(0, 0));
    mapLayer->addChild(man, 1);
    
    //控制层
    controlLayer = ControlLayer::create();
    controlLayer->setPosition(0, 0);
    controlLayer->mapLayer = mapLayer;
    controlLayer->man = man;
    this->addChild(controlLayer);
    
    return true;
}
