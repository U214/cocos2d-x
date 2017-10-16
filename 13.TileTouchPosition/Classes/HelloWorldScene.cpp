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

	/////////////////////////////
		
	map = TMXTiledMap::create("TileMaps/iso-test-touch.tmx");
	this->addChild(map, 0, 1);

	Size s = map->getContentSize();
	log("ContentSize: %f, %f", s.width, s.height);
	map->setPosition(Vec2(0, 0));
  
    return true;
}

void HelloWorld::onEnter()
{
	Scene::onEnter();

	//싱글 터치모드로 터치 리스너 등록
	listener = EventListenerTouchOneByOne::create();
	//swallow touches only available in OneByOne mode.
	//핸들링 된 터치 이벤트를 터치 이벤트 array에서 지우겠다는 의미다.

	listener->setSwallowTouches(true);

	listener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(HelloWorld::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);


	//the priority of the touch listener is based on the draw order of sprite 
	//터치 리스너의 우선순위를 (노드가) 화면에 그려진 순서대로 한다.

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}


void HelloWorld::onExit()
{

	_eventDispatcher->removeEventListener(listener);
	//_eventDispatcher->removeALLEventListener();
	//_eventDispatcher->removeEventListenersForType
	//(EventListeners::Type::TOUCH_ONE_BY_ONE);

	Scene::onExit();

}

//처음 손가락이 화면에 닿는 순간 호출된다. 
bool HelloWorld::onTouchBegan(Touch*touch, Event*event)
{
	auto touchPoint = touch->getLocation();
	touchPoint = map->convertToNodeSpace(touchPoint);

	Vec2 pos = touchTOXY(touchPoint);
		log("gid.x = %f, gid.y = %f",
			pos.x,
			pos.y);

	return true;
}

Vec2 HelloWorld::touchTOXY(Vec2 touch)
{
	Size maps = map->getContentSize();
	Size ts = map->getTileSize();
	int mapsize = maps.width / ts.width;

	int isoy = (
		(
		(touch.y / ts.height) +
			(touch.x - (mapsize * ts.width / 2)) / ts.width
			) - mapsize
		) *-1;

	int isox = (
		(
		(touch.y / ts.height) -
			(touch.x - (mapsize * ts.width / 2)) / ts.width
			) - mapsize
		) *-1;
	return Vec2(isox, isoy);
}

void HelloWorld::onTouchMoved(cocos2d::Touch*touch, cocos2d::Event*event)
{

}
void HelloWorld::onTouchEnded(cocos2d::Touch*touch, cocos2d::Event*event)
{

}