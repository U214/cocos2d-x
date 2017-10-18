#include "HelloWorldScene.h"

USING_NS_CC;
using namespace ui;

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

	// 위치 구분용 스프라이트
	auto sprite1 = Sprite::create("Images/grossini.png");
	auto sprite2 = Sprite::create("Images/grossinis_sister1.png");

	sprite1->setPosition(Vec2(40, 80));
	sprite2->setPosition(Vec2(920, 80));

	// 스크롤 뷰를 구분해서 보여주기 위한 레이어
	auto layer = LayerColor::create(Color4B(255, 0, 255, 255));
	layer->setAnchorPoint(Vec2::ZERO);
	layer->setPosition(Vec2(0, 0));
	layer->setContentSize(Size(960, 160));

	layer->addChild(sprite1);
	layer->addChild(sprite2);

	auto scrollView = ScrollView::create();

	scrollView->setSize(Size(480, 160));
	scrollView->setInnerContainerSize(layer->getContentSize());
	// 스크롤이 가능한 방향을 지정한다.
	scrollView->setDirection(ScrollView::Direction::HORIZONTAL);
	scrollView->addChild(layer);
	// 스크롤시 끝에 도달하면 바운스를 할 것인지를 정한다.
	scrollView->setBounceEnabled(true);
	// 스크롤바가 자동으로 사라지게 할 것인지를 정한다.
	scrollView->setScrollBarAutoHideEnabled(true);
	// 이벤트 발생시 처리할 메서드를 등록한다.
	scrollView->addEventListener(CC_CALLBACK_2(HelloWorld::scrollEvent, this));
	// 스크롤이 될 대상의 스크롤뷰 안에서의 현재 위치를 지정한다.
	scrollView->jumpToPercentHorizontal(50);
	scrollView->setPosition(Vec2(0, 100));
	this->addChild(scrollView);

    return true;
}

void HelloWorld::scrollEvent(Ref* pSender, cocos2d::ui::ScrollView::EventType event) {
	switch (event)
	{
	case cocos2d::ui::ScrollView::EventType::BOUNCE_TOP:
		log("BOUNCE_TOP");
		break;

	case cocos2d::ui::ScrollView::EventType::BOUNCE_BOTTOM:
		log("BOUNCE_BOTTOM");
		break;

	case cocos2d::ui::ScrollView::EventType::BOUNCE_LEFT:
		log("BOUNCE_LEFT");
		break;

	case cocos2d::ui::ScrollView::EventType::BOUNCE_RIGHT:
		log("BOUNCE_RIGHT");
		break;

	case cocos2d::ui::ScrollView::EventType::CONTAINER_MOVED:
		//log("CONTAINER_MOVED");
		break;

	case cocos2d::ui::ScrollView::EventType::SCROLLING:
		//log("SCROLLING");
		break;
	}
}