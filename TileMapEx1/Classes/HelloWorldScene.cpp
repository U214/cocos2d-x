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

	auto tmap = TMXTiledMap::create("TileMaps/TestDesert.tmx");
	this->addChild(tmap, 0, 11); // z-order가 -1면 화면 안나옴
	Size s = tmap->getContentSize();
	log("ContentSize : %f, %f", s.width, s.height);

    return true;
}

void HelloWorld::onEnter() {
	Scene::onEnter();

	// 싱글 터치 모드로 터치 리스너 등록
	listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);

	listener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(HelloWorld::onTouchMoved, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void HelloWorld::onExit() {
	_eventDispatcher->removeEventListener(listener);
	Scene::onExit();
}

// 처음 손가락이 화면에 닿는 순간 호출된다.
bool HelloWorld::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event) {
	auto touchPoint = touch->getLocation();

	return true;
}

// 손가락을 화면에 떼지 않고 이리 저리 움직일 때 계속해서 호출된다.
// 호출의 빈도수는 이벤트를 핸들링하는 애플리케이션의 run loop에 달렸다.
void HelloWorld::onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event) {
	Vec2 diff = touch->getDelta();

	Node* node = this->getChildByTag(11);
	Vec2 currentPos = node->getPosition();

	Vec2 newPos = currentPos + diff;

	if (newPos.x < -160) {
		newPos.x = -160;
	}

	if (newPos.x > 0) {
		newPos.x = 0;
	}
	newPos.y = 0;

	node->setPosition(newPos);
}



