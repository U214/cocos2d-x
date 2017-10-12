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

	auto pLabel1 = LabelTTF::create(
		"Fixed priority test",
		"Arial",
		20);
	pLabel1->setPosition(Vec2(240, 300));
	pLabel1->setColor(Color3B::BLACK);
	this->addChild(pLabel1, 101);

	auto pLabel2 = LabelTTF::create(
		"Fixed priority, Blue : 30, Red : 20, Yellow : 10 \n"
		"작은 수가 더 높은 우선순위를 가집니다",
		"Arial",
		14);
	pLabel2->setPosition(Vec2(240, 270));
	pLabel2->setColor(Color3B::BLUE);
	this->addChild(pLabel2, 101);

	sprite1 = new Monster();
	sprite2 = new Monster();
	sprite3 = new Monster();

	sprite1->setTexture("Images/CyanSquare.png");
	sprite2->setTexture("Images/MagentaSquare.png");
	sprite3->setTexture("Images/YellowSquare.png");

	sprite1->setPosition(Vec2(240, 120) + Vec2(-80, 80));
	sprite2->setPosition(Vec2(240, 120));
	sprite3->setPosition(Vec2(0, 0));

	sprite1->setPriority(30);
	sprite2->setPriority(20);
	sprite3->setPriority(10);

	addChild(sprite1);
	addChild(sprite2);
	sprite2->addChild(sprite3);

    return true;
}
