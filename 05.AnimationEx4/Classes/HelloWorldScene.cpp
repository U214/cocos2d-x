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
	auto cache = SpriteFrameCache::getInstance();

	cache->addSpriteFramesWithFile("animations/grossini_family.xml");
	cache->addSpriteFramesWithFile("animations/grossini.xml");

	auto pSprite = SpriteFrame::create("Images/blocks9.png", Rect(0, 0, 96, 96));
	cache->addSpriteFrame(pSprite, "blocks9.png");

	auto pWoman = Sprite::createWithSpriteFrameName("grossinis_sister1.png");
	pWoman->setPosition(Vec2(120, 220));
	this->addChild(pWoman);

	auto pMan = Sprite::createWithSpriteFrameName("grossini_dance_01.png");
	pMan->setPosition(Vec2(240, 220));
	this->addChild(pMan);

	auto pBox = Sprite::createWithSpriteFrameName("blocks9.png");
	pBox->setPosition(Vec2(360, 220));
	this->addChild(pBox);

	// TextureCache는 파일 이름을 키값으로 메모리에 텍스쳐를 저장한다
	// 이후 같으 ㄴ파일을 부르면 파일 IO를 발생시ㅣ지 않고
	// 메모리에서 텍스쳐를 리턴한다

	auto texture1 = Director::getInstance()->getTextureCache()->addImage("Images/grossini_dance_atlas.png");

	auto texture2 = Director::getInstance()->getTextureCache()->addImage("animations/dragon_animation.png");

	auto pMan2 = Sprite::createWithTexture(texture1, Rect(0, 0, 85, 121));
	pMan2->setPosition(Vec2(120, 100));
	this->addChild(pMan2);

	auto pDragon = Sprite::createWithTexture(texture2, Rect(0, 0, 130, 140));
	pDragon->setPosition(Vec2(240, 100));
	this->addChild(pDragon);

	Director::getInstance()->getTextureCache()->addImageAsync(
		"Images/blocks9.png",
		CC_CALLBACK_1(HelloWorld::imageLoaded, this));

    return true;
}

void HelloWorld::imageLoaded(Ref* pSender) {
	auto tex = static_cast<Texture2D*>(pSender);
	auto sprite = Sprite::createWithTexture(tex);
	sprite->setPosition(Vec2(360, 100));
	
	this->addChild(sprite);

	log("Image loaded: %p", pSender);
}