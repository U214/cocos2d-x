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


	MenuItemFont::setFontSize(28);

	auto pMenuItem = MenuItemFont::create(
		"Action",
		CC_CALLBACK_1(HelloWorld::doAction, this));
	pMenuItem->setColor(Color3B::BLACK);

	auto pMenu = Menu::create(pMenuItem, nullptr);
	pMenu->setPosition(Vec2(240, 50));
	this->addChild(pMenu);

	pMan = Sprite::create("Images/grossini.png");
	pMan->setPosition(Vec2(50, 230));
	this->addChild(pMan);

	pWoman = Sprite::create("Images/grossinis_sister1.png");
	pWoman->setPosition(Vec2(50, 110));
	this->addChild(pWoman);

    return true;
}

void HelloWorld::doAction(Ref* pSender) {
	//doActionMove();
	//doActionJump();
	//doActionRotate();
	//doActionScale();
	//doActionTint();
	//
	//doActionPlace();
	//doActionBlink();
	//doActionShow();
	doActionFadeInOut();
}

void HelloWorld::doActionMove() {
	//	by는 현재 값에서 지정한 값만큼 변하는 액션 수행
	//	to는 지정한 값으로 변하는 액션 수행

	auto myActionTo = MoveTo::create(2, Vec2(400, 0));
	auto myActionBy = MoveBy::create(2, Vec2(400, 0));

	pMan->runAction(myActionTo);
	pWoman->runAction(myActionBy);
}

void HelloWorld::doActionJump() {
	auto myActionTo = JumpTo::create(2, Vec2(400, 0), 50, 3);
	auto myActionBy = JumpBy::create(2, Vec2(400, 0), 50, 3);

	pMan->runAction(myActionTo);
	pWoman->runAction(myActionBy);
}

void HelloWorld::doActionRotate() {
	// RotateTo : 결과에 가까운 쪽으로 최소한으로 회전한다 180, 270
	// RotateBy : 적힌 숫자만큼 시계방향으로 회전한다. 180, 270, 540

	auto myActionTo = RotateTo::create(2, 270);
	auto myActionBy = RotateBy::create(2, 270);

	pMan->runAction(myActionTo);
	pWoman->runAction(myActionBy);
}

void HelloWorld::doActionScale() {
	auto myActionTo = ScaleTo::create(2, 2.0);
	auto myActionBy = ScaleBy::create(2, 2.0);

	pMan->runAction(myActionTo);
	pWoman->runAction(myActionBy);
}

void HelloWorld::doActionTint() {
	// 메뉴를 두 번 클릭해서 테스트
	auto myActionTo = TintTo::create(2, 128, 128, 128);
	auto myActionBy = TintBy::create(2, 128, 128, 128);

	pMan->runAction(myActionTo);
	pWoman->runAction(myActionBy);
}

void HelloWorld::doActionPlace() {
	// 단독 액션들 : Place는 reverse() 액션이 없다.

	auto myAction = Place::create(Vec2(300, 200));

	pMan->runAction(myAction);
}

void HelloWorld::doActionBlink() {
	auto myAction = Blink::create(2, 5);

	pMan->runAction(myAction);
}

void HelloWorld::doActionShow() {
	if (pMan->isVisible()) {
		auto myAction = Hide::create();
		pMan->runAction(myAction);
	}
	else {
		auto myAction = Show::create();
		pMan->runAction(myAction);
	}

	//if (pMan->isVisible()) {
	//	pMan->setVisible(false);
	//}
	//else {
	//	pMan->setVisible(true);
	//}
}

void HelloWorld::doActionFadeInOut() {
	/*if (pMan->getOpacity() == 0) {
		auto myAction = FadeIn::create(1.5);
		pMan->runAction(myAction);
	}
	else {
		auto myAction = FadeOut::create(1.5);
		pMan->runAction(myAction);
	}*/
	
	auto myAction = FadeTo::create(1.5, 0);
	pMan->runAction(myAction);
}

/*
MoveTo		: 리버스 액션 동작 안함
JumpTo		: 리버스 액션 에러남
RotateTo	: 리버스 액션 에러남
ScaleTo		: 리버스 액션 에러남
TintTo		: 리버스 액션 에러남
*/


