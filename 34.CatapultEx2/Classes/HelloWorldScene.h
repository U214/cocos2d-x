#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#pragma execution_character_set("utf-8")
#endif

#include "cocos2d.h"
#include "Box2D\Box2D.h"
#include <GLES-Render.h>

#define PTM_RATIO 32
#define FLOOR_HEIGHT 62.0f

using namespace cocos2d;

class HelloWorld : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(HelloWorld);

	EventListenerTouchOneByOne* listener;

	Size winSize;
	Texture2D* texture;
	b2World* _world;

	// For debugging
	GLESDebugDraw* m_debugDraw;
	CustomCommand _customCommand;

	bool				bDrag;
	b2Body				*dragBody;
	b2MouseJoint		*mouseJoint;
	b2Body				*gbody;
	b2Body				*groundBody;

	bool				releasingArm;

	b2Fixture*			armFixture;
	b2Body*				armBody;
	b2RevoluteJoint*	armJoint;
	b2Body*				bulletBody;
	b2WeldJoint*		bulletJoint;

	bool createBox2dWorld(bool debug);
	void setBox2dWorld();
	~HelloWorld();
	void tick(float dt);

	virtual void draw(Renderer* renderer, const Mat4& transform, 
		uint32_t flags) override;
	void onDraw(const Mat4& transform, uint32_t flags);

	void onEnter();
	void onExit();
	bool onTouchBegan(Touch* touch, Event* event);
	void onTouchMoved(Touch* touch, Event* event);
	void onTouchEnded(Touch* touch, Event* event);

	b2Body* addNewSprite(Vec2 point, Size size, b2BodyType bodytype,
		const char* spriteName, int type);
	b2Body* getBodyAtTab(Vec2 point);

	void attachBullet();
	//void doReset(Ref* pSender);
};

#endif // __HELLOWORLD_SCENE_H__
