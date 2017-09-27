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

	auto pMenuItem1 = MenuItemImage::create(
		"Images/btn-play-normal.png",
		"Images/btn-play-selected.png",
		CC_CALLBACK_1(HelloWorld::doClick1, this));

	auto pMenuItem2 = MenuItemImage::create(
		"Images/btn-highscores-normal.png",
		"Images/btn-highscores-selected.png",
		CC_CALLBACK_1(HelloWorld::doClick2, this));

	auto pMenuItem3 = MenuItemImage::create(
		"Images/btn-about-normal.png",
		"Images/btn-about-selected.png",
		CC_CALLBACK_1(HelloWorld::doClick3, this));

	auto pMenu = Menu::create(pMenuItem1, pMenuItem2, pMenuItem3, NULL);
	pMenu->alignItemsVertically();
	this->addChild(pMenu);

    return true;
}

void HelloWorld::doClick1(Ref* pSender) {
	log("첫번째 메뉴가 선택되었습니다.");
}

void HelloWorld::doClick2(Ref* pSender) {
	log("두번째 메뉴가 선택되었습니다.");
}

void HelloWorld::doClick3(Ref* pSender) {
	log("세번째 메뉴가 선택되었습니다.");
}