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

	auto cache = SpriteFrameCache::getInstance();
	cache->addSpriteFramesWithFile("animations/grossini.xml");

	Vector<SpriteFrame*> animFrames;

	char str[100] = { 0 };

	for (int i = 1; i < 15; i++) {
		sprintf(str, "grossini_dance_%02d.png", i);
		SpriteFrame* frame = cache->getSpriteFrameByName(str);
		animFrames.pushBack(frame);
	}

	auto pMan = Sprite::createWithSpriteFrameName("grossini_dance_01.png");
	pMan->setPosition(Vec2(240, 160));
	this->addChild(pMan);

	auto animation = Animation::createWithSpriteFrames(animFrames, 0.5f);
	auto animate = Animate::create(animation);
	auto rep = RepeatForever::create(animate);

	pMan->runAction(rep);

    return true;
}
