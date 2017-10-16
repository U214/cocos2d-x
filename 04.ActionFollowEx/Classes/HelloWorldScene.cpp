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

	auto pMan = Sprite::create("Images/grossini.png");
	pMan->setPosition(Vec2(50, 160));
	this->addChild(pMan);

	auto pR1 = Sprite::create("Images/r1.png");
	pR1->setPosition(Vec2(25, 160));
	this->addChild(pR1);

	auto pR2 = Sprite::create("Images/r1.png");
	pR2->setPosition(Vec2(960 - 25, 160));
	this->addChild(pR2);

	auto move = MoveBy::create(2, Vec2(480 * 2 - 100, 0));
	auto move_back = move->reverse();
	auto seq = Sequence::create(move, move_back, NULL);
	auto rep = RepeatForever::create(seq);

	pMan->runAction(rep);

	this->runAction(Follow::create(pMan, Rect(0, 0, 480 * 2, 320)));

    return true;
}
