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

	auto mask = Sprite::create("Images/CalendarMask.png");
	//auto mask = Sprite::create("Images/mask_star.png");

	auto content = Sprite::create("Images/Calendar2.png");
	//content->setPosition(Vec2(clipper->getContentSize.width/2,
	//	clipper->getContentSize.height / 2)

	auto clipper = ClippingNode::create();
	clipper->setStencil(mask);
	clipper->setAlphaThreshold(0.05f);
	clipper->setPosition(Vec2(240, 160));
	clipper->addChild(content);

	this->addChild(clipper);

    return true;
}
