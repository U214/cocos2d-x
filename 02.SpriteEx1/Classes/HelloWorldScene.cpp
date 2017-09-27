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
    
	////////////////////////////////

	auto pMan = Sprite::create("Images/grossini.png");
	pMan->setPosition(Vec2(240, 160));
	this->addChild(pMan, 2);

	auto pWoman = Sprite::create("Images/grossinis_sister1.png");
	pWoman->setPosition(Vec2(260, 160));
	this->addChild(pWoman, 1);

	// z-order값이 있으면 큰 순서대로 앞에 온당

	pMan->setLocalZOrder(1);
	//스프라이트 위치 동적 지정
    return true;
}
