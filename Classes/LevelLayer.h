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
#include "FFTableViewAdapter.h"
#include "FFTableView.h"

USING_NS_CC;

class LevelLayer : public cocos2d::CCLayer {
private:
    FFTableViewAdapter *mDataAdapter;
    FFTableView *mDataTableView;
    
public:
    virtual bool init();
    CREATE_FUNC(LevelLayer);
};

#endif /* defined(__Carrier__LevelLayer__) */
