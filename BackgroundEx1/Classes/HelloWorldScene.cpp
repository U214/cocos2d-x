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
    
	/////////////////////////////////

	// 배경 스프라이트를 담을 부모로 레이어를 만든다.
	auto voidNode = Layer::create();
	this->addChild(voidNode);

	// 배경 레이어1
	auto background1 = Sprite::create("Images/background1.png");
	background1->setAnchorPoint(Vec2(0, 0));
	background1->setPosition(Vec2(0, 0));

	// 배경 레이어1
	auto background2 = Sprite::create("Images/background2.png");
	background2->setAnchorPoint(Vec2(0, 0));
	background2->setPosition(Vec2(512, 0));

	// 이미지가 만나는 가장자리(edge)에 검은선이 생기는 현상을 방지하기 위하여
	// Anti-Aliasing을 끈다
	background1->getTexture()->setAliasTexParameters();
	background2->getTexture()->setAliasTexParameters();

	// 배경 스프라이트를 레이어에 넣는다
	// 배경이미지의 사이즈 : 512 x 320
	voidNode->addChild(background1);
	voidNode->addChild(background2);

	auto go = MoveBy::create(4, Vec2(-512, 0));
	auto goBack = go->reverse();
	auto seq = Sequence::create(go, goBack, NULL);
	auto act = RepeatForever::create(seq);

	voidNode->runAction(act);

    return true;
}
