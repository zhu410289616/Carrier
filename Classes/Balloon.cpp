//
//  Balloon.cpp
//  Carrier
//
//  Created by pig on 14-10-10.
//
//

#include "Balloon.h"

bool Balloon::init()
{
    if (!CCSprite::initWithFile("balloon@2x.png")) {
        return false;
    }
    return true;
}

void Balloon::setExistBox(bool isExistBox)
{
    mIsExistBox = isExistBox;
}

bool Balloon::isExistBox()
{
    return mIsExistBox;
}
