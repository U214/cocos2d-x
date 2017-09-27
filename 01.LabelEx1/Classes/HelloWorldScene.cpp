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

	//auto pLabel = LabelTTF::create("Hello World","Arial", 64);
	//auto pLabel = LabelTTF::create("동해물과 백두산이 마르고 닳도록 하느님이 보우하사 우리나라 만세","Arial",34);
	auto pLabel = LabelTTF::create(
		"동해물과 백두산이 마르고 닳도록 하느님이 보우하사 우리나라 만세", 
		"Arial", 
		34,
		Size(300, 200),
		TextHAlignment::CENTER,
		TextVAlignment::CENTER);
	// Size() : 해당 크기가 넘어가면 알아서 줄변경

	pLabel->setPosition(Vec2(240, 160));
	pLabel->setColor(Color3B(0, 0, 0));
	this->addChild(pLabel);

    return true;
}
