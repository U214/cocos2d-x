#include "HelloWorldScene.h"
#include "SecondScene.h"
#include "GameManager.h"

USING_NS_CC;

Scene* SecondScene::createScene(int num)
{
	return SecondScene::create(num);
}

SecondScene* SecondScene::create(int num)
{
	SecondScene *pRet = new(std::nothrow) SecondScene();
	if (pRet && pRet->init(num))
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = nullptr;
		return nullptr;
	}
};

bool SecondScene::init(int num)
{

	if (!Scene::init())
	{
		return false;
	}

	auto wlayer = LayerColor::create(Color4B(0, 0, 255, 255));
	this->addChild(wlayer);

	/////////////////////////////

	auto item1 = MenuItemFont::create(
		"Close Scene", CC_CALLBACK_1(SecondScene::doClose, this));
	item1->setColor(Color3B::GREEN);

	auto pMenu = Menu::create(item1, NULL);
	pMenu->setPosition(Vec2(240, 50));
	this->addChild(pMenu);

	int count = GameManager::getInstance()->getCount();

	log("SecondScene :: init %d... %d", num, count);

	return true;
}

void SecondScene::doClose(Ref* pSender)
{
	auto pScene = HelloWorld::createScene();
	Director::getInstance()->replaceScene(pScene);
}