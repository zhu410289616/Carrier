//
//  Box.h
//  Map
//
//  Created by pig on 14-9-13.
//
//

#ifndef __Map__Box__
#define __Map__Box__

#include "cocos2d.h"
#include "GameConstants.h"

USING_NS_CC;

class Box : public cocos2d::CCSprite {
private:
    
public:
    virtual bool init();
    CREATE_FUNC(Box);
    
    CCPoint positionWithDirection(MoveDirection direction);
    void move(MoveDirection direction);
};

#endif /* defined(__Map__Box__) */
