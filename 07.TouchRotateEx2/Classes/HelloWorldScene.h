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

	virtual void onEnter();
	virtual void onExit();

	void onTouchesBegan(const std::vector<cocos2d::Touch*> touches, cocos2d::Event* event);
	void onTouchesMoved(const std::vector<cocos2d::Touch*> touches, cocos2d::Event* event);
	void onTouchesEnded(const std::vector<cocos2d::Touch*> touches, cocos2d::Event* event);

	cocos2d::Sprite* pMan;
	cocos2d::LabelTTF* pLabel1;
	cocos2d::LabelTTF* pLabel2;

	bool bSelect;
	int i;
	float gRotation;
};

#endif // __HELLOWORLD_SCENE_H__
