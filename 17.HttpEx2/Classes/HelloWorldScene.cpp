#include "HelloWorldScene.h"
#include "network/HttpClient.h"

USING_NS_CC;
using namespace cocos2d::network;

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
	auto request = new HttpRequest();
	request->setUrl("http://www.cocos2d-x.org/images/logo.png");
	request->setRequestType(HttpRequest::Type::GET);
	request->setResponseCallback([&](HttpClient* sender, HttpResponse* response) {
		if (!response->isSucceed()) {
			log("error");
			return;
		}

		std::vector<char>* buffer = response->getResponseData();
		std::string path = FileUtils::getInstance()->getWritablePath() + "image.png";
		FILE* fp = fopen(path.c_str(), "wb");
		fwrite(buffer->data(), 1, buffer->size(), fp);
		fclose(fp);

		auto size = Director::getInstance()->getWinSize();
		auto sprite = Sprite::create(path);
		sprite->setPosition(size / 2);
		this->addChild(sprite);
	});

	network::HttpClient::getInstance()->send(request);
	request->release();

    return true;
}
