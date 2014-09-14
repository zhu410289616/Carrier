//
//  GameConstants.h
//  Map
//
//  Created by pig on 14-9-13.
//
//

#ifndef Map_GameConstants_h
#define Map_GameConstants_h

#define kTileSizeWidth              60.0f
#define kTileSizeHeight             60.0f

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
    MoveCheckCodeMoveBox = 2,
    MoveCheckCodeMoveManAndBox = 3,
    MoveCheckCodeFailed = 4,
    MoveCheckCodeUnknow
} MoveCheckCode;

typedef enum {
    ElementTypeNone = 0,
    ElementTypeNormal = 1,
    
    ElementTypeGreenRoad,
    ElementTypeBox,
    ElementTypePoolUp,
    ElementTypePoolDown,
    ElementTypePoolLeft,
    ElementTypePoolRight,
    ElementTypegGreenTree,
    ElementTypeGreenShrub,
    ElementTypeSceneryTree,
    ElementTypeRedBarricade,
    ElementTypeBlueHouse,
    ElementTypeRedHouse,
    ElementTypeYellowHouse,
    ElementTypeRedWall,
    ElementTypeYellowFlower,
    ElementTypeBalloon,
    ElementTypeMan,
    
    ElementTypeUnknow
} ElementType;

#endif
