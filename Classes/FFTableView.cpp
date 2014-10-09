//
//  FFTableView.cpp
//  Carrier
//
//  Created by pig on 14-10-9.
//
//

#include "FFTableView.h"

FFTableView *FFTableView::create(FFTableViewAdapter *adapter, cocos2d::CCSize size)
{
    FFTableView *tableView = new FFTableView();
    if (tableView->initWithTableViewAdapter(adapter, size)) {
        tableView->autorelease();
        return tableView;
    }
    CC_SAFE_RELEASE(tableView);
    return NULL;
}

bool FFTableView::initWithTableViewAdapter(FFTableViewAdapter *adapter, cocos2d::CCSize size)
{
    if (!CCLayer::init()) {
        return false;
    }
    
    mTableView = CCTableView::create(adapter, size);
    mTableView->setPosition(CCPointZero);
    mTableView->setDirection(kCCScrollViewDirectionHorizontal);
    mTableView->setDelegate(adapter);
    this->addChild(mTableView);
    
    mTableView->reloadData();
    
    return true;
}

void FFTableView::setTableViewAdapter(FFTableViewAdapter *adapter)
{
    mTableView->setDataSource(adapter);
    mTableView->setDelegate(adapter);
}

void FFTableView::refreshTableView()
{
    mTableView->reloadData();
}
