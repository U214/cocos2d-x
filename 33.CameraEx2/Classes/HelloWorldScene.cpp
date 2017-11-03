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

	Size winSize = Director::getInstance()->getWinSize();

	auto bgLayer = LayerColor::create(Color4B(0, 255, 0, 255),
		winSize.width, winSize.height);
	bgLayer->setRotation3D(cocos2d::Vertex3F(-20.0, 0.0, 0.0));
	this->addChild(bgLayer);

	auto bgSprite = Sprite::create("Images/Hello.png");
	bgSprite->setPosition(Vec2(winSize.width / 2, winSize.height / 2));
	bgLayer->addChild(bgSprite);

	auto man = Sprite::create("Images/grossini.png");
	man->setPosition(Vec2(240, -50));
	bgLayer->addChild(man);

	auto act = MoveBy::create(2.0f, Vec2(0, 450));
	auto seq = Sequence::create(
		Place::create(Vec2(240, -50)),
		act,
		nullptr);
	auto rep = RepeatForever::create(seq);
	man->runAction(rep);

    return true;
}
