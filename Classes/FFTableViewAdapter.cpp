//
//  FFTableViewAdapter.cpp
//  Carrier
//
//  Created by pig on 14-10-9.
//
//

#include "FFTableViewAdapter.h"
#include "FFTableViewCell.h"

FFTableViewAdapter::FFTableViewAdapter()
{
    mDataSource = CCArray::create();
    mDataSource->retain();
}

FFTableViewAdapter::~FFTableViewAdapter()
{
    if (mDataSource) {
        mDataSource->removeAllObjects();
        CC_SAFE_RELEASE_NULL(mDataSource);
    }
}

bool FFTableViewAdapter::init()
{
    return true;
}

void FFTableViewAdapter::setDataSource(CCArray *dataSource)
{
    mDataSource->removeAllObjects();
    mDataSource->addObjectsFromArray(dataSource);
}

#pragma mark CCTableViewDelegate method

void FFTableViewAdapter::tableCellTouched(cocos2d::extension::CCTableView *table, cocos2d::extension::CCTableViewCell *cell)
{
    CCLOG("cell touched at index: %i", cell->getIdx());
}

#pragma mark CCTableViewDataSource method

CCSize FFTableViewAdapter::tableCellSizeForIndex(cocos2d::extension::CCTableView *table, unsigned int idx)
{
    return CCSizeMake(120, 120);
}

CCTableViewCell *FFTableViewAdapter::tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx)
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

unsigned int FFTableViewAdapter::numberOfCellsInTableView(cocos2d::extension::CCTableView *table)
{
    return 20;
}
