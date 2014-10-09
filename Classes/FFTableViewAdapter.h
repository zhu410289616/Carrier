//
//  FFTableViewAdapter.h
//  Carrier
//
//  Created by pig on 14-10-9.
//
//

#ifndef __Carrier__FFTableViewAdapter__
#define __Carrier__FFTableViewAdapter__

#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

class FFTableViewAdapter : public cocos2d::CCObject, public cocos2d::extension::CCTableViewDataSource, public cocos2d::extension::CCTableViewDelegate {
private:
    CCArray *mDataSource;
    
public:
    FFTableViewAdapter();
    ~FFTableViewAdapter();
    
    virtual bool init();
    CREATE_FUNC(FFTableViewAdapter);
    
    //
    void setDataSource(CCArray *dataSource);
    
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

#endif /* defined(__Carrier__FFTableViewAdapter__) */
