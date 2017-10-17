#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#pragma execution_character_set("utf-8")
#endif

#include "cocos2d.h"
#include "network/HttpClient.h"

class HelloWorld : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(HelloWorld);

	void onGetTest(Ref* sender);
	void onPostTest(Ref* sender);

	void onHttpRequestCompleted(
		cocos2d::network::HttpClient* sender,
		cocos2d::network::HttpResponse* response);

	cocos2d::LabelTTF* lblStatusCode;
};

#endif // __HELLOWORLD_SCENE_H__
