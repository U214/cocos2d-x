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

	auto pMenuItem = MenuItemImage::create(
		"Images/btn-play-normal.png",
		"Images/btn-play-selected.png",
		CC_CALLBACK_1(HelloWorld::menuSelect, this));

	pMenuItem->setPosition(Vec2(100, 100));
	// 부모인 pMenu를 기준으로 위치되는 좌표
	// 부모가 0,0일때 0+100, 0+100 이고
	// 부모가 디폴트값(중간)일때 중간+100 중간+100 이다

	auto pMenu = Menu::create(pMenuItem, NULL);
	//pMenu->setPosition(Vec2::ZERO);

	this->addChild(pMenu);

    return true;
}

void HelloWorld::menuSelect(Ref* pSender) {
	log("메뉴가 선택되었습니다.");
}