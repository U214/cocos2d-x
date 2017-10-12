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

	/////////////////////////////////

	winSize = Director::getInstance()->getWinSize();

	this->createBackground();
	this->createDragon();
	this->createArrowButtons();

    return true;
}

void HelloWorld::createBackground() {
	// 배경 레이어1
	auto background1 = Sprite::create("Images/background1.png");
	background1->setAnchorPoint(Vec2(0, 0));
	background1->setPosition(Vec2(0, 0));

	// 배경 레이어1
	auto background2 = Sprite::create("Images/background2.png");
	background2->setAnchorPoint(Vec2(0, 0));
	background2->setPosition(Vec2(512, 0));

	// 배경 스프라이트를 담을 부모로 레이어를 만든다.
	auto voidNode = Layer::create();

	// 배경 스프라이트를 레이어에 넣는다
	// 배경이미지의 사이즈 : 512 x 320
	voidNode->addChild(background1);
	voidNode->addChild(background2);

	voidNode->setTag(1);

	this->addChild(voidNode, 0);
}

void HelloWorld::createDragon() {
	auto texture = Director::getInstance()->getTextureCache()
		->addImage("Images/dragon_animation.png");

	auto animation = Animation::create();
	animation->setDelayPerUnit(0.1f);

	for (int i = 0; i < 6; i++) {
		int index = i % 4;
		int rowIndex = i / 4;

		animation->addSpriteFrameWithTexture(
			texture,
			Rect(index * 130, rowIndex * 140 + 70, 110, 70));
	}

	dragon = Sprite::createWithTexture(texture, Rect(0, 70, 110, 70));
	dragon->setPosition(Vec2(240, 160));
	this->addChild(dragon);

	auto animate = Animate::create(animation);
	auto rep = RepeatForever::create(animate);
	dragon->runAction(rep);
}

void HelloWorld::createArrowButtons() {
	// 왼쪽 화살표
	leftSprite = Sprite::create("Images/b1.png");
	leftSprite->setPosition(Vec2(180, 30));

	this->addChild(leftSprite, 2);

	// 클릭시 왼쪽 화살표
	leftPressedSprite = Sprite::create("Images/b2.png");
	leftPressedSprite->setPosition(leftSprite->getPosition());

	this->addChild(leftPressedSprite, 1);

	// 오른쪽 화살표
	rightSprite = Sprite::create("Images/f1.png");
	rightSprite->setPosition(Vec2(300, 30));

	this->addChild(rightSprite, 2);

	// 클릭시 오른쪽 화살표
	rightPressedSprite = Sprite::create("Images/f2.png");
	rightPressedSprite->setPosition(rightSprite->getPosition());

	this->addChild(rightPressedSprite, 1);
}

void HelloWorld::onEnter() {
	Scene::onEnter();

	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);

	listener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(HelloWorld::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void HelloWorld::onExit() {
	_eventDispatcher->removeEventListener(listener);
	Scene::onExit();
}

bool HelloWorld::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event) {
	// leftSprite, rightSprite의 visible값을 직접 사용해도 무방
	isLeftPressed = false;
	isRightPressed = false;

	if (this->isTouchInside(leftSprite, touch) == true) {
		leftSprite->setVisible(false);
		isLeftPressed = true;
	}
	else if (this->isTouchInside(rightSprite, touch) == true) {
		rightSprite->setVisible(false);
		isRightPressed = true;
	}

	if (isLeftPressed == true || isRightPressed == true) {
		this->startMovingBackground();
	}

	return true;
}

void HelloWorld::onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event) {
	if (isLeftPressed == true && this->isTouchInside(leftSprite, touch) == false) {
		leftSprite->setVisible(true);
		this->stopMovingBackground();
	}

	if (isRightPressed == true && this->isTouchInside(rightSprite, touch) == false) {
		rightSprite->setVisible(true);
		this->stopMovingBackground();
	}

}

void HelloWorld::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event) {
	if (isLeftPressed == true || isRightPressed == true) {
		this->stopMovingBackground();
	}

	if (isLeftPressed == true) {
		leftSprite->setVisible(true);
	}

	if (isRightPressed == true) {
		rightSprite->setVisible(true);
	}
}

bool HelloWorld::isTouchInside(cocos2d::Sprite* sprite, cocos2d::Touch* touch) {
	auto touchPoint = touch->getLocation();
	bool bTouch = sprite->getBoundingBox().containsPoint(touchPoint);

	return bTouch;
}

void HelloWorld::startMovingBackground() {
	log("start moving");
}
void HelloWorld::stopMovingBackground() {
	log("stop moving");
}
void HelloWorld::moveBackground(float t) {
	log("moving background");
}
