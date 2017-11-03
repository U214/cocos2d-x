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
	texture = Director::getInstance()->getTextureCache()->addImage("blocks.png");

	auto pMenuItem = MenuItemFont::create(
		" Reset ",
		CC_CALLBACK_1(HelloWorld::doReset, this));

	auto pMenu = Menu::create(pMenuItem, nullptr);
	pMenu->setPosition(Vec2(240, 50));
	this->addChild(pMenu);

	// 월드 생성
	if (this->createBox2dWorld(true)) {
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
	b2Body *groundBody = _world->CreateBody(&groundBodyDef);

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

	// 조준 Sprite
	for (int i = 0; i < 5; ++i) {
		line[i] = Sprite::create("line.png");
		line[i]->setPosition(Vec2(0, 0));
		line[i]->setOpacity(0);
		this->addChild(line[i], 200);
	}

	// 바디를 생성해서 월드에 추가한다
	this->doReset(this);

	// 네모 추가
	this->addNewSprite(Vec2(240, 160), Size(64, 64), b2_dynamicBody, "test", 2);
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

	if (type == 1) {
		b2CircleShape circle;

		circle.m_radius = (size.width / 2) / PTM_RATIO;
		fixtureDef.shape = &circle;
		fixtureDef.friction = 0.3f;
		fixtureDef.density = 1.0f;
		fixtureDef.restitution = 0.8f;

		body->CreateFixture(&fixtureDef);

		b2WeldJointDef weldJointDef;
		weldJointDef.Initialize(body, gbody, body->GetPosition());
		weldJoint = (b2WeldJoint *)_world->CreateJoint(&weldJointDef);
	}
	else if (type == 2) {
		b2PolygonShape dynamicBox;

		dynamicBox.SetAsBox(size.width / 2 / PTM_RATIO, size.height / 2 / PTM_RATIO);
		fixtureDef.shape = &dynamicBox;
		fixtureDef.friction = 0.3f;
		fixtureDef.density = 1.0f;
		fixtureDef.restitution = 0.8f;

		body->CreateFixture(&fixtureDef);
	}
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

	if (this->getBodyAtTab(touchPoint) != nullptr) {
		dragBody = this->getBodyAtTab(touchPoint);
	}
	else {
		return false;
	}
	
	// 터치한 대상이 볼일 경우
	if (dragBody == myBall && bBallTouch == false) {
		bBallTouch = true;

		_world->DestroyJoint(weldJoint);
		weldJoint = nullptr;		

		startPoint = myBall->GetPosition();
		Vec2 point = Vec2(startPoint.x * PTM_RATIO, startPoint.y * PTM_RATIO);

		for (int i = 0; i < 5; ++i) {
			line[i]->setPosition(point);
			line[i]->setOpacity(100);
		}
	}

	bDrag = true;

	b2MouseJointDef md;
	md.bodyA = gbody;
	md.bodyB = dragBody;
	md.target.Set(dragBody->GetPosition().x, dragBody->GetPosition().y);
	md.maxForce = 300.0 * dragBody->GetMass();

	mouseJoint = (b2MouseJoint *)_world->CreateJoint(&md);
	
	return true;
}

void HelloWorld::onTouchMoved(Touch* touch, Event* event) {
	Vec2 touchPoint = touch->getLocation();

	if (bDrag) {
		if (bBallTouch == true) {
			b2Vec2 point = updateLine(b2Vec2(touchPoint.x / PTM_RATIO, touchPoint.y / PTM_RATIO));
			mouseJoint->SetTarget(point);
		}
		else {
			mouseJoint->SetTarget(b2Vec2(touchPoint.x / PTM_RATIO, touchPoint.y / PTM_RATIO));
		}
	}
}

void HelloWorld::onTouchEnded(Touch* touch, Event* event) {
	if (bDrag) {
		if (myBall && bBallTouch) {
			bBallTouch = false;
			endPoint = myBall->GetPosition();

			float dx = endPoint.x - startPoint.x;
			float dy = endPoint.y - startPoint.y;
			float distance = sqrt(dx * dx + dy * dy);

			// 당긴 거리가 일정 거리 이상이며 발사 아니면 Reset
			if (distance > PLAYER_RADIUS_MIN) {
				b2Vec2 force = startPoint - endPoint;

				force.x *= 250.0f;
				force.y *= 250.0f;

				myBall->ApplyForceToCenter(force, true);
			}
			else {
				myBall->SetTransform(b2Vec2(100 / PTM_RATIO, 100 / PTM_RATIO),
					myBall->GetAngle());

				b2WeldJointDef weldJointDef;
				weldJointDef.Initialize(myBall, gbody, myBall->GetPosition());
				weldJoint = (b2WeldJoint *)_world->CreateJoint(&weldJointDef);
			}

			// Line 그림 투명하게 처리
			for (int i = 0; i < 5; ++i) {
				line[i]->setOpacity(0);
			}
		}

		_world->DestroyJoint(mouseJoint);
		mouseJoint = NULL;

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

b2Vec2 HelloWorld::updateLine(b2Vec2 point) {
	float dx = point.x - startPoint.x;
	float dy = point.y - startPoint.y;

	float distance = sqrt(dx * dx + dy * dy);
	float angle = atan2(dy, dx);

	// 최대 거리보다 볼이 멀어지지 않게 조정
	if (distance > PLAYER_RADIUS_MAX) {
		point.x = startPoint.x + cos(angle) * PLAYER_RADIUS_MAX;
		point.y = startPoint.y + sin(angle) * PLAYER_RADIUS_MAX;

		for (int i = 0; i < 5; ++i) {
			line[i]->setOpacity(100);
			line[i]->setPosition(Vec2(
				(startPoint.x + cos(angle) * (i*PLAYER_RADIUS_MAX / 5)) * PTM_RATIO,
				(startPoint.y + sin(angle) * (i*PLAYER_RADIUS_MAX / 5)) * PTM_RATIO));
		}
	}
	else {
		for (int i = 0; i < 5; ++i) {
			line[i]->setPosition(Vec2(
				(startPoint.x + cos(angle) * (i * (distance / 5))) * PTM_RATIO,
				(startPoint.y + sin(angle) * (i * (distance / 5))) * PTM_RATIO));
		}
	}

	return point;
}

void HelloWorld::doReset(Ref* pSender) {
	bBallTouch = false;

	if (myBall != nullptr) {
		auto ball = (Sprite *)myBall->GetUserData();
		myBall->SetActive(false);

		b2JointEdge* joints = myBall->GetJointList();

		while (joints) {
			b2Joint* joint = joints->joint;
			joints = joints->next;

			_world->DestroyJoint(joint);
		}
		this->removeChild(ball, true);
		_world->DestroyBody(myBall);
	}
	myBall = this->addNewSprite(Vec2(100, 100), Size(32, 32), b2_dynamicBody, "SpinningPeas.png", 1);
}