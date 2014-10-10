//
//  LevelLayer.h
//  Carrier
//
//  Created by pig on 14-10-9.
//
//

#ifndef __Carrier__LevelLayer__
#define __Carrier__LevelLayer__

#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

class LevelLayer : public cocos2d::CCLayer, public cocos2d::extension::CCTableViewDataSource, public cocos2d::extension::CCTableViewDelegate {
private:
    CCTableView *mDataTableView;
    
public:
    virtual bool init();
    CREATE_FUNC(LevelLayer);
    
    //暂时没有用，因为继承了抽象类必须重写
    virtual void scrollViewDidScroll(cocos2d::extension::CCScrollView *scrollView){}
    virtual void scrollViewDidZoom(cocos2d::extension::CCScrollView *scrollView){}
    //CCTableViewDelegate
    virtual void tableCellTouched(CCTableView* table, CCTableViewCell* cell);
    //CCTableViewDataSource
    virtual CCSize tableCellSizeForIndex(CCTableView *table, unsigned int idx);
    virtual CCTableViewCell* tableCellAtIndex(CCTableView *table, unsigned int idx);
    virtual unsigned int numberOfCellsInTableView(CCTableView *table);
};

#endif /* defined(__Carrier__LevelLayer__) */
