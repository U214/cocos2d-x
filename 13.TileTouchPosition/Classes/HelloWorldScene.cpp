#include "HelloWorldScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

bool HelloWorld::init()
{
    if ( !Scene::init() )
    {
        return false;
    }

	auto wlayer = LayerColor::create(Color4B(255, 255, 255, 255));
	this->addChild(wlayer);
    
	/////////////////////////////////

	map = TMXTiledMap::create("TileMaps/iso-test-touch.tmx");
	this->addChild(map, 0, 1);

	Size s = map->getContentSize();
	log("ContentSize : %f, %f", s.width, s.height);
	map->setPosition(Vec2(0, 0));

    return true;
}

void HelloWorld::onEnter() {
	Scene::onEnter();

	// 싱글 터치 모드로 터치 리스너 등록
	listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);

	listener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void HelloWorld::onExit() {
	_eventDispatcher->removeEventListener(listener);
	Scene::onExit();
}

bool HelloWorld::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event) {
	auto touchPoint = touch->getLocation();
	touchPoint = map->convertToNodeSpace(touchPoint);

	Vec2 pos = touchToXY(touchPoint);

	log("gid.x = %f, gid.y = %f",
		pos.x,
		pos.y);

	return true;
}

Vec2 HelloWorld::touchToXY(Vec2 touch) {
	Size maps = map->getContentSize();
	Size ts = map->getTileSize();

	int mapsize = maps.width / ts.width;

	int isoy = (((touch.y / ts.height) + (touch.x - (mapsize * ts.width / 2))
		/ ts.width) - mapsize) * -1;
	int isox = (((touch.y / ts.height) - (touch.x - (mapsize * ts.width / 2))
		/ ts.width) - mapsize) * -1;
	
	return Vec2(isox, isoy);
}
