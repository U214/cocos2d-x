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

	auto pMenuItem1 = MenuItemFont::create(
		"Menu-1",
		CC_CALLBACK_1(HelloWorld::doClick, this));
	pMenuItem1->setColor(Color3B(0, 0, 0));

	auto pMenuItem2 = MenuItemFont::create(
		"Menu-2",
		CC_CALLBACK_1(HelloWorld::doClick, this));
	pMenuItem2->setColor(Color3B(0, 0, 0));

	pMenuItem1->setTag(1);
	pMenuItem2->setTag(2);

	auto pMenu = Menu::create(pMenuItem1, pMenuItem2, NULL);
	pMenu->alignItemsVertically();
	this->addChild(pMenu);

    return true;
}

void HelloWorld::doClick(Ref* pSender) {
	auto tItem = (MenuItem *)pSender;
	int i = tItem->getTag();

	if (i == 1) {
		auto pMan = Sprite::create("Images/grossini.png");
		pMan->setPosition(Vec2(100, 160));
		pMan->setTag(11);
		this->addChild(pMan);
	}
	else {
		auto pMan = (Sprite*)getChildByTag(11);
		//태그는 중복으로 줄 수 있으니까 반드시 뭐가 올지 형변환을 하자
		this->removeChild(pMan, true);
		//true : 객체가 무슨 동작을 하고 있을때 멈추고 제거하라는 것
		// this->removeChildByTag(11, true);
	}
}