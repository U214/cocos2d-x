#include "HelloWorldScene.h"
#include "SecondScene.h"

USING_NS_CC;

Scene* SecondScene::createScene()
{
	return SecondScene::create();
}

bool SecondScene::init()
{
	if (!Scene::init())
	{
		return false;
	}

	/////////////////////////////////

	auto item1 = MenuItemFont::create(
		"Close Scene 2",
		CC_CALLBACK_1(SecondScene::doClose, this));
	item1->setColor(Color3B::WHITE);

	auto pMenu = Menu::create(item1, NULL);
	pMenu->setPosition(Vec2(240, 50));
	this->addChild(pMenu);

	log("SecondScene::init");

	return true;
}

void SecondScene::onEnter() {
	Scene::onEnter();
	log("SecondScene::onEnter");
}

void SecondScene::onEnterTransitionDidFinish() {
	Scene::onEnterTransitionDidFinish();
	log("SecondScene::onEnterTransitionDidFinish");
}

void SecondScene::onExitTransitionDidStart() {
	Scene::onExitTransitionDidStart();
	log("SecondScene::onExitTransitionDidStart");
}

void SecondScene::onExit() {
	Scene::onExit();
	log("SecondScene::onExit");
}

SecondScene::~SecondScene(void) {
	log("SecondScene::dealloc");
}

void SecondScene::doClose(Ref* pSender) {
	auto pScene = HelloWorld::createScene();
	Director::getInstance()->replaceScene(pScene);
}