//
//  MapLayer.h
//  Map
//
//  Created by pig on 14-9-13.
//
//

#ifndef __Map__MapLayer__
#define __Map__MapLayer__

#include "cocos2d.h"
#include "Level.h"
#include "Man.h"
#include "Box.h"
#include "GameConstants.h"

USING_NS_CC;

class MapLayer : public cocos2d::CCLayer {
private:
    CCTMXTiledMap *gameMap;
    CCTMXLayer *bgLayer;
    CCTMXLayer *redWallLayer;
    CCTMXLayer *boxLayer;
    CCTMXLayer *destLayer;
    
    CCTMXObjectGroup *objects;
    
protected:
    
public:
    virtual bool initWithLevel(Level *level);
    static MapLayer *create(Level *level);
    
    //
    void initBox();
    
    //触摸点坐标转化成地图上的坐标点
    CCPoint tileCoordinateWithPosition(CCPoint position);
    //将地图坐标转换成瓦片值
    int tileIdWithTileCoordinate(CCPoint tileCoordinate);
    //触摸点转化为瓦片值
    int tileIdWithPosition(CCPoint position);
    //将地图坐标点转换成触摸点坐标
    CCPoint positionWithTileCoordinate(CCPoint tileCoordinate);
};

#endif /* defined(__Map__MapLayer__) */
