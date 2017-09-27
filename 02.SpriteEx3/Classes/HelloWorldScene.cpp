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
	// 1. 스프라이트의 색 지정
	// 2. 스프라이트의 여러가지 속성 지정
	
	auto parent = Sprite::create("Images/grossini.png");
	//parent->setTextureRect(Rect(0, 0, 150, 150));
	parent->setPosition(Vec2(300, 300));
	//parent->setColor(Color3B(0, 0, 255));

	//parent->setScale(2.0f);						//이미지의 사이즈 설정
	//parent->setOpacity(0);						//투명도 설정 255 * 0.7 (0이 투명)
	parent->setAnchorPoint(Vec2(0, 0));		//이미지의 출력 중심점을 설정
	//parent->setVisible(true);						//이미지 보여줄건지 설정
	parent->setRotation(90.0f);					//이미지 회전, degree기준(90.0f = 90도)
	//parent->setFlippedX(true);					//이미지를 x축으로 뒤집어 보여줄건지를 설정

	this->addChild(parent);

    return true;
}
