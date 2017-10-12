#include "HelloWorldScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
	return HelloWorld::create();
}

bool HelloWorld::init()
{
	if (!Scene::init())
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
	auto listener = EventListenerTouchAllAtOnce::create();

	listener->onTouchesBegan = CC_CALLBACK_2(HelloWorld::onTouchesBegan, this);
	listener->onTouchesMoved = CC_CALLBACK_2(HelloWorld::onTouchesMoved, this);
	listener->onTouchesEnded = CC_CALLBACK_2(HelloWorld::onTouchesEnded, this);
	listener->onTouchesCancelled = CC_CALLBACK_2(HelloWorld::onTouchesCancelled, this);

	// 터치 리스너의 우선순위를 화면에 그려진 순서대로 한다.
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void HelloWorld::onExit() {
	_eventDispatcher->removeEventListener(listener);
	Scene::onExit();
}

// 처음 손가락이 화면에 닿는 순간 호출된다.
bool HelloWorld::onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event) {
	auto touch = touches[0];
	auto touchPoint = touch->getLocation();
	touchPoint = this->convertToWorldSpace(touchPoint);

	log("onTouchesBegan id = %d, x = %f, y = %f",
		touch->getID(),
		touchPoint.x,
		touchPoint.y);

	// 터치 체크
	bool bTouch = pMan->getBoundingBox().containsPoint(touchPoint);

	if (bTouch) {
		log("Sprite clicked...");
	}

	/*
	for (auto &item : touched){
		auto touch = item;
		auto touchPoint = touch->getLocation();

		log("onTouchesBegan id = %d, x = %f, y = %f",
		touch->getID(),
		touchPoint.x,
		touchPoint.y);
	}
	*/

	return true;
}

// 손가락을 화면에 떼지 않고 이리 저리 움직일 때 계속해서 호출된다.
// 호출의 빈도수는 이벤트를 핸들링하는 애플리케이션의 run loop에 달렸다.
void HelloWorld::onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event) {
	auto touch = touches[0];
	auto touchPoint = touch->getLocation();
	touchPoint = this->convertToWorldSpace(touchPoint);

	log("onTouchesMoved id = %d, x = %f, y = %f",
		touch->getID(),
		touchPoint.x,
		touchPoint.y);
}

// 손가락을 화면에 떼는 순간 호출된다.
void HelloWorld::onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event) {
	auto touch = touches[0];
	auto touchPoint = touch->getLocation();
	touchPoint = this->convertToWorldSpace(touchPoint);

	log("onTouchesEnded id = %d, x = %f, y = %f",
		touch->getID(),
		touchPoint.x,
		touchPoint.y);
}

// 시스템이 터치를 중지시키는 경우에 호출된다. ex)  전화가 오는 경우
void HelloWorld::onTouchesCancelled(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event) {
	onTouchesEnded(touches, event);
}