//
//  Man.h
//  Map
//
//  Created by pig on 14-9-13.
//
//

#ifndef __Map__Man__
#define __Map__Man__

#include "cocos2d.h"
#include "GameConstants.h"

USING_NS_CC;

class Man : public cocos2d::CCSprite {
private:
    MoveDirection mDirection;
    
public:
    virtual bool init();
    CREATE_FUNC(Man);
    
    CCPoint positionWithDirection(MoveDirection direction);
    void setFaceDirection(MoveDirection faceDirection);
    void move(MoveDirection moveDirection);
};

#endif /* defined(__Map__Man__) */
