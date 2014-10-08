//
//  MapLayer.cpp
//  Map
//
//  Created by pig on 14-9-13.
//
//

#include "MapLayer.h"
#include "LevelManager.h"

MapLayer *MapLayer::create(Level *level)
{
    MapLayer *mapLayer = new MapLayer();
    if (mapLayer->initWithLevel(level)) {
        mapLayer->autorelease();
        return mapLayer;
    }
    CC_SAFE_RELEASE(mapLayer);
    return NULL;
}

bool MapLayer::initWithLevel(Level *level)
{
    if (!CCLayer::init()) {
        return false;
    }
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    
    CCLOG("level->mapName: %s", level->mapName->m_sString.c_str());
    gameMap = CCTMXTiledMap::create(level->mapName->m_sString.c_str());
    float scale = visibleSize.height / gameMap->getContentSize().height;
//    gameMap->setScale(scale);
    gameMap->setPosition(0, 0);
    this->addChild(gameMap, 1);
    
    bgLayer = gameMap->layerNamed("bg_layer");
    redWallLayer = gameMap->layerNamed("red_wall_layer");
    boxLayer = gameMap->layerNamed("box_layer");
    destLayer = gameMap->layerNamed("desc_layer");
    
    objects = gameMap->objectGroupNamed("object1");
    CCDictionary *object1 = objects->objectNamed("object_test1");
    CCLog("object1 x: %s", object1->valueForKey("x")->getCString());
    
    return true;
}

void MapLayer::initBox()
{
    //todo
}

//触摸点坐标转化成地图上的坐标点
CCPoint MapLayer::tileCoordinateWithPosition(cocos2d::CCPoint position)
{
    int coordinatex = 0;
    int coordinatey = 0;
    
    CCSize bgLayerSize = bgLayer->getLayerSize();
    CCSize tileSize = gameMap->getTileSize();
    coordinatex = position.x / tileSize.width;
    coordinatey = bgLayerSize.height - position.y / tileSize.height;
    
    if ((coordinatex >= 0) && (coordinatex < bgLayerSize.width) && (coordinatey >= 0) && (coordinatey < bgLayerSize.height)) {
        return ccp(coordinatex, coordinatey);
    } else {
        return ccp(-1, -1);
    }
}

//将地图坐标转换成瓦片值
int MapLayer::tileIdWithTileCoordinate(cocos2d::CCPoint tileCoordinate)
{
    if (tileCoordinate.x < 0) {
        return -1;
    }
    if (tileCoordinate.y < 0) {
        return -1;
    }
    
    CCSize bgLayerSize = bgLayer->getLayerSize();
    if (tileCoordinate.x >= bgLayerSize.width) {
        return -1;
    }
    if (tileCoordinate.y >= bgLayerSize.height) {
        return -1;
    }
    
    return redWallLayer->tileGIDAt(tileCoordinate);
}

//触摸点转化为瓦片值
int MapLayer::tileIdWithPosition(cocos2d::CCPoint position)
{
    int coordinatex = 0;
    int coordinatey = 0;
    
    CCSize bgLayerSize = bgLayer->getLayerSize();
    CCSize tileSize = gameMap->getTileSize();
    coordinatex = position.x / tileSize.width;
    coordinatey = bgLayerSize.height - position.y / tileSize.height;
    
    if ((coordinatex >= 0) && (coordinatex < bgLayerSize.width) && (coordinatey >= 0) && (coordinatey < bgLayerSize.height)) {
        CCPoint tileCoordinate = ccp(coordinatex, coordinatey);
        int tileId = redWallLayer->tileGIDAt(tileCoordinate);
        CCDictionary *tileDic = gameMap->propertiesForGID(tileId);
        if (tileDic) {
            CCString *value = (CCString *)tileDic->objectForKey("collion");
            CCLog("value: %s", value->getCString());
        }
        if (tileId < 1) {
            tileId = boxLayer->tileGIDAt(tileCoordinate);
        }
        return tileId;
    } else {
        return -1;
    }
}

//将地图坐标点转换成触摸点坐标
CCPoint MapLayer::positionWithTileCoordinate(cocos2d::CCPoint tileCoordinate)
{
    int posx = 0;
    int posy = 0;
    
    CCSize bgLayerSize = bgLayer->getLayerSize();
    CCSize tileSize = gameMap->getTileSize();
    posx = tileCoordinate.x * tileSize.width;
    posy = (bgLayerSize.height - tileCoordinate.y) * tileSize.height;
    
    return ccp(posx, posy);
}
