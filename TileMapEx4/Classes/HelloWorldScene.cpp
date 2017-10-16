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

	tmap = TMXTiledMap::create("TileMaps/TestDesert.tmx");
	background = tmap->getLayer("Background");
	items = tmap->getLayer("Items");
	metainfo = tmap->getLayer("MetaInfo");
	metainfo->setVisible(false);

	this->addChild(tmap, 0, 11);

	// 타일 맵에서 Objects라고 지정한 오브젝트 레이어의 객체를 가져오기
	TMXObjectGroup* objects = tmap->getObjectGroup("Objects");

	// 오브젝트 레이어에서 SpawnPoint라고 지정한 속성값 읽어오기
	ValueMap& spawnPoint = objects->getObject("SpawnPoint");

	int x = spawnPoint["x"].asInt();
	int y = spawnPoint["y"].asInt();

	dragonPosition = Vec2(x, y);

	this->createDragon();

	return true;
}

void HelloWorld::onEnter() {
	Scene::onEnter();

	// 싱글 터치 모드로 터치 리스너 등록
	listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);

	listener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
	listener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void HelloWorld::onExit() {
	_eventDispatcher->removeEventListener(listener);
	Scene::onExit();
}

void HelloWorld::createDragon() {
	auto texture = Director::getInstance()->getTextureCache()
		->addImage("Images/dragon_animation.png");

	auto animation = Animation::create();
	animation->setDelayPerUnit(0.1f);

	for (int i = 0; i < 6; i++) {
		int index = i % 4;
		int rowIndex = i / 4;

		animation->addSpriteFrameWithTexture(
			texture,
			Rect(index * 130, rowIndex * 140, 130, 140));
	}

	dragon = Sprite::createWithTexture(texture, Rect(0, 0, 130, 140));
	dragon->setPosition(dragonPosition);
	this->addChild(dragon);

	dragon->setFlippedX(true);
	dragon->setScale(0.5);

	auto animate = Animate::create(animation);
	auto rep = RepeatForever::create(animate);
	dragon->runAction(rep);
}

bool HelloWorld::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event) {

	return true;
}

void HelloWorld::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event) {
	auto touchPoint = touch->getLocation();
	touchPoint = this->convertToNodeSpace(touchPoint);

	Vec2 playerPos = dragon->getPosition();

	Vec2 diff = touchPoint - playerPos;

	// 일단 거리로 위로 갓는지 아래로 갓는지 판단하려고 절댓값
	// 방향은 그 안에서 판단한다
	if (abs(diff.x) > abs(diff.y)) {
		if (diff.x > 0) {
			playerPos.x = playerPos.x + tmap->getTileSize().width;
			dragon->setFlippedX(true);
		}
		else {
			playerPos.x = playerPos.x - tmap->getTileSize().width;
			dragon->setFlippedX(false);
		}
	}
	else {
		if (diff.y > 0) {
			playerPos.y = playerPos.y + tmap->getTileSize().height;
		}
		else {
			playerPos.y = playerPos.y - tmap->getTileSize().height;
		}
	}

	if (playerPos.x <= (tmap->getMapSize().width * tmap->getTileSize().width)
		&& playerPos.y <= (tmap->getMapSize().height * tmap->getTileSize().height)
		&& playerPos.y >= 0
		&& playerPos.x >= 0) {
		this->setPlayerPosition(playerPos);
	}

	this->setViewPointCenter(dragon->getPosition());


}

void HelloWorld::setViewPointCenter(Vec2 position) {
	int x = MAX(position.x, winSize.width / 2);
	int y = MAX(position.y, winSize.height / 2);

	x = MIN(x, (tmap->getMapSize().width * tmap->getTileSize().width) - winSize.width / 2);
	y = MIN(y, (tmap->getMapSize().height * tmap->getTileSize().height) - winSize.height / 2);

	Vec2 actualPosition = Vec2(x, y);
	Vec2 centerOfView = Vec2(winSize.width / 2, winSize.height / 2);
	Vec2 viewPoint = centerOfView - actualPosition;

	this->setPosition(viewPoint);
}

Vec2 HelloWorld::tileCoordForPosition(Vec2 position) {
	int x = position.x / tmap->getTileSize().width;
	int y = ((tmap->getMapSize().height * tmap->getTileSize().height) - position.y)
		/ tmap->getTileSize().height;

	return Vec2(x, y);
}

void HelloWorld::setPlayerPosition(Vec2 position) {
	Vec2 tileCoord = this->tileCoordForPosition(position);

	int tileGid = this->metainfo->getTileGIDAt(tileCoord);

	if (tileGid) {
		Value& properties = tmap->getPropertiesForGID(tileGid);

		if (!properties.isNull()) {
			std::string wall = properties.asValueMap()["Wall"].asString();

			if (wall == "YES") {
				log("Wall");
				return;
			}
		}

		std::string item1 = properties.asValueMap()["Items"].asString();

		if (item1 == "YES") {
			this->metainfo->removeTileAt(tileCoord);
			items->removeTileAt(tileCoord);

			log("아이템 획득");
		}
	}
	dragon->setPosition(position);
}
