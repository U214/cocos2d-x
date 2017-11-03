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
	texture = Director::getInstance()->getTextureCache()->addImage("Pea.png");

	if (this->createBox2dWorld(true)) {
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

	// 휴식 상태일 때 포함된 바디들을 멈추게 (Sleep)할 것인가 결정
	_world->SetAllowSleeping(true);

	// 지속적인 물리 작용을 할 것인지
	_world->SetContinuousPhysics(true);

	// 디버그 드로잉 설정
	if (debug) {
		// 적색 : 현재 운동중
		// 회색 : 현재 물리 운동량 없음
		m_debugDraw = new GLESDebugDraw(PTM_RATIO);
		_world->SetDebugDraw(m_debugDraw);

		uint32 flags = 0;
		flags += b2Draw::e_shapeBit;
		//flags += b2Draw::e_jointBit;
		//flags += b2Draw::e_aabbBit;
		//flags += b2Draw::e_pairBit;
		//flags += b2Draw::e_centerOfMassBit;
		m_debugDraw->SetFlags(flags);
	}

	// 가장 자리를 지정해 공간을 만든다

	// 바디데프에 좌표 설정
	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0, 0);

	// 월드에 바디데프의 정보로 바디를 만든다
	b2Body *groundBody = _world->CreateBody(&groundBodyDef);

	// 가장자리 경계선을 그릴 수 있는 모양의 객체를 만든다
	b2EdgeShape groundEdge;
	b2FixtureDef boxShapeDef;
	boxShapeDef.shape = &groundEdge;

	// 만든 객체에 set함수로 선을 만든다
	// 그리고 바디(groundBody)에 모양(groundEge)을 고정시킨다

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

HelloWorld::~HelloWorld() {
	delete _world;
	_world = NULL;
}

void HelloWorld::onEnter() {
	Scene::onEnter();

	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);

	listener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void HelloWorld::onExit() {
	_eventDispatcher->removeEventListener(listener);
	Scene::onExit();
}

bool HelloWorld::onTouchBegan(Touch* touch, Event* event) {
	auto touchPoint = touch->getLocation();

	addNewSpriteAtPosition(touchPoint);

	return true;
}

void HelloWorld::tick(float dt) {
	// 물리적 위치를 이용해 그래픽 위치를 갱신한다

	// 프로젝트 생성시 기본 값
	// int velocityIterations = 8;
	// 바디를 정상적으로 이동시키기 위해 필요한 충돌을
	// 반복적으로 계산

	// int positionIterations = 1;
	// 조인트 분리와 겹침 현상을 줄이기 위해 바디의 위치를
	// 반복적으로 적용

	// 값이 클수록 정확한 연산은 가능하지만 성능이 떨어짐

	// 매뉴얼 권장값
	int velocityIterations = 8;
	int positionIterations = 3;

	// Step : 물리 세계를 시뮬레이션 한다
	_world->Step(dt, velocityIterations, positionIterations);

	// 모든 물리 객체는 링크드 리스트에 저장되어 참조해 볼수 있다
	// 만들어진 객체만큼 루프를 돌리면서 바디에 붙인 스프라이트를
	// 여기서 제어한다 (위치 등)

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

void HelloWorld::addNewSpriteAtPosition(Vec2 location) {
	// 스프라이트를 파라미터로 넘어온 위치에 만든다 (터치포인트)
	Sprite* pSprite = Sprite::createWithTexture(texture, Rect(0, 0, 37, 37));
	pSprite->setPosition(Vec2(location.x, location.y));
	this->addChild(pSprite);


	// 바디 데프를 만들고 속성을 지정한다
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(location.x / PTM_RATIO, location.y / PTM_RATIO);
	//bodyDef.userData = pSprite;
	bodyDef.userData = NULL;

	// 월드에 바디데프의 정보로 바디를 만든다
	b2Body* body = _world->CreateBody(&bodyDef);

	// 바디에 적용할 물리 속성용 바디 모양을 만든다
	// 원 형태를 선택해 반지름을 지정한다
	b2CircleShape circle;
	circle.m_radius = 0.45f; // 수정해서 테스트

	// 바디에 원 만든거 고정
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &circle;

	// 밀도
	fixtureDef.density = 1.0f;
	
	// 마찰력 (0 ~ 1)
	fixtureDef.friction = 0.2f;

	// 반반력 (1 : 처음 위치로 올라간당)
	fixtureDef.restitution = 0.6f;

	body->CreateFixture(&fixtureDef);
}

void HelloWorld::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags)
{
	Scene::draw(renderer, transform, flags);

	_customCommand.init(_globalZOrder, transform, flags);
	_customCommand.func = CC_CALLBACK_0(HelloWorld::onDraw, this, transform, flags);
	renderer->addCommand(&_customCommand);
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
