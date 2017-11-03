#include "HelloWorldScene.h"
#include <cstdlib>
#include <ctime>

USING_NS_CC;

Scene* HelloWorld::createScene()
{
	return HelloWorld::create();
}

bool HelloWorld::init()
{
	if (!Scene::init())
	{
		return false;
	}

	/////////////////////////////////
	winSize = Director::getInstance()->getWinSize();
	texture = Director::getInstance()->getTextureCache()->addImage("blocks.png");

	if (this->createBox2dWorld(true)) {
	_world->SetContactListener((b2ContactListener *)this);

		srand((int)time(nullptr));
		this->setBox2dWorld();
		this->schedule(schedule_selector(HelloWorld::tick));
	}

	return true;
}

bool HelloWorld::createBox2dWorld(bool debug) {
	////////////////////////// 월드 생성 시작

	//중력의 방향 결정
	b2Vec2 gravity = b2Vec2(0.0f, -30.0f);

	// 월드 생성
	_world = new b2World(gravity);
	_world->SetAllowSleeping(true);
	_world->SetContinuousPhysics(true);

	// 디버그 드로잉 설정
	if (debug) {
		m_debugDraw = new GLESDebugDraw(PTM_RATIO);
		_world->SetDebugDraw(m_debugDraw);

		uint32 flags = 0;
		flags += b2Draw::e_shapeBit;
		flags += b2Draw::e_jointBit;
		//flags += b2Draw::e_aabbBit;
		//flags += b2Draw::e_pairBit;
		//flags += b2Draw::e_centerOfMassBit;
		m_debugDraw->SetFlags(flags);
	}

	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0, 0);
	b2Body *groundBody = _world->CreateBody(&groundBodyDef);

	b2EdgeShape groundEdge;
	b2FixtureDef boxShapeDef;
	boxShapeDef.shape = &groundEdge;

	// 아래
	groundEdge.Set(b2Vec2(0, 0), b2Vec2(winSize.width * 2 / PTM_RATIO, 0));
	groundBody->CreateFixture(&boxShapeDef);

	// 왼쪽
	groundEdge.Set(b2Vec2(0, 0), b2Vec2(0, winSize.height / PTM_RATIO));
	groundBody->CreateFixture(&boxShapeDef);

	// 위쪽
	groundEdge.Set(
		b2Vec2(0, winSize.height / PTM_RATIO),
		b2Vec2(winSize.width / PTM_RATIO, winSize.height / PTM_RATIO));
	groundBody->CreateFixture(&boxShapeDef);

	//// 오른쪽
	//groundEdge.Set(
	//	b2Vec2(winSize.width / PTM_RATIO, winSize.height / PTM_RATIO),
	//	b2Vec2(winSize.width / PTM_RATIO, 0));
	//groundBody->CreateFixture(&boxShapeDef);

	///////////////////////////// 월드 생성 끝

	return true;
}

void HelloWorld::setBox2dWorld() {
	Sprite* bg1 = Sprite::create("background1.png");
	bg1->setPosition(Vec2::ZERO);
	bg1->setAnchorPoint(Vec2::ZERO);
	this->addChild(bg1);

	myBall = this->addNewSprite(Vec2(25, 50), Size(50, 50), b2_dynamicBody, "test", 0);
	Sprite* myBallSprite = (Sprite*)myBall->GetUserData();
	Rect myBoundary = Rect(0, 0, winSize.width * 2, winSize.height);

	this->runAction(Follow::create(myBallSprite, myBoundary));

	float start = winSize.width * 2 - 130;

	struct BLOCK {
		Vec2 point;
		Size size;
	};

	int const numBlocks = 6;
	struct BLOCK blocks[numBlocks] =
	{
		{ Vec2(start, 50), Size(10, 100) },
		{ Vec2(start + 50, 50), Size(10, 100) },
		{ Vec2(start + 25, 100 + 5), Size(200, 10) },
		{ Vec2(start, 120 + 50), Size(10, 100) },
		{ Vec2(start + 50, 120 + 50), Size(10, 100) },
		{ Vec2(start + 25, 220 + 50), Size(200, 100) },
	};
	
	for (int i = 0; i < numBlocks; i++) {
		this->addNewSprite(blocks[i].point, blocks[i].size, b2_dynamicBody, "test", 0);
	}
}

HelloWorld::~HelloWorld() {
	delete _world;
	_world = NULL;
}

void HelloWorld::onEnter() {
	Scene::onEnter();

	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);

	listener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
	listener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void HelloWorld::onExit() {
	_eventDispatcher->removeEventListener(listener);
	Scene::onExit();
}

