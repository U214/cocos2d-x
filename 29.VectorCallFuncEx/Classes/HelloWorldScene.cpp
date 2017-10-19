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

	//A* 예제에도 적용되어 있음
	// 조합스킬에 써도 괜찮겠당

	Vector<FiniteTimeAction*> vact;

	for (int i = 0; i < 5; i++) {
		auto act1 = DelayTime::create(3.0f);
		auto act2 = CallFunc::create(CC_CALLBACK_0(HelloWorld::callback1, this, i));

		vact.pushBack(act1);
		vact.pushBack(act2);
	}

	auto action = Sequence::create(vact);
	this->runAction(action);


    return true;
}

void HelloWorld::callback1(int num) {
	log("number : %d", num);
}