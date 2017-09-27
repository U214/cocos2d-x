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

	auto pMenu = Menu::create(pMenuItem, nullptr);
	pMenu->setPosition(Vec2(240, 50));
	this->addChild(pMenu);

	pBall = Sprite::create("Images/r1.png");
	pBall->setPosition(Vec2(50, 100));
	pBall->setScale(0.7f);
	this->addChild(pBall);

	pMan = Sprite::create("Images/grossini.png");
	pMan->setPosition(Vec2(50, 150));
	pMan->setScale(0.5f);
	this->addChild(pMan);

	pWomen1 = Sprite::create("Images/grossinis_sister1.png");
	pWomen1->setPosition(Vec2(50, 220));
	pWomen1->setScale(0.5f);
	this->addChild(pWomen1);

	pWomen2 = Sprite::create("Images/grossinis_sister2.png");
	pWomen2->setPosition(Vec2(50, 280));
	pWomen2->setScale(0.5f);
	this->addChild(pWomen2);

    return true;
}

void HelloWorld::doAction(Ref* pSender) {
	//Reset
	pBall->setPosition(Vec2(50, 100));
	pMan->setPosition(Vec2(50, 150));
	pWomen1->setPosition(Vec2(50, 220));
	pWomen2->setPosition(Vec2(50, 280));

	//doActionEase();
	doActionElastic();
	//doActionBounce();
	//doActionSpeed();
}

void HelloWorld::doActionEase() {
	// EaseExponential, EaseSine, EaseBack

	// 정상 속도
	auto move = MoveBy::create(3.0f, Vec2(400, 0));

	// 빨라지기 : 시작이 늦고 나중에 빠름
	auto ease_in = EaseIn::create(move->clone(), 3.0f);
	// 느려지기 : 시작이 빠르고 나중에 늦음
	auto ease_out = EaseOut::create(move->clone(), 3.0f);
	// 빨라졌다 느려지기 : 시작과 끝이 느리고 중간이 빠름
	auto ease_inout = EaseInOut::create(move->clone(), 3.0f);

	pBall->runAction(move);
	pMan->runAction(ease_in);
	pWomen1->runAction(ease_out);
	pWomen2->runAction(ease_inout);
}

void HelloWorld::doActionElastic() {
	// 정상 속도
	auto move = MoveBy::create(3.0f, Vec2(400, 0));

	// 화면 밖으로 삐져나옴
	// 탄성 ------------------------------------
	auto ease_in = EaseElasticIn::create(move->clone(), 0.4f);
	auto ease_out1 = EaseElasticOut::create(move->clone(), 0.3f);
	auto ease_out2 = EaseElasticOut::create(move->clone(), 0.4f);
	auto ease_out3 = EaseElasticOut::create(move->clone(), 0.45f);
	auto ease_inout = EaseElasticInOut::create(move->clone(), 0.4f);

	pBall->runAction(move);
	//pMan->runAction(ease_in);
	pMan->runAction(ease_out1);
	pWomen1->runAction(ease_out2);
	pWomen2->runAction(ease_out3);
	//pWomen2->runAction(ease_inout);
}

void HelloWorld::doActionBounce() {
	// 정상 속도
	auto move = MoveBy::create(3.0f, Vec2(400, 0));

	// 화면 밖을 벗어나지 않음
	// 부딫히는 과정까지 전체시간에 친다(제자리에올때까지)
	// 바운스 ------------------------------------
	auto ease_in = EaseBounceIn::create(move->clone());
	auto ease_out = EaseBounceOut::create(move->clone());
	auto ease_inout = EaseBounceInOut::create(move->clone());

	pBall->runAction(move);
	pMan->runAction(ease_in);
	pWomen1->runAction(ease_out);
	pWomen2->runAction(ease_inout);
}

void HelloWorld::doActionSpeed() {
	// 정상 속도
	auto move = MoveBy::create(3.0f, Vec2(400, 0));

	// 화면 밖을 벗어나지 않음
	// 바운스 ------------------------------------
	auto ease_in = Speed::create(move->clone(), 1.0);
	auto ease_out = Speed::create(move->clone(), 2.0);
	auto ease_inout = Speed::create(move->clone(), 3.0);

	pBall->runAction(move);
	pMan->runAction(ease_in);
	pWomen1->runAction(ease_out);
	pWomen2->runAction(ease_inout);
}