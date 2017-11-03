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

	// 오른쪽
	groundEdge.Set(
		b2Vec2(winSize.width / PTM_RATIO, winSize.height / PTM_RATIO),
		b2Vec2(winSize.width / PTM_RATIO, 0));
	groundBody->CreateFixture(&boxShapeDef);

	///////////////////////////// 월드 생성 끝

	return true;
}

void HelloWorld::setBox2dWorld() {
	playerIsFlying = false;

	Sprite* pSprite1 = Sprite::createWithTexture(texture, Rect(0, 0, 64, 64));
	pSprite1->setPosition(Vec2(winSize.width / 2, winSize.height / 2));
	this->addChild(pSprite1);

	b2BodyDef bodyDef1;
	bodyDef1.type = b2_staticBody;
	bodyDef1.position.Set(winSize.width / 2 / PTM_RATIO, winSize.height / 2 / PTM_RATIO);
	bodyDef1.userData = pSprite1;

	b2Body* body1 = _world->CreateBody(&bodyDef1);

	b2PolygonShape staticBox;
	staticBox.SetAsBox((pSprite1->getContentSize().width / 2) / PTM_RATIO,
		(pSprite1->getContentSize().height / 2) / PTM_RATIO);

	b2FixtureDef fixtureDef1;
	fixtureDef1.shape = &staticBox;
	fixtureDef1.density = 1.0f;

	body1->CreateFixture(&fixtureDef1);

	addNewSpriteAtPosition(Vec2(240, 100));
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

	_customCmd.init(_globalZOrder, transform, flags);
	_customCmd.func = CC_CALLBACK_0(HelloWorld::onDraw, this, transform, flags);
	renderer->addCommand(&_customCmd);
}

void HelloWorld::addNewSpriteAtPosition(Vec2 location) {
	Sprite* pea = Sprite::create("pea.png");
	pea->setPosition(location);
	this->addChild(pea);

	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(location.x / PTM_RATIO, location.y / PTM_RATIO);

	bodyDef.userData = pea;

	myBall = _world->CreateBody(&bodyDef);

	b2CircleShape circle;
	circle.m_radius = 0.45f;

	b2FixtureDef fixtureDef;

	fixtureDef.shape = &circle;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.2f;
	fixtureDef.restitution = 0.6f;

	myBall->CreateFixture(&fixtureDef);
}

bool HelloWorld::onTouchBegan(Touch* touch, Event* event) {
	playerVelocity = 0.5f;
	playerIsFlying = true;

	return true;
}

void HelloWorld::onTouchEnded(Touch* touch, Event* event) {
	playerIsFlying = false;
	playerVelocity = 0.f;
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

void HelloWorld::BeginContact(b2Contact* contact) {
}

void HelloWorld::PreSolve(b2Contact* contact, const b2Manifold* oldManifold) {
	b2Fixture *fixA = contact->GetFixtureA(); // 맞은애
	b2Fixture *fixB = contact->GetFixtureB(); // 때린 애

	b2Body *bodyA = fixA->GetBody();
	b2Body *bodyB = fixB->GetBody();

	if (bodyA->GetUserData() == nullptr || bodyB->GetUserData() == nullptr) {
		return;
	}

	Sprite* spr1 = (Sprite*)bodyA->GetUserData();
	Sprite* spr2 = (Sprite*)bodyB->GetUserData();

	float pos1 = spr1->getPosition().y + (spr1->getContentSize().height / 2);
	//float pos2 = spr2->getPosition().y + (spr2->getContentSize().height / 2);
	float pos2 = spr2->getPosition().y;

	if (pos2 < pos1) {
		contact->SetEnabled(false);
	}
}

void HelloWorld::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse) {
}

void HelloWorld::EndContact(b2Contact* contact) {
	contact->SetEnabled(true);
}

