//
//  GameConstants.h
//  Map
//
//  Created by pig on 14-9-13.
//
//

#ifndef Map_GameConstants_h
#define Map_GameConstants_h

//tile map网格
#define kTileSizeWidth              60.0f
#define kTileSizeHeight             60.0f

//
#define kLevelNumberKey             "kLevelNumberKey"

typedef enum {
    MoveDirectionUp = 0,
    MoveDirectionDown = 1,
    MoveDirectionLeft = 2,
    MoveDirectionRight = 3,
    MoveDirectionUnknow
} MoveDirection;

typedef enum {
    MoveCheckCodeNone = 0,
    MoveCheckCodeMoveMan = 1,
    MoveCheckCodeCheckBox = 2,
    MoveCheckCodeMoveManAndBox = 3,
    MoveCheckCodeMoveBox2Balloon = 4,
    MoveCheckCodeUnknow
} MoveCheckCode;

typedef enum {
    ElementTypeNone = 0,
    ElementTypeNormal = 1,
    
    ElementTypeGreenRoad = 2,
    ElementTypeBox = 3,
    ElementTypePoolUp = 4,
    ElementTypePoolDown = 5,
    ElementTypePoolLeft = 6,
    ElementTypePoolRight = 7,
    ElementTypegGreenTree = 8,
    ElementTypeGreenShrub = 9,
    ElementTypeSceneryTree = 10,
    ElementTypeRedBarricade = 11,
    ElementTypeBlueHouse = 12,
    ElementTypeRedHouse = 13,
    ElementTypeYellowHouse = 14,
    ElementTypeRedWall = 15,
    ElementTypeYellowFlower = 16,
    ElementTypeBalloon = 17,
    ElementTypeMan = 18,
    
    ElementTypeUnknow = 999
} ElementType;

#endif
