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

	pMan = Sprite::create("Images/grossini.png");
	pMan->setPosition(Vec2(240, 160));
	this->addChild(pMan);

    return true;
}

void HelloWorld::onEnter() {
	Scene::onEnter();

	// 싱글 터치 모드로 터치 리스너 등록
	auto listener = EventListenerTouchOneByOne::create();

	// 핸들링 된 터치 이벤트를 터치 이벤트 배열에서 지우겠다는 의미
	listener->setSwallowTouches(true);

	listener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(HelloWorld::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);
	listener->onTouchCancelled = CC_CALLBACK_2(HelloWorld::onTouchCancelled, this);

	// 터치 리스너의 우선순위를 화면에 그려진 순서대로 한다.
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void HelloWorld::onExit() {
	_eventDispatcher->removeEventListener(listener);
	Scene::onExit();
}

// 처음 손가락이 화면에 닿는 순간 호출된다.
bool HelloWorld::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event) {
	auto touchPoint = touch->getLocation();

	log("onTouchBegan id = %d, x = %f, y = %f",
		touch->getID(),
		touchPoint.x,
		touchPoint.y);

	// 터치 체크
	bool bTouch = pMan->getBoundingBox().containsPoint(touchPoint);

	if (bTouch) {
		log("Sprite clicked...");
	}

	return true;
}

// 손가락을 화면에 떼지 않고 이리 저리 움직일 때 계속해서 호출된다.
// 호출의 빈도수는 이벤트를 핸들링하는 애플리케이션의 run loop에 달렸다.
void HelloWorld::onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event) {
	auto touchPoint = touch->getLocation();

	log("onTouchMoved id = %d, x = %f, y = %f",
		touch->getID(),
		touchPoint.x,
		touchPoint.y);
}

// 손가락을 화면에 떼는 순간 호출된다.
void HelloWorld::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event) {
	auto touchPoint = touch->getLocation();

	log("onTouchEnded id = %d, x = %f, y = %f",
		touch->getID(),
		touchPoint.x,
		touchPoint.y);
}

// 시스템이 터치를 중지시키는 경우에 호출된다. ex)  전화가 오는 경우
void HelloWorld::onTouchCancelled(cocos2d::Touch* touch, cocos2d::Event* event) {

}