#include "HelloWorldScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
	return HelloWorld::create();
}

bool HelloWorld::init()
{
	if (!Scene::init())
	{
		return false;
	}

	/////////////////////////////////

	this->creatBackground();

	this->createDragon();

	return true;
}

void HelloWorld::creatBackground() {
	// 배경 레이어1
	auto background1 = Sprite::create("Images/background1.png");
	background1->setAnchorPoint(Vec2(0, 0));
	background1->setPosition(Vec2(0, 0));

	// 배경 레이어1
	auto background2 = Sprite::create("Images/background2.png");
	background2->setAnchorPoint(Vec2(0, 0));
	background2->setPosition(Vec2(512, 0));

	// 배경 스프라이트를 담을 부모로 레이어를 만든다.
	auto voidNode = Layer::create();

	// 배경 스프라이트를 레이어에 넣는다
	// 배경이미지의 사이즈 : 512 x 320
	voidNode->addChild(background1);
	voidNode->addChild(background2);

	voidNode->setTag(1);

	this->addChild(voidNode, 0);
}

void HelloWorld::createDragon() {
	auto texture = Director::getInstance()->getTextureCache()
		->addImage("Images/dragon_animation.png");

	auto animation = Animation::create();
	animation->setDelayPerUnit(0.f);

	for (int i = 0; i < 6; i++) {
		int index = i % 4;
		int rowIndex = i / 4;

		animation->addSpriteFrameWithTexture(
			texture,
			Rect(index * 130, rowIndex * 140 + 70, 110, 70));
	}

	dragon = Sprite::createWithTexture(texture, Rect(0, 70, 110, 70));
	dragon->setPosition(Vec2(240, 160));
	this->addChild(dragon);

	auto animate = Animate::create(animation);
	auto rep = RepeatForever::create(animate);
	dragon->runAction(rep);
}