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

	Size winSize = Director::getInstance()->getWinSize();

	// 게임용 레이어
	gameLayer = LayerColor::create(Color4B(255, 0, 0, 255), winSize.width, winSize.height);
	gameLayer->setAnchorPoint(Vec2(0, 0));
	gameLayer->setPosition(Vec2(0, 0));
	this->addChild(gameLayer);

	// 메뉴용 레이어
	menuLayer = LayerColor::create(Color4B(0, 0, 0, 0), winSize.width, winSize.height);
	menuLayer->setAnchorPoint(Vec2(0, 0));
	menuLayer->setPosition(Vec2(0, 0));
	this->addChild(menuLayer);

	auto pMan = Sprite::create("Images/grossini.png");
	pMan->setPosition(Vec2(60, 160));
	gameLayer->addChild(pMan);

	auto myActionForward = MoveBy::create(2, Vec2(380, 0));
	auto myActionBack = myActionForward->reverse();
	auto myAction = Sequence::create(myActionForward, myActionBack, NULL);
	auto rep = RepeatForever::create(myAction);

	pMan->runAction(rep);

	auto pBack = Sprite::create("Images/minimap_back.png");
	pBack->setPosition(Vec2(400, 260));
	menuLayer->addChild(pBack);

	miniMap = RenderTexture::create(480, 320, Texture2D::PixelFormat::RGB888);
	miniMap->retain();
	miniMap->setPosition(400, 260);
	miniMap->getSprite()->setScale(0.22f);
	menuLayer->addChild(miniMap);

    return true;
}

void HelloWorld::onEnter() {
	Scene::onEnter();

	this->schedule(schedule_selector(HelloWorld::updateMinimap));
}

void HelloWorld::updateMinimap(float f) {
	miniMap->clear(0, 0, 0, 255);
	miniMap->begin();
	gameLayer->visit();
	miniMap->end();
}