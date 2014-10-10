//
//  LevelLayer.cpp
//  Carrier
//
//  Created by pig on 14-10-9.
//
//

#include "LevelLayer.h"

bool LevelLayer::init()
{
    if (!CCLayer::init()) {
        return false;
    }
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    
    mDataTableView = CCTableView::create(this, visibleSize);
    mDataTableView->setDirection(kCCScrollViewDirectionHorizontal);
    mDataTableView->setPosition(ccp(0, visibleSize.height / 2 - 50));
    mDataTableView->setDelegate(this);
    this->addChild(mDataTableView);
    
    mDataTableView->reloadData();
    
    return true;
}

#pragma mark CCTableViewDelegate method

void LevelLayer::tableCellTouched(cocos2d::extension::CCTableView *table, cocos2d::extension::CCTableViewCell *cell)
{
    CCLOG("cell touched at index: %i", cell->getIdx());
}

#pragma mark CCTableViewDataSource method

CCSize LevelLayer::tableCellSizeForIndex(cocos2d::extension::CCTableView *table, unsigned int idx)
{
    return CCSizeMake(120, 120);
}

CCTableViewCell *LevelLayer::tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx)
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

unsigned int LevelLayer::numberOfCellsInTableView(cocos2d::extension::CCTableView *table)
{
    return 20;
}
