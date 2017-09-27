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
	auto pMenuItem = MenuItemFont::create(
		"Action",
		CC_CALLBACK_1(HelloWorld::doAction, this));
	pMenuItem->setColor(Color3B::BLACK);

	auto pMenu = Menu::create(pMenuItem, NULL);
	pMenu->setPosition(Vec2(240, 50));
	this->addChild(pMenu);

	pMan = Sprite::create("Images/grossini.png");
	pMan->setPosition(Vec2(50, 160));
	this->addChild(pMan);

    return true;
}

void HelloWorld::doAction(Ref* pSender) {
	pMan->removeFromParentAndCleanup(true);

	pMan = Sprite::create("Images/grossini.png");
	pMan->setPosition(Vec2(50, 160));
	this->addChild(pMan);

	//this->ActionSequence();
	//this->ActionSpawn();
	//this->ActionReverse();
	//this->ActionRepeat();
	//this->ActionRepeatForever();
	this->ActionDelayTime();
}

void HelloWorld::ActionSequence() {
	auto action = Sequence::create(
		MoveBy::create(2, Vec2(400, 0)),
		RotateBy::create(2, 540),
		NULL);

	pMan->runAction(action);
}

void HelloWorld::ActionSpawn() {
	auto action = Spawn::create(
		JumpBy::create(4, Vec2(400, 0), 50, 4),
		RotateBy::create(2, 720),
		NULL);

	pMan->runAction(action);
}

void HelloWorld::ActionReverse() {
	auto action = MoveBy::create(2, Vec2(400, 0));
	auto reverseAction = action->reverse();

	pMan->runAction(reverseAction);
}

void HelloWorld::ActionRepeat() {
	auto myActionForward = MoveBy::create(2, Vec2(400, 0));
	auto myActionBack = myActionForward->reverse();
	auto myAction = Sequence::create(myActionForward, myActionBack, NULL);

	auto rep1 = Repeat::create(myAction, 3);

	pMan->runAction(rep1);
}

void HelloWorld::ActionRepeatForever() {
	auto myActionForward = MoveBy::create(2, Vec2(400, 0));
	auto myActionBack = myActionForward->reverse();
	auto myAction = Sequence::create(myActionForward, myActionBack, NULL);

	auto rep2 = RepeatForever::create(myAction);

	pMan->runAction(rep2);
}

void HelloWorld::ActionDelayTime() {
	auto act1 = RotateTo::create(1, 150);
	auto act2 = RotateTo::create(1, 0);
	auto myAction = Sequence::create(
		act1,
		DelayTime::create(2),
		act2,
		DelayTime::create(1),
		NULL);

	auto rep2 = RepeatForever::create(myAction);

	pMan->runAction(rep2);
}