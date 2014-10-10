//
//  MenuScene.cpp
//  Carrier
//
//  Created by pig on 14-10-9.
//
//

#include "MenuScene.h"
#include "GameScene.h"
#include "SettingScene.h"

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
    
    CCSprite *pBackground = CCSprite::create("background@2x.png");
    pBackground->setRotation(90);
    pBackground->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    this->addChild(pBackground);
    
    //添加一个半透明的灰显层
    CCLayerColor *backLayerCorlor = CCLayerColor::create(ccc4(25, 25, 25, 125));
    this->addChild(backLayerCorlor);
    
    mLevelLayer = LevelLayer::create();
    mLevelLayer->setPosition(origin);
    mLevelLayer->setDelegate(this);
    this->addChild(mLevelLayer);
    
    //menu
    CCMenuItemImage *pSettingItem = CCMenuItemImage::create("CloseNormal.png", "CloseSelected.png", this, menu_selector(MenuScene::menuSettingCallback));
    pSettingItem->setPosition(ccp(origin.x + visibleSize.width - pSettingItem->getContentSize().width/2, origin.y + pSettingItem->getContentSize().height/2));
    
    CCMenu *pMenu = CCMenu::create(pSettingItem, NULL);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu, 1);
    
    return true;
}

//LevelLayerDelegate
void MenuScene::didLevelSelected(Level *level)
{
    CCLog("MenuScene::didLevelSelected: %d", level->number);
    
    CCDirector::sharedDirector()->replaceScene(GameScene::scene(level));
//    CCDirector::sharedDirector()->pushScene(GameScene::scene());
}

void MenuScene::menuSettingCallback(cocos2d::CCObject *pSender)
{
    CCLog("MenuScene::menuSettingCallback...");
    
    CCDirector::sharedDirector()->replaceScene(SettingScene::scene());
    CCDirector::sharedDirector()->pushScene(SettingScene::scene());
}
