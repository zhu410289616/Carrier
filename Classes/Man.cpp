//
//  Man.cpp
//  Map
//
//  Created by pig on 14-9-13.
//
//

#include "Man.h"

bool Man::init()
{
    if (!CCSprite::initWithFile("balloon@2x.png")) {
        return false;
    }
    
//    this->set
    
    return true;
}

CCPoint Man::positionWithDirection(MoveDirection direction)
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

void Man::setFaceDirection(MoveDirection direction)
{
    CCLOG("Man::setFaceDirection: %d", direction);
    switch (direction) {
        case MoveDirectionUp:
        {
            CCLOG("");
        }
            break;
        case MoveDirectionDown:
        {}
            break;
        case MoveDirectionLeft:
        {}
            break;
        case MoveDirectionRight:
        {}
            break;
            
        default:
            break;
    }
}

void Man::move(MoveDirection direction)
{
    CCLOG("Man::move: %d", direction);
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
