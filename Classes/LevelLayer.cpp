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
    
    mDataAdapter = FFTableViewAdapter::create();
//    mDataTableView = FFTableView::create(mDataAdapter, visibleSize);
//    this->addChild(mDataTableView);
    
    return true;
}
