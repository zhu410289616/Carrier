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
    if (!CCSprite::initWithFile("boxman_down@2x.png")) {
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

void Man::setFaceDirection(MoveDirection faceDirection)
{
    std::string fileName = "boxman_down@2x.png";
    switch (faceDirection) {
        case MoveDirectionUp:
        {
            fileName = "boxman_up@2x.png";
        }
            break;
        case MoveDirectionDown:
        {
            fileName = "boxman_down@2x.png";
        }
            break;
        case MoveDirectionLeft:
        {
            fileName = "boxman_left@2x.png";
        }
            break;
        case MoveDirectionRight:
        {
            fileName = "boxman_right@2x.png";
        }
            break;
            
        default:
            break;
    }
    CCSprite *sprite = CCSprite::create(fileName.c_str());
    this->setTexture(sprite->getTexture());
    this->direction = faceDirection;
}

void Man::move(MoveDirection moveDirection)
{
    CCLOG("Man::move: %d", moveDirection);
    switch (moveDirection) {
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
    this->setFaceDirection(moveDirection);
}
