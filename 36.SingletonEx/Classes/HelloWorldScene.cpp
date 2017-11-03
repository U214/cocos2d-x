#include "HelloWorldScene.h"
#include "SecondScene.h"
#include "GameManager.h"

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
    
	auto wlayer = LayerColor::create(Color4B(0, 255, 0, 255));
	this->addChild(wlayer);

	/////////////////////////////

	auto item1 = MenuItemFont::create(
		"pushScene", CC_CALLBACK_1(HelloWorld::doChangeScene, this));
	item1->setColor(Color3B::BLACK);

	auto pMenu = Menu::create(item1, NULL);
	this->addChild(pMenu);

	log("HelloWorld :: init");
  
    return true;
}

void HelloWorld::doChangeScene(Ref* pSender)
{
	GameManager::getInstance()->setCount(5);
	
	auto pScene = SecondScene::createScene(5);
	Director::getInstance()->replaceScene(pScene);

}

