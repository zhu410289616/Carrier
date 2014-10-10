//
//  SettingScene.cpp
//  Carrier
//
//  Created by pig on 14-10-10.
//
//

#include "SettingScene.h"
#include "MenuScene.h"

CCScene *SettingScene::scene()
{
    CCScene *scene = CCScene::create();
    
    SettingScene *settingScene = SettingScene::create();
    scene->addChild(settingScene);
    
    return scene;
}

bool SettingScene::init()
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
    
    //menu
    CCMenuItemImage *pBackItem = CCMenuItemImage::create("CloseNormal.png", "CloseSelected.png", this, menu_selector(SettingScene::menuBackCallback));
    pBackItem->setPosition(ccp(origin.x + visibleSize.width - pBackItem->getContentSize().width/2, origin.y + pBackItem->getContentSize().height/2));
    
    CCMenu *pMenu = CCMenu::create(pBackItem, NULL);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu, 1);
    
    return true;
}

void SettingScene::menuBackCallback(cocos2d::CCObject *pSender)
{
    CCLog("SettingScene::menuBackCallback...");
    CCDirector::sharedDirector()->replaceScene(MenuScene::scene());
}
