//
//  Balloon.h
//  Carrier
//
//  Created by pig on 14-10-10.
//
//

#ifndef __Carrier__Balloon__
#define __Carrier__Balloon__

#include "cocos2d.h"

USING_NS_CC;

class Balloon : public cocos2d::CCSprite {
private:
    bool mIsExistBox;
    
public:
    virtual bool init();
    CREATE_FUNC(Balloon);
    
    void setExistBox(bool isExistBox);
    bool isExistBox();
};

#endif /* defined(__Carrier__Balloon__) */
