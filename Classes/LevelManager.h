//
//  LevelManager.h
//  Map
//
//  Created by pig on 14-9-13.
//
//

#ifndef __Map__LevelManager__
#define __Map__LevelManager__

#include "cocos2d.h"
#include "Level.h"

class LevelManager : public cocos2d::CCObject {
private:
    Level *mCurrentLevel;
    
public:
    static LevelManager *sharedInstance();
    
    LevelManager();
    ~LevelManager();
    
    virtual bool init();
    CREATE_FUNC(LevelManager);
    
    void setCurrentLevel(unsigned int levelNumber);
    Level *getCurrentLevel();
    
    bool shouldGotoPrevLevel();
    bool shouldGotoNextLevel();
    Level *prevLevel();
    Level *nextLevel();
};

#endif /* defined(__Map__LevelManager__) */
