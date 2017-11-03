#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#pragma execution_character_set("utf-8")
#endif

#include "cocos2d.h"
#include "Box2D\Box2D.h"
#include <GLES-Render.h>

#define PTM_RATIO 32

using namespace cocos2d;

class VRope;

class HelloWorld 
	: public cocos2d::Scene
	, public b2ContactListener
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(HelloWorld);

	EventListenerTouchOneByOne* listener;
	CustomCommand _customCommand;
	b2Body* groundBody;

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

	b2Body* createCandyAt(Vec2 location);
	void createRope(b2Body* bodyA, b2Vec2 anchorA, b2Body* bodyB, b2Vec2 anchorB, float32 sag);
	bool checkLineIntersection(Vec2 p1, Vec2 p2, Vec2 p3, Vec2 p4);
	b2Body* createRopeTipBody();

	void BeginContact(b2Contact* contact);
	void PreSolve(b2Contact* contact, const b2Manifold* oldManifold);

private:
	Size winSize;
	Texture2D* texture;
	b2World* _world;
	GLESDebugDraw* m_debugDraw;

	std::vector<VRope *>*	ropes;
	SpriteBatchNode*		ropeSpriteSheet;

	Sprite*					candySprite;
	Sprite*					croc_;
	b2Body*					crocMouth_;
	bool					crocMouthOpened;
};

#endif // __HELLOWORLD_SCENE_H__
