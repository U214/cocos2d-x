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

	cocos2d::Sprite* sprite1;
	cocos2d::Sprite* sprite2;
	cocos2d::Sprite* sprite3;

	virtual void onEnter();
	virtual void onExit();
	void reZorder(cocos2d::Sprite* pSender);
};

#endif // __HELLOWORLD_SCENE_H__
