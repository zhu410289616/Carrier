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
    
    dataTableView = CCTableView::create(this, visibleSize);
    dataTableView->setDirection(kCCScrollViewDirectionHorizontal);
    dataTableView->setPosition(ccp(0, visibleSize.height / 2 - 50));
    dataTableView->setDelegate(this);
    this->addChild(dataTableView);
    
    dataTableView->reloadData();
    
    //添加一个半透明的灰显层
    CCLayerColor *backLayerCorlor = CCLayerColor::create(ccc4(25, 25, 25, 125));
//    this->addChild(backLayerCorlor);
    
    return true;
}

#pragma mark CCTableViewDelegate method

void LevelScene::tableCellTouched(cocos2d::extension::CCTableView *table, cocos2d::extension::CCTableViewCell *cell)
{
    CCLOG("cell touched at index: %i", cell->getIdx());
}

#pragma mark CCTableViewDataSource method

CCSize LevelScene::tableCellSizeForIndex(cocos2d::extension::CCTableView *table, unsigned int idx)
{
    return CCSizeMake(120, 120);
}

CCTableViewCell *LevelScene::tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx)
{
    CCString *string = CCString::createWithFormat("%d", idx);
    CCTableViewCell *cell = table->dequeueCell();
    if (!cell) {
        cell = new CCTableViewCell();
        cell->autorelease();
        
        CCSprite *sprite = CCSprite::create("HelloWorld.png");
        sprite->setScale(0.2f);
        sprite->setPosition(ccp(60, 60));
        sprite->setTag(123);
        cell->addChild(sprite);
        
        CCLabelTTF *label = CCLabelTTF::create(string->getCString(), "Helvetica", 20.0f);
        label->setPosition(ccp(60, 10));
        label->setTag(456);
        cell->addChild(label);
    } else {
        CCLabelTTF *label = (CCLabelTTF *)cell->getChildByTag(456);
        label->setString(string->getCString());
    }
    return cell;
}

unsigned int LevelScene::numberOfCellsInTableView(cocos2d::extension::CCTableView *table)
{
    return 20;
}
