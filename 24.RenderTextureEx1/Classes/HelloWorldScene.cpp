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

	winSize = Director::getInstance()->getWinSize();

	// Render Texture 만들기
	m_pTarget = RenderTexture::create(winSize.width, winSize.height,
		Texture2D::PixelFormat::RGBA8888);
	m_pTarget->retain();
	m_pTarget->setPosition(Vec2(winSize.width / 2, winSize.height / 2));

	this->addChild(m_pTarget, 1);

	MenuItemFont::setFontSize(16);

	auto item1 = MenuItemFont::create("Save Image", CC_CALLBACK_1(HelloWorld::saveImage, this));
	item1->setColor(Color3B::BLACK);

	auto item2 = MenuItemFont::create("Clear", CC_CALLBACK_1(HelloWorld::clearImage, this));
	item2->setColor(Color3B::BLACK);

	auto menu = Menu::create(item1, item2, NULL);
	menu->alignItemsVertically();
	menu->setPosition(Vec2(winSize.width - 80, winSize.height - 30));

	this->addChild(menu, 3);

    return true;
}

HelloWorld::~HelloWorld() {
	m_pTarget->release();
	Director::getInstance()->getTextureCache()->removeUnusedTextures();
}

void HelloWorld::onEnter() {
	Scene::onEnter();

	listener = EventListenerTouchAllAtOnce::create();
	listener->onTouchesMoved = CC_CALLBACK_2(HelloWorld::onTouchesMoved, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void HelloWorld::onExit() { 
	_eventDispatcher->removeEventListener(listener);

	Scene::onExit();
}

void HelloWorld::onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event) {
	auto touch = touches[0];
	Vec2 start = touch->getLocation();
	Vec2 end = touch->getPreviousLocation();

	m_pTarget->begin();

	float distance = start.getDistance(end);

	if (distance > 1) {
		int d = (int)distance;
		m_pBrush.clear();

		for (int i = 0; i < d; ++i) {
			Sprite* sprite = Sprite::create("Images/brush.png");
			sprite->setColor(Color3B::RED);
			m_pBrush.pushBack(sprite);
		}

		for (int i = 0; i < d; i++) {
			float difx = end.x - start.x;
			float dify = end.y - start.y;
			float delta = (float)i / distance;
			m_pBrush.at(i)->setPosition(Vec2(start.x + (difx * delta), start.y + (dify * delta)));
			m_pBrush.at(i)->setRotation(rand() % 360);

			float r = (float)(rand() % 50 / 50.f) + 0.25f;
			m_pBrush.at(i)->setScale(r);

			//m_pBrush.at(i)->setColor(Color3B(rand() % 127 + 128, 255, 255));
			m_pBrush.at(i)->visit();
		}
	}
	m_pTarget->end();
}

void HelloWorld::saveImage(Ref* sender) {
	static int counter = 0;

	char png[20];
	sprintf(png, "image-%d.png", counter);

	/*auto callback = [&](RenderTexture* rt, const std::string& path) {
		auto sprite = Sprite::create(path);
		addChild(sprite);
		sprite->setScale(0.3f);
		sprite->setPosition(Vec2(40, 40));
		sprite->setRotation(counter * 3);

		addChild(sprite);
	};

	m_pTarget->saveToFile(png, Image::Format::PNG, true, callback);*/

	m_pTarget->saveToFile(png, Image::Format::PNG, true, nullptr);

	auto image = m_pTarget->newImage();
	auto tex = Director::getInstance()->getTextureCache()->addImage(image, png);

	CC_SAFE_DELETE(image);

	//auto sprite = Sprite::createWithTexture(tex);

	//sprite->setScale(0.3f);
	//sprite->setPosition(Vec2(40, 40));
	//sprite->setRotation(counter * 3);

	//addChild(sprite);

	Director::getInstance()->getRenderer()->render();
	std::string fullpath = FileUtils::getInstance()->getWritablePath() + png;
	log("Image saved %s", fullpath.c_str());

	counter++;
}

void HelloWorld::clearImage(Ref* sender) {
	m_pTarget->clear(255, 255, 255, 255);
}
