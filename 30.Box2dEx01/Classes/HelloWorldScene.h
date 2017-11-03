#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#pragma execution_character_set("utf-8")
#endif

#include "cocos2d.h"
#include "Box2D\/Box2D.h"

#define PTM_RATIO 32

using namespace cocos2d;

class HelloWorld : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(HelloWorld);

	~HelloWorld();

	void onEnter();
	void onExit();
	bool onTouchBegan(Touch* touch, Event* event);
	void tick(float dt);
	void addNewSpriteAtPosition(Vec2 location);

	EventListenerTouchOneByOne* listener;

	Size winSize;
	Texture2D* texture;
	b2World* _world;
};

#endif // __HELLOWORLD_SCENE_H__
