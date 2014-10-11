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
    
    CCLOG("level->mapName: %s", level->mapName->getCString());
    gameMap = CCTMXTiledMap::create(level->mapName->getCString());
    gameMap->setPosition(0, 0);
    this->addChild(gameMap, 1);
    
    bgLayer = gameMap->layerNamed("bg_layer");
    redWallLayer = gameMap->layerNamed("red_wall_layer");
    boxLayer = gameMap->layerNamed("box_layer");
    destLayer = gameMap->layerNamed("desc_layer");
    
    //
    this->initBalloon();
    this->initBox();
    
    return true;
}

void MapLayer::initBalloon()
{
    //todo
    CCPoint point;
    Balloon *balloon = NULL;
    CCPoint adjustPoint = ccp(2, 2);
    
    point = this->positionWithTileCoordinate(ccp(8, 6));
    balloon = Balloon::create();
    balloon->setPosition(ccpAdd(point, adjustPoint));
    this->balloons->addObject(balloon);
    
    point = this->positionWithTileCoordinate(ccp(9, 10));
    balloon = Balloon::create();
    balloon->setPosition(ccpAdd(point, adjustPoint));
    this->balloons->addObject(balloon);
    
    point = this->positionWithTileCoordinate(ccp(11, 8));
    balloon = Balloon::create();
    balloon->setPosition(ccpAdd(point, adjustPoint));
    this->balloons->addObject(balloon);
    
    CCObject *object;
    CCARRAY_FOREACH(balloons, object) {
        Balloon *balloonObject = (Balloon *)object;
        balloonObject->setAnchorPoint(ccp(0, 0));
        this->addChild(balloonObject, 1);
    }
}

void MapLayer::initBox()
{
    objects = gameMap->objectGroupNamed("object1");
    CCDictionary *object1 = objects->objectNamed("object_test1");
    CCLog("object1 x: %s", object1->valueForKey("x")->getCString());
    
    //test logic
    CCPoint point;
    Box *box = NULL;
    CCPoint adjustPoint = ccp(2, 2);
    
    point = this->positionWithTileCoordinate(ccp(5, 7));
    box = Box::create();
    box->setPosition(ccpAdd(point, adjustPoint));
    this->boxes->addObject(box);
    
    point = this->positionWithTileCoordinate(ccp(8, 10));
    box = Box::create();
    box->setPosition(ccpAdd(point, adjustPoint));
    this->boxes->addObject(box);
    
    point = this->positionWithTileCoordinate(ccp(10, 10));
    box = Box::create();
    box->setPosition(ccpAdd(point, adjustPoint));
    this->boxes->addObject(box);
    
    CCObject *object;
    CCARRAY_FOREACH(boxes, object) {
        Box *boxObject = (Box *)object;
        boxObject->setAnchorPoint(ccp(0, 0));
        this->addChild(boxObject, 2);
    }
}

MapLayer::MapLayer()
{
    boxes = CCArray::create();//autorelease，会被自动释放
    boxes->retain();
    
    balloons = CCArray::create();
    balloons->retain();
}

MapLayer::~MapLayer()
{
    if (NULL != boxes) {
        boxes->removeAllObjects();
        CC_SAFE_RELEASE_NULL(boxes);
    }
    if (NULL != balloons) {
        balloons->removeAllObjects();
        CC_SAFE_RELEASE_NULL(balloons);
    }
}

//触摸点坐标转化成地图上的坐标点(如果地图内，则为大于0的坐标。否则为（-1, -1）)
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
    CCPoint tileCoordinate = this->tileCoordinateWithPosition(position);
    
    if ((tileCoordinate.x >= 0) && (tileCoordinate.y >= 0)) {
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
    }
    
    return -1;
}

//触摸点转化为red wall layer瓦片值
int MapLayer::tileIdOfRedWallWithPosition(cocos2d::CCPoint position)
{
    CCPoint tileCoordinate = this->tileCoordinateWithPosition(position);
    if ((tileCoordinate.x >= 0) && (tileCoordinate.y >= 0)) {
        int tileId = redWallLayer->tileGIDAt(tileCoordinate);
        return tileId;
    }
    return -1;
}

//获取某个触摸点的box,如果不存在则返回null
Box *MapLayer::boxWithPosition(cocos2d::CCPoint position)
{
    Box *box = NULL;
    CCPoint tileCoordinate = this->tileCoordinateWithPosition(position);
    
    CCObject *object;
    CCARRAY_FOREACH(this->boxes, object) {
        Box *boxObject = (Box *)object;
        CCPoint boxCoordinate = this->tileCoordinateWithPosition(boxObject->getPosition());
//        CCLOG("tileCoordinate(%f, %f), boxCoordinate(%f, %f)", tileCoordinate.x, tileCoordinate.y, boxCoordinate.x, boxCoordinate.y);
        if (tileCoordinate.equals(boxCoordinate)) {
            box = boxObject;
            break;
        }
    }
    if (box) {
        CCLog("boxWithPosition: (box != NULL)");
    } else {
        CCLog("boxWithPosition: (box == NULL)");
    }
    return box;
}

//
Balloon *MapLayer::balloonWithPosition(cocos2d::CCPoint position)
{
    Balloon *balloon = NULL;
    CCPoint tileCoordinate = this->tileCoordinateWithPosition(position);
    
    CCObject *object;
    CCARRAY_FOREACH(balloons, object) {
        Balloon *balloonObject = (Balloon *)object;
        CCPoint balloonCoordinate = this->tileCoordinateWithPosition(balloonObject->getPosition());
        if (tileCoordinate.equals(balloonCoordinate)) {
            balloon = balloonObject;
            break;
        }
    }
    if (balloon) {
        CCLog("balloonWithPosition: (balloon != NULL)");
    } else {
        CCLog("balloonWithPosition: (balloon == NULL)");
    }
    return balloon;
}
