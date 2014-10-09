//
//  FFTableView.h
//  Carrier
//
//  Created by pig on 14-10-9.
//
//

#ifndef __Carrier__FFTableView__
#define __Carrier__FFTableView__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "FFTableViewAdapter.h"

USING_NS_CC;
USING_NS_CC_EXT;

class FFTableView : public cocos2d::CCLayer {
public:
    CCTableView *mTableView;
    
public:
    virtual bool initWithTableViewAdapter(FFTableViewAdapter *adapter, CCSize size);
    static FFTableView *create(FFTableViewAdapter *adapter, CCSize size);
    
    void setTableViewAdapter(FFTableViewAdapter *adapter);
    void refreshTableView();
};

#endif /* defined(__Carrier__FFTableView__) */
