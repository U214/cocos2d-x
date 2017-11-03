#include "HelloWorldScene.h"

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
	
	//auto pMenuItem = MenuItemFont::create(
	//	" Reset ",
	//	CC_CALLBACK_1(HelloWorld::doReset, this));

	//auto pMenu = Menu::create(pMenuItem, nullptr);
	//pMenu->setPosition(Vec2(240, 50));
	//this->addChild(pMenu);

	// 월드 생성
	if (this->createBox2dWorld(true)) {
		bulletBody = nullptr;
		bulletJoint = nullptr;
		releasingArm = false;

		this->setBox2dWorld();
		this->schedule(schedule_selector(HelloWorld::tick));
	}

	return true;
}

bool HelloWorld::createBox2dWorld(bool debug) {
	////////////////////////// 월드 생성 시작

	//중력의 방향 결정
	b2Vec2 gravity = b2Vec2(0.0f, 0.0f);

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
	groundBody = _world->CreateBody(&groundBodyDef);

	b2EdgeShape groundEdge;
	b2FixtureDef boxShapeDef;
	boxShapeDef.shape = &groundEdge;

	// 아래
	groundEdge.Set(b2Vec2(0, 0), b2Vec2(winSize.width / PTM_RATIO, 0));
	groundBody->CreateFixture(&boxShapeDef);

	// 왼쪽
	groundEdge.Set(b2Vec2(0, 0), b2Vec2(0, winSize.height / PTM_RATIO));
	groundBody->CreateFixture(&boxShapeDef);

	// 위쪽
	groundEdge.Set(
		b2Vec2(0, winSize.height / PTM_RATIO),
		b2Vec2(winSize.width / PTM_RATIO, winSize.height / PTM_RATIO));
	groundBody->CreateFixture(&boxShapeDef);

	// 아래
	groundEdge.Set(
		b2Vec2(winSize.width / PTM_RATIO, winSize.height / PTM_RATIO),
		b2Vec2(winSize.width / PTM_RATIO, 0));
	groundBody->CreateFixture(&boxShapeDef);

	///////////////////////////// 월드 생성 끝

	return true;
}

