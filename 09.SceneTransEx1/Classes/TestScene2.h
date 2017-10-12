#ifndef __TESTSCENE2_SCENE_H_
#define __TESTSCENE2_SCENE_H__

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#pragma execution_character_set("utf-8")
#endif

#include "cocos2d.h"

class TestScene2 : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(TestScene2);
};

#endif // __HELLOWORLD_SCENE_H__
