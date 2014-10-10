//
//  GameScene.cpp
//  Carrier
//
//  Created by pig on 14-9-13.
//
//

#include "GameScene.h"
#include "LevelManager.h"
#include "MenuScene.h"

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
    CCLOG("currentLevel->mapName: %s", currentLevel->mapName->getCString());
    
    //根据关卡初始化地图
    MapLayer *mapLayer = MapLayer::create(currentLevel);
    mapLayer->setPosition(origin.x, origin.y / 2);//宽度固定y坐标调整
    this->addChild(mapLayer);
    
    //初始化搬运工
    Man *man = Man::create();//todo
    man->setScale(0.6);
    CCPoint point = mapLayer->positionWithTileCoordinate(ccp(5, 7));
    man->setPosition(ccp(point.x + 2, point.y + 2));
    man->setAnchorPoint(ccp(0, 0));
    mapLayer->addChild(man, 9);
    
    //控制层
    controlLayer = ControlLayer::create();
    controlLayer->setPosition(origin.x, origin.y);
    controlLayer->mapLayer = mapLayer;
    controlLayer->man = man;
    this->addChild(controlLayer);
    
    //menu
    CCMenuItemImage *pBackItem = CCMenuItemImage::create("CloseNormal.png", "CloseSelected.png", this, menu_selector(GameScene::menuBackCallback));
    pBackItem->setPosition(ccp(origin.x + visibleSize.width - pBackItem->getContentSize().width/2, origin.y + pBackItem->getContentSize().height/2));
    
    CCMenu *pMenu = CCMenu::create(pBackItem, NULL);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu, 1);
    
    return true;
}

void GameScene::menuBackCallback(cocos2d::CCObject *pSender)
{
    CCLog("SettingScene::menuBackCallback...");
//    CCDirector::sharedDirector()->replaceScene(MenuScene::scene());
}
