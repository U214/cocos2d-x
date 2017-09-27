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
/*
	auto parent = Sprite::create("Images/white-512x512.png");
	parent->setTextureRect(Rect(0, 0, 150, 150));
	parent->setPosition(Vec2(240, 160));
	parent->setColor(Color3B(0, 0, 255));
	this->addChild(parent);
*/

	auto parent = Sprite::create("Images/grossini.png");
	parent->setPosition(Vec2(240, 160));
	this->addChild(parent);

	auto child = Sprite::create("Images/white-512x512.png");
	child->setTextureRect(Rect(0, 0, 50, 5));

	Size parentSize;
	parentSize = parent->getContentSize();

	child->setPosition(Vec2(parentSize.width / 2.0, parentSize.height + 10));
	// 부모(150, 150)기준의 포지션 ( 정가운데로 하려면 75, 75로)
	child->setColor(Color3B::RED);
	parent->addChild(child);

    return true;
}
