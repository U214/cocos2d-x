#include "TestScene2.h"

USING_NS_CC;

Scene* TestScene2::createScene()
{
	return TestScene2::create();
}

bool TestScene2::init()
{
	if (!Scene::init())
	{
		return false;
	}

	auto wlayer = LayerColor::create(Color4B(255, 255, 255, 255));
	this->addChild(wlayer);

	/////////////////////////////////


	return true;
}
