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
	
	auto pLabel1 = LabelTTF::create("Hello World", "Arial", 34);
	pLabel1->setPosition(Vec2(240, 250));
	pLabel1->setColor(Color3B(0, 0, 0));
	this->addChild(pLabel1);
	
	//비트맵 폰트
	//같은 이름의 fnt파일과 png파일이 필요하다. (사용하려는 글자도 반드시 파일 내에 있어야 함)
	auto pLabel2 = LabelBMFont::create("Hello", "futura-48.fnt");
	pLabel2->setPosition(Vec2(240, 150));
	this->addChild(pLabel2);

	//캐릭터맵 폰트
	// itemWidth, itemHeight : 글자 하나에 해당하는 크기
	// startCharMap('.') : 첫번째 이미지에 해당하는 아스키값. 
	auto pLabel3 = LabelAtlas::create("1234", "fps_images.png", 12, 32, '.');
	pLabel3->setPosition(Vec2(240, 50));
	this->addChild(pLabel3);

    return true;
}
