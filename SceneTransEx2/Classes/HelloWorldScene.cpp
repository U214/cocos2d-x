#include "HelloWorldScene.h"
#include "SecondScene.h"

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

	auto item1 = MenuItemFont::create(
		"pushScene",
		CC_CALLBACK_1(HelloWorld::doChangeScene, this));
	item1->setColor(Color3B::WHITE);

	auto pMenu = Menu::create(item1, NULL);
	pMenu->setPosition(Vec2(240, 50));
	this->addChild(pMenu);

	log("HelloWorld::init");

    return true;
}

void HelloWorld::doChangeScene(Ref* pSender) {
	auto pScene = SecondScene::createScene();
	Director::getInstance()->replaceScene(pScene);
}

void HelloWorld::onEnter() {
	Scene::onEnter();
	log("HelloWorld::onEnter");
}

void HelloWorld::onEnterTransitionDidFinish() {
	Scene::onEnterTransitionDidFinish();
	log("HelloWorld::onEnterTransitionDidFinish");
}

void HelloWorld::onExitTransitionDidStart() {
	Scene::onExitTransitionDidStart();
	log("HelloWorld::onExitTransitionDidStart");
}

void HelloWorld::onExit() {
	Scene::onExit();
	log("HelloWorld::onExit");
}

HelloWorld::~HelloWorld(void) {
	log("HelloWorld::dealloc");
}