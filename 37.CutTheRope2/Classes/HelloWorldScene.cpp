#include "HelloWorldScene.h"
#include "vrope-x\vrope.h"

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
	ropes = new std::vector<VRope*>;

	winSize = Director::getInstance()->getWinSize();

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Images/CutTheVerlet.plist");

	srand((int)time(nullptr));

	// 월드 생성
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
	// 배경 로드
	Sprite* bg = Sprite::createWithSpriteFrameName("bg.png");
	bg->setPosition(Vec2(winSize.width / 2, winSize.height / 2));
	this->addChild(bg);

	// 악어 이미지 로드
	croc_ = Sprite::createWithSpriteFrameName("croc_front_mouthclosed.png");
	croc_->setPosition(Vec2((winSize.width - 140), 40));
	this->addChild(croc_);

	b2BodyDef bodyDef;
	bodyDef.type = b2_staticBody;
	bodyDef.position.Set(
		croc_->getPosition().x / PTM_RATIO,
		croc_->getPosition().y / PTM_RATIO);

	bodyDef.userData = croc_;
	crocMouth_ = _world->CreateBody(&bodyDef);

	b2FixtureDef fixtureDef;
	b2PolygonShape dynamicBox;

	dynamicBox.SetAsBox(
		croc_->getContentSize().width / 3 / PTM_RATIO,
		croc_->getContentSize().height / 5 / PTM_RATIO);
	fixtureDef.shape = &dynamicBox;

	crocMouth_->CreateFixture(&fixtureDef);

	// 밧줄 이미지 로드
	ropeSpriteSheet = SpriteBatchNode::create("Images/rope_texture.png");
	this->addChild(ropeSpriteSheet);

	// 아이템 추가
	b2Body*	candy = this->createCandyAt(Vec2(winSize.width / 2, winSize.height * 2 / 3));

	// Add a bunch of ropes
	this->createRope(
		groundBody,
		b2Vec2(130 / PTM_RATIO, (winSize.height - 60) / PTM_RATIO),
		candy,
		candy->GetLocalCenter(),
		1.1f);

	this->createRope(
		groundBody,
		b2Vec2((winSize.width - 120) / PTM_RATIO, (winSize.height - 60) / PTM_RATIO),
		candy,
		candy->GetLocalCenter(),
		1.1f);

	this->createRope(
		groundBody,
		b2Vec2((winSize.width - 120) / PTM_RATIO, (winSize.height - 150) / PTM_RATIO),
		candy,
		candy->GetLocalCenter(),
		1.1f);
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

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void HelloWorld::onExit() {
	_eventDispatcher->removeEventListener(listener);
	Scene::onExit();
}

void HelloWorld::tick(float dt) {
	int velocityIterations = 8;
	int positionIterations = 1;

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

	// 밧줄 시뮬레이션
	std::vector<VRope *>::iterator rope;

	for (rope = ropes->begin(); rope != ropes->end(); ++rope) {
		(*rope)->update(dt);
		(*rope)->updateSprites();
	}
}

void HelloWorld::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags)
{
	Scene::draw(renderer, transform, flags);

	_customCommand.init(_globalZOrder, transform, flags);
	_customCommand.func = CC_CALLBACK_0(HelloWorld::onDraw, this, transform, flags);
	renderer->addCommand(&_customCommand);
}

b2Body* HelloWorld::createCandyAt(Vec2 location) {
	candySprite = Sprite::createWithSpriteFrameName("pineapple.png");
	this->addChild(candySprite);

	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(location.x / PTM_RATIO, location.y / PTM_RATIO);
	bodyDef.userData = candySprite;
	bodyDef.linearDamping = 0.3f;

	b2Body* body = _world->CreateBody(&bodyDef);

	b2FixtureDef fixtureDef;
	b2PolygonShape spriteShape;

	b2Vec2 verts[] = {
		b2Vec2(-7.6f / PTM_RATIO, -34.4f / PTM_RATIO),
		b2Vec2(8.3f / PTM_RATIO, -34.4f / PTM_RATIO),
		b2Vec2(15.55f / PTM_RATIO, -27.15f / PTM_RATIO),
		b2Vec2(13.8f / PTM_RATIO, 23.05f / PTM_RATIO),
		b2Vec2(-3.35f / PTM_RATIO, 35.25f / PTM_RATIO),
		b2Vec2(-16.25f / PTM_RATIO, 25.55f / PTM_RATIO),
		b2Vec2(-15.55f / PTM_RATIO, -23.95f / PTM_RATIO)
	};

	spriteShape.Set(verts, 7);

	fixtureDef.shape = &spriteShape;
	fixtureDef.density = 30.0f;
	fixtureDef.filter.categoryBits = 0x01;
	fixtureDef.filter.maskBits = 0x01;

	body->CreateFixture(&fixtureDef);

	return body;
}

