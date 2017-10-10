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
	//pMan->setAnchorPoint(Vec2(0, 0));
	this->addChild(pMan);

	pLabel1 = LabelTTF::create("0", "Arial", 64);
	pLabel2 = LabelTTF::create("0", "Arial", 64);

	pLabel1->setPosition(Vec2(100, 100));
	pLabel2->setPosition(Vec2(200, 100));

	pLabel1->setColor(Color3B::BLACK);
	pLabel2->setColor(Color3B::BLACK);

	this->addChild(pLabel1);
	this->addChild(pLabel2);

	bSelect = false;
	i = 0;

    return true;
}

void HelloWorld::onEnter() {
	Scene::onEnter();

	auto listener = EventListenerTouchAllAtOnce::create();

	listener->onTouchesBegan = CC_CALLBACK_2(HelloWorld::onTouchesBegan, this);
	listener->onTouchesMoved = CC_CALLBACK_2(HelloWorld::onTouchesMoved, this);
	listener->onTouchesEnded = CC_CALLBACK_2(HelloWorld::onTouchesEnded, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void HelloWorld::onExit() {
	_eventDispatcher->removeAllEventListeners();
	Scene::onExit();
}

void HelloWorld::onTouchesBegan(const std::vector<cocos2d::Touch*> touches, cocos2d::Event* event) {
	bSelect = false;

	char myNum1[20] = { 0 };
	sprintf(myNum1, "%lu", touches.size());
	pLabel1->setString(myNum1);

	//if ((int)touches.size() < 2) {
	//	return;
	//}

	for (auto &item : touches) {
		auto touch = item;
		auto touchPoint = touch->getLocation();

		Rect rect = pMan->getBoundingBox();
		if (rect.containsPoint(touchPoint)) {
			log("Touch x : %d y : %d", (int)touchPoint.x, (int)touchPoint.y);
			i++;
		}
	}

	char myNum2[20] = { 0 };
	sprintf(myNum2, "%d", i);
	pLabel2->setString(myNum2);

	if (i > 1) {
		bSelect = true;
	}
}

void HelloWorld::onTouchesMoved(const std::vector<cocos2d::Touch*> touches, cocos2d::Event* event) {
	// 회전시키는 로직
	if (bSelect) {
		auto touch = touches[0];

		Vec2 oldPoint = touch->getPreviousLocation();
		Vec2 nowPoint = touch->getLocation();

		Vec2 firstVector = oldPoint - pMan->getPosition();
		float firstRotateAngle = -firstVector.getAngle();
		float previousTouch = CC_RADIANS_TO_DEGREES(firstRotateAngle);

		Vec2 secondVector = nowPoint - pMan->getPosition();
		float secondRotateAngle = -secondVector.getAngle();
		float currentTouch = CC_RADIANS_TO_DEGREES(secondRotateAngle);

		gRotation = gRotation + currentTouch - previousTouch;
		gRotation = fmod(gRotation, 360.0f);

		pMan->setRotation(gRotation);
	}
}

void HelloWorld::onTouchesEnded(const std::vector<cocos2d::Touch*> touches, cocos2d::Event* event) {
	pLabel1->setString("0");
	pLabel2->setString("0");

	i = 0;
	bSelect = false;
}