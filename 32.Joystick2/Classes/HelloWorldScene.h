#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#pragma execution_character_set("utf-8")
#endif

#define PTM_RATIO 32

#include "cocos2d.h"
#include "Box2D\Box2D.h"
#include <GLES-Render.h>
#include "Joystick.h"

class HelloWorld : 
	public cocos2d::Scene
	, public b2ContactListener
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(HelloWorld);

	Joystick* joystick;
	void tick(float dt);

	Size winSize;
	b2World* _world;

	bool createBox2dWorld(bool debug);
	b2Body* addNewSprite(Vec2 point, Size size, b2BodyType bodytype,
		const char* spriteName, int type);
};

#endif // __HELLOWORLD_SCENE_H__