void HelloWorld::tick(float dt) {
	int velocityIterations = 8;
	int positionIterations = 3;

	// Step : 물리 세계를 시뮬레이션 한다
	_world->Step(dt, velocityIterations, positionIterations);

	for (b2Body *b = _world->GetBodyList(); b; b = b->GetNext()) {
		if (b->GetUserData() != NULL) {
			Sprite* spriteData = (Sprite*)b->GetUserData();
			spriteData->setPosition(Vec2(
				b->GetPosition().x * PTM_RATIO,
				b->GetPosition().y * PTM_RATIO));
			spriteData->setRotation(-1 * CC_RADIANS_TO_DEGREES(b->GetAngle()));
		}
	}
}

void HelloWorld::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags)
{
	Scene::draw(renderer, transform, flags);

	_customCommand.init(_globalZOrder, transform, flags);
	_customCommand.func = CC_CALLBACK_0(HelloWorld::onDraw, this, transform, flags);
	renderer->addCommand(&_customCommand);
}

b2Body* HelloWorld::addNewSprite(Vec2 point, Size size, b2BodyType bodytype,
	const char* spriteName, int type) {
	b2BodyDef bodyDef;
	bodyDef.type = bodytype;
	bodyDef.position.Set(point.x / PTM_RATIO, point.y / PTM_RATIO);

	if (spriteName) {
		if (strcmp(spriteName, "test") == 0) {
			int idx = (CCRANDOM_0_1() > .5 ? 0 : 1);
			int idy = (CCRANDOM_0_1() > .5 ? 0 : 1);
			Sprite* sprite = Sprite::createWithTexture(texture,
				Rect(32 * idx, 32 * idy, 32, 32));
			sprite->setPosition(point);
			this->addChild(sprite);

			bodyDef.userData = sprite;
		}
		else {
			Sprite* sprite = Sprite::create(spriteName);
			sprite->setPosition(point);
			this->addChild(sprite);
			bodyDef.userData = sprite;
		}
	}

	b2Body* body = _world->CreateBody(&bodyDef);

	b2FixtureDef fixtureDef;
	b2CircleShape circle;
	b2PolygonShape dynamicBox;

	if (type == 0) {
		dynamicBox.SetAsBox(size.width / 2 / PTM_RATIO, size.height / 2 / PTM_RATIO);
		fixtureDef.shape = &dynamicBox;
	}
	else {
		circle.m_radius = (size.width / 2) / PTM_RATIO;
		fixtureDef.shape = &circle;
	}

	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;
	fixtureDef.restitution = 0.f;

	body->CreateFixture(&fixtureDef);

	return body;
}

b2Body* HelloWorld::getBodyAtTab(Vec2 point) {
	b2Fixture *fix;
	for (b2Body *b = _world->GetBodyList(); b; b = b->GetNext()) {
		if (b->GetUserData() != NULL) {
			if (b->GetType() == b2_staticBody) continue;

			fix = b->GetFixtureList();
			if (fix->TestPoint(b2Vec2(point.x / PTM_RATIO, point.y / PTM_RATIO))) {
				return b;
			}
		}
	}
	return NULL;
}

bool HelloWorld::onTouchBegan(Touch* touch, Event* event) {
	Vec2 touchPoint = touch->getLocation();
	Vec2 touchPoint2 = Node::convertToNodeSpace(touchPoint);

	b2Body* tBall = this->getBodyAtTab(touchPoint2);

	bBallTouch = false;

	if (tBall == myBall) {
		log("touch start");
		bBallTouch = true;
		startPoint = b2Vec2(touchPoint2.x / PTM_RATIO, touchPoint2.y / PTM_RATIO);
	}

	return true;
}

void HelloWorld::onTouchEnded(Touch* touch, Event* event) {
	Vec2 touchPoint = touch->getLocation();
	Vec2 touchPoint2 = Node::convertToNodeSpace(touchPoint);

	if (myBall && bBallTouch) {
		log("touch end...");
		endPoint = b2Vec2(touchPoint2.x / PTM_RATIO, touchPoint2.y / PTM_RATIO);

		b2Vec2 force = endPoint - startPoint;

		force.x *= 250.0f;
		force.y *= 250.0f;

		myBall->ApplyForceToCenter(force, true);
		bBallTouch = false;
	}
}

void HelloWorld::onDraw(const Mat4 &transform, uint32_t flags)
{
	Director* director = Director::getInstance();
	CCASSERT(nullptr != director, "Director is null when seting matrix stack");
	director->pushMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
	director->loadMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW, transform);

	GL::enableVertexAttribs(cocos2d::GL::VERTEX_ATTRIB_FLAG_POSITION);
	_world->DrawDebugData();
	CHECK_GL_ERROR_DEBUG();

	director->popMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
}

