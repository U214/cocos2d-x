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

	m_pStreak = MotionStreak::create(2.0f, 1.0f, 10.0f, Color3B::RED, "streak2.png");
	this->addChild(m_pStreak);

    return true;
}

void HelloWorld::onEnter() {
	Scene::onEnter();
	auto listener = EventListenerTouchOneByOne::create();

	listener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(HelloWorld::onTouchMoved, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void HelloWorld::onExit() {
	Scene::onExit();
}

bool HelloWorld::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event) {
	m_pStreak->reset();

	auto touchPoint = touch->getLocation();
	m_pStreak->setPosition(touchPoint);

	return true;
}

void HelloWorld::onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event) {
	auto touchPoint = touch->getLocation();

	m_pStreak->setPosition(touchPoint);
}