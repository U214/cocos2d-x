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

	auto sprite = Sprite::create("Images/grossinis_sister1.png");

	pt = ProgressTimer::create(sprite);
	pt->setType(ProgressTimer::Type::RADIAL);
	pt->setPosition(Vec2(240, 160));
	
	this->addChild(pt);
	nNum = 0;
	this->schedule(schedule_selector(HelloWorld::myTick), 0.1f);

    return true;
}

void HelloWorld::myTick(float f) {
	nNum++;

	this->SpriteProgressToRadial(nNum * 2);
	if (nNum > 50) {
		nNum = 0;
	}
}

void HelloWorld::SpriteProgressToRadial(float f) {
	pt->setPercentage(f);
}
