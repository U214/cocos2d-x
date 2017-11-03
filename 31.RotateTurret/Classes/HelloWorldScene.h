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

	cocos2d::Size winSize;
	cocos2d::Sprite* player;
	cocos2d::Vector<cocos2d::Sprite*> projectiles;
	bool bProjectile;

	virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	void finishRotate(Ref* sender, cocos2d::Vec2 dir);
	void spriteMoveFinished(Ref* sender);
};

#endif // __HELLOWORLD_SCENE_H__
