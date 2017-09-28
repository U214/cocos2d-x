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
	// 다양한 방법으로 스프라이트쉬트 텍스쳐를 만든다.

	// ---------------------------------------------------------
	// Type 1 : from Sprite
	// ---------------------------------------------------------
	auto sprite = Sprite::create("Images/grossini_dance_atlas.png");
	auto texture1 = sprite->getTexture();

	// ---------------------------------------------------------
	// Type 2 : from Texture
	// ---------------------------------------------------------
	auto texture2 = 
		Director::getInstance()->getTextureCache()->addImage("Images/grossini_dance_atlas.png");

	// ---------------------------------------------------------


	auto animation = Animation::create();
	animation->setDelayPerUnit(0.3f);

	for (int i = 0; i < 14; i++) {
		//가로에 그림이 다섯개
		int column = i % 5;
		int row = i / 5;

		animation->addSpriteFrameWithTexture(
			texture1,
			Rect(column * 85, row * 121, 85, 121));
	}

	auto pMan = Sprite::create("Images/grossini_dance_atlas.png",
		Rect(0, 0, 85, 121));
	pMan->setPosition(Vec2(240, 160));
	this->addChild(pMan);

	auto animate = Animate::create(animation);
	auto rep = RepeatForever::create(animate);
	pMan->runAction(rep);

    return true;
}
