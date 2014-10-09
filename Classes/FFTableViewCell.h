//
//  FFTableViewCell.h
//  Carrier
//
//  Created by pig on 14-10-9.
//
//

#ifndef __Carrier__FFTableViewCell__
#define __Carrier__FFTableViewCell__

#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

class FFTableViewCell : public cocos2d::extension::CCTableViewCell {
protected:
    
public:
    virtual bool init();
    CREATE_FUNC(FFTableViewCell);
};

#endif /* defined(__Carrier__FFTableViewCell__) */