bool HelloWorld::onTouchBegan(Touch* touch, Event* event) {
	return true;
}

void HelloWorld::onTouchMoved(Touch* touch, Event* event) {
	Vec2 pt0 = touch->getPreviousLocation();
	Vec2 pt1 = touch->getLocation();

	std::vector<VRope *>::iterator rope;
	for (rope = ropes->begin(); rope != ropes->end(); ++rope) {
		std::vector<VStick *>::iterator stick;
		for (stick = (*rope)->getSticks().begin(); stick != (*rope)->getSticks().end(); ++stick) {
			Vec2 pa = (*stick)->getPointA()->point();
			Vec2 pb = (*stick)->getPointB()->point();

			if (this->checkLineIntersection(pt0, pt1, pa, pb)) {
				// cut the rope here
				b2Body *newBodyA = createRopeTipBody();
				b2Body *newBodyB = createRopeTipBody();

				VRope *newRope = (*rope)->cutRopeInStick((*stick), newBodyA, newBodyB);
				ropes->push_back(newRope);

				return;
			}
		}
	}
}

b2Body* HelloWorld::createRopeTipBody() {
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.linearDamping = 0.5f;
	b2Body *body = _world->CreateBody(&bodyDef);

	b2FixtureDef circleDef;
	b2CircleShape circle;
	circle.m_radius = 1.0f / PTM_RATIO;
	circleDef.shape = &circle;
	circleDef.density = 10.0f;

	circleDef.filter.maskBits = 0;
	body->CreateFixture(&circleDef);

	return body;
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

void HelloWorld::createRope(b2Body* bodyA, b2Vec2 anchorA, b2Body* bodyB, b2Vec2 anchorB, float32 sag) {
	b2RopeJointDef jd;
	jd.bodyA = bodyA;
	jd.bodyB = bodyB;
	jd.localAnchorA = anchorA;
	jd.localAnchorB = anchorB;

	// Max length of joint = current distance between bodies * sag
	float32 ropeLength = (bodyA->GetWorldPoint(anchorA) - bodyB->GetWorldPoint(anchorB)).Length()*sag;
	jd.maxLength = ropeLength;

	b2RopeJoint* ropeJoint = (b2RopeJoint*)_world->CreateJoint(&jd);

	VRope* newRope = new VRope(ropeJoint, ropeSpriteSheet);
	ropes->push_back(newRope);
}

/*
	밧줄의 터치 여부 체크
*/
bool HelloWorld::checkLineIntersection(Vec2 p1, Vec2 p2, Vec2 p3, Vec2 p4) {
	float denominator = (p4.y - p3.y) * (p2.x - p1.x) - (p4.x - p3.x) * (p2.y - p1.y);

	if (denominator == 0.0f) return false;

	float ua = ((p4.x - p3.x) * (p1.y - p3.y) - (p4.y - p3.y) * (p1.x - p3.x)) / denominator;
	float ub = ((p2.x - p1.x) * (p1.y - p3.y) - (p2.y - p1.y) * (p1.x - p3.x)) / denominator;

	if (ua >= 0.0 && ua <= 1.0 && ub >= 0.0 && ub <= 1.0) return true;

	return false;
}

void HelloWorld::BeginContact(b2Contact* contact) {
}

void HelloWorld::PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
{
	b2Fixture* fixA = contact->GetFixtureA();
	b2Fixture* fixB = contact->GetFixtureB();

	b2Body* bodyA = fixA->GetBody();
	b2Body* bodyB = fixB->GetBody();
	
	if ((bodyA->GetUserData() == croc_) && (bodyB->GetUserData() == candySprite)) {
		if (!crocMouthOpened) {
			croc_->setSpriteFrame("croc_front_mouthopen.png");
			crocMouthOpened = true;
			candySprite->setOpacity(0);
		}
	}
}
