#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#pragma execution_character_set("utf-8")
#endif

#include "cocos2d.h"

class HelloWorld : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(HelloWorld);

	void createDragon();
	void setViewPointCenter(cocos2d::Vec2 position);

	void onEnter();
	void onExit();
	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);

	cocos2d::EventListenerTouchOneByOne* listener;
	cocos2d::Size			winSize;
	cocos2d::Vec2			dragonPosition;
	cocos2d::Sprite*		dragon;
	cocos2d::TMXTiledMap*	tmap;
};

#endif // __HELLOWORLD_SCENE_H__
