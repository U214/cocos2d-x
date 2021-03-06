﻿#ifndef __HELLOWORLD_SCENE_H__
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

	cocos2d::TransitionScene* createTransition(int nIndex, float t, cocos2d::Scene* s);

	void doPushScene(Ref* pSender);
	void doPushSceneTran(Ref* pSender);
	void doReplaceScene(Ref* pSender);
	void doReplaceSceneTran(Ref* pSender);
};

#endif // __HELLOWORLD_SCENE_H__
