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
#include "Balloon.h"

USING_NS_CC;

class MapLayer : public cocos2d::CCLayer {
private:
    CCTMXTiledMap *gameMap;
    CCTMXLayer *bgLayer;
    CCTMXLayer *redWallLayer;
    CCTMXLayer *boxLayer;
    CCTMXLayer *destLayer;
    
    CCTMXObjectGroup *objects;
    
    //
    CCArray *mBoxes;
    CCArray *mBalloons;
    
protected:
    
public:
    virtual bool initWithLevel(Level *level);
    void initBalloon();
    void initBox();
    static MapLayer *create(Level *level);
    
    MapLayer();
    ~MapLayer();
    
    //触摸点坐标转化成地图上的坐标点(如果地图内，则为大于0的坐标。否则为（-1, -1）)
    CCPoint tileCoordinateWithPosition(CCPoint position);
    //将地图坐标点转换成触摸点坐标
    CCPoint positionWithTileCoordinate(CCPoint tileCoordinate);
    
    //将地图坐标转换成瓦片值
    int tileIdWithTileCoordinate(CCPoint tileCoordinate);
    //触摸点转化为瓦片值
    int tileIdWithPosition(CCPoint position);
    //触摸点转化为red wall layer瓦片值
    int tileIdOfRedWallWithPosition(CCPoint position);
    
    //获取某个触摸点的box,如果不存在则返回null
    Box *boxWithPosition(CCPoint position);
    //获取某个触摸点的balloon,用于更新是否已经有box存在
    Balloon *balloonWithPosition(CCPoint position);
    
    bool isTaskDoneStatus();
};

#endif /* defined(__Map__MapLayer__) */
