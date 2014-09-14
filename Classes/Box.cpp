//
//  Box.cpp
//  Map
//
//  Created by pig on 14-9-13.
//
//

#include "Box.h"

bool Box::init()
{
    if (!CCSprite::initWithFile("box.png")) {
        return false;
    }
    return true;
}

CCPoint Box::positionWithDirection(MoveDirection direction)
{
    int posx = this->getPositionX();
    int posy = this->getPositionY();
    
    switch (direction) {
        case MoveDirectionUp:
        {
            posy += kTileSizeHeight;
        }
            break;
        case MoveDirectionDown:
        {
            posy -= kTileSizeHeight;
        }
            break;
        case MoveDirectionLeft:
        {
            posx -= kTileSizeWidth;
        }
            break;
        case MoveDirectionRight:
        {
            posx += kTileSizeWidth;
        }
            break;
            
        default:
            break;
    }
    
    return ccp(posx, posy);
}

void Box::move(MoveDirection direction)
{
    CCLOG("Box::move: %d", direction);
    switch (direction) {
        case MoveDirectionUp:
        {
            this->setPosition(ccp(this->getPosition().x, this->getPosition().y + kTileSizeWidth));
        }
            break;
        case MoveDirectionDown:
        {
            this->setPosition(ccp(this->getPosition().x, this->getPosition().y - kTileSizeWidth));
        }
            break;
        case MoveDirectionLeft:
        {
            this->setPosition(ccp(this->getPosition().x - kTileSizeWidth, this->getPosition().y));
        }
            break;
        case MoveDirectionRight:
        {
            this->setPosition(ccp(this->getPosition().x + kTileSizeWidth, this->getPosition().y));
        }
            break;
            
        default:
            break;
    }
}
