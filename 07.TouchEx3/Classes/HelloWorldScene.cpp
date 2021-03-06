﻿#include "HelloWorldScene.h"

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
	// 람다 함수 타입

	auto pLabel = LabelTTF::create(
		"블럭을 터치해서 드래그 하세요",
		"Arial",
		20);
	pLabel->setPosition(Vec2(240, 280));
	pLabel->setColor(Color3B::BLACK);
	this->addChild(pLabel, 101);

	sprite1 = Sprite::create("Images/CyanSquare.png");
	sprite1->setPosition(Vec2(240, 160) + Vec2(-80, 80));
	this->addChild(sprite1);

	sprite2 = Sprite::create("Images/MagentaSquare.png");
	sprite2->setPosition(Vec2(240, 160));
	this->addChild(sprite2);

	sprite3 = Sprite::create("Images/YellowSquare.png");
	sprite3->setPosition(Vec2(0, 0));
	sprite2->addChild(sprite3);

    return true;
}

void HelloWorld::onEnter() {
	Scene::onEnter();

	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);

	listener->onTouchBegan = [=](Touch* touch, Event* event) {
		log("touch began");

		auto target = static_cast<Sprite*>(event->getCurrentTarget());

		Vec2 locationInNode = target->convertToNodeSpace(touch->getLocation());
		Size s = target->getContentSize();
		Rect rect = Rect(0, 0, s.width, s.height);

		if (rect.containsPoint(locationInNode)) {
			reZorder(target);

			log("sprite onTouchBegan x = %f, y = %f",
				locationInNode.x, locationInNode.y);
			
			target->setOpacity(180);

			return true;
		}
		return false;
	};

	listener->onTouchMoved = [](Touch* touch, Event* event) {
		auto target = static_cast<Sprite*>(event->getCurrentTarget());
		target->setPosition(target->getPosition() + touch->getDelta());
	};

	listener->onTouchEnded = [](Touch* touch, Event* event) {
		auto target = static_cast<Sprite*>(event->getCurrentTarget());
		log("sprete ontouchEnded");
		target->setOpacity(255);
	};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, sprite1);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener->clone(), sprite2);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener->clone(), sprite3);
}

void HelloWorld::onExit() {
	_eventDispatcher->removeAllEventListeners();

	Scene::onExit();
}

void HelloWorld::reZorder(Sprite* pSender) {
	sprite1->setZOrder(0);
	sprite2->setZOrder(0);
	sprite3->setZOrder(0);

	pSender->setZOrder(1);
}