void HelloWorld::setBox2dWorld() {
	// 마우스 조인트 바디를 생성해서 월드에 추가
	bDrag = false;
	gbody = this->addNewSprite(Vec2::ZERO, Size::ZERO, b2_staticBody, NULL, 0);

	///////////////
	Sprite* sprite = Sprite::create("Images/catapult_base_2.png");
	sprite->setAnchorPoint(Vec2(0, 0));
	sprite->setPosition(Vec2(120.0f, 0));
	this->addChild(sprite, 0);

	sprite = Sprite::create("Images/catapult_base_1.png");
	sprite->setAnchorPoint(Vec2(0, 0));
	sprite->setPosition(Vec2(120.0f, 0));
	this->addChild(sprite, 9);

	///////////// create the catapult's arm
	Sprite *arm = Sprite::create("Images/catapult_arm.png");
	this->addChild(arm, 1);

	b2BodyDef armBodyDef;
	armBodyDef.type = b2_dynamicBody;
	armBodyDef.linearDamping = 1;
	armBodyDef.angularDamping = 1;
	armBodyDef.position.Set(170.0f / PTM_RATIO, 91.0f / PTM_RATIO);
	armBodyDef.userData = arm;
	armBody = _world->CreateBody(&armBodyDef);

	// create a joint to fix the catapult to the floor
	b2RevoluteJointDef armJointDef;
	armJointDef.Initialize(groundBody, armBody,
		b2Vec2(170.0f / PTM_RATIO, 10.0f / PTM_RATIO));
	armJointDef.enableMotor = true;
	armJointDef.enableLimit = true;
	armJointDef.motorSpeed = -10;
	armJointDef.lowerAngle = CC_DEGREES_TO_RADIANS(9);
	armJointDef.upperAngle = CC_DEGREES_TO_RADIANS(75);
	armJointDef.maxMotorTorque = 700;

	armJoint = (b2RevoluteJoint*)_world->CreateJoint(&armJointDef);

	///////////////////////////
	b2PolygonShape armBox;
	armBox.SetAsBox(11.0f / PTM_RATIO, 91.0f / PTM_RATIO);
	b2FixtureDef armBoxDef;
	armBoxDef.shape = &armBox;
	armBoxDef.density = 0.3F;
	armFixture = armBody->CreateFixture(&armBoxDef);

	this->attachBullet();
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
	listener->onTouchMoved = CC_CALLBACK_2(HelloWorld::onTouchMoved, this);
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

	// arm is being released
	if (releasingArm && bulletJoint) {
		// check if the arm reached the end so we can return the limits
		if (armJoint->GetJointAngle() <= CC_DEGREES_TO_RADIANS(10)) {
			releasingArm = false;

			// destroy joint so the bullet will be free
			_world->DestroyJoint(bulletJoint);
			bulletJoint = NULL;
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
	
	if (b2Body* b = this->getBodyAtTab(touchPoint)) { 
		dragBody = b;
		bDrag = true;

		b2MouseJointDef md;
		md.bodyA = gbody;
		md.bodyB = dragBody;
		md.target.Set(dragBody->GetPosition().x, dragBody->GetPosition().y);
		md.maxForce = 300.0 * dragBody->GetMass();

		mouseJoint = (b2MouseJoint *)_world->CreateJoint(&md);
	}

	return true;
}

void HelloWorld::onTouchMoved(Touch* touch, Event* event) {
	Vec2 touchPoint = touch->getLocation();

	if (bDrag) {
		mouseJoint->SetTarget(b2Vec2(touchPoint.x / PTM_RATIO, touchPoint.y / PTM_RATIO));
	}
}

void HelloWorld::onTouchEnded(Touch* touch, Event* event) {
	if (bDrag) {
		if (armJoint->GetJointAngle() >= CC_DEGREES_TO_RADIANS(20)) {
			releasingArm = true;
		}

		_world->DestroyJoint(mouseJoint);
		mouseJoint = nullptr;

		dragBody->SetAwake(true);
	}
	bDrag = false;
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

//void HelloWorld::doReset(Ref* pSender) {
//	bBallTouch = false;
//
//	if (myBall != nullptr) {
//		auto ball = (Sprite *)myBall->GetUserData();
//		myBall->SetActive(false);
//
//		b2JointEdge* joints = myBall->GetJointList();
//
//		while (joints) {
//			b2Joint* joint = joints->joint;
//			joints = joints->next;
//
//			_world->DestroyJoint(joint);
//		}
//		this->removeChild(ball, true);
//		_world->DestroyBody(myBall);
//	}
//	myBall = this->addNewSprite(Vec2(100, 100), Size(32, 32), b2_dynamicBody, "SpinningPeas.png", 1);
//}

void HelloWorld::attachBullet() {
	// create bullet
	Sprite* sprite = Sprite::create("Images/acorn.png");
	this->addChild(sprite, 1);

	b2BodyDef bulletBodyDef;
	bulletBodyDef.type = b2_dynamicBody;
	bulletBodyDef.bullet = true;
	bulletBodyDef.position.Set(62.0f / PTM_RATIO, 15.0f / PTM_RATIO);
	bulletBodyDef.userData = sprite;
	b2Body* bullet = _world->CreateBody(&bulletBodyDef);
	bullet->SetActive(false);

	b2CircleShape circle;
	circle.m_radius = 15.0 / PTM_RATIO;

	b2FixtureDef ballShapeDef;
	ballShapeDef.shape = &circle;
	ballShapeDef.density = 0.8f;
	ballShapeDef.restitution = 0.2f;
	ballShapeDef.friction = 0.99f;
	bullet->CreateFixture(&ballShapeDef);

	bulletBody = bullet;
	bulletBody->SetTransform(b2Vec2(190.0f / PTM_RATIO, 155.0f / PTM_RATIO), 0.0f);
	bulletBody->SetActive(true);

	b2WeldJointDef weldJoingDef;
	weldJoingDef.Initialize(bulletBody, armBody, b2Vec2(190.0f / PTM_RATIO, 155.0f / PTM_RATIO));
	weldJoingDef.collideConnected = false;

	bulletJoint = (b2WeldJoint*)_world->CreateJoint(&weldJoingDef);
}