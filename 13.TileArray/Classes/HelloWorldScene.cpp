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

	/////////////////////////////

	//화면 사이즈 구하기
	winSize = Director::getInstance()->getWinSize();

	tmap = TMXTiledMap::create("TileMaps/TestDesert.tmx");
	background = tmap->getLayer("Background");
	items = tmap->getLayer("Items");
	metainfo = tmap->getLayer("MetaInfo");
	metainfo->setVisible(false);
	this->addChild(tmap, 0, 11);

	TMXObjectGroup* objects = tmap->getObjectGroup("Objects");
	ValueMap spawnPoint = objects->getObject("SpawnPoint");

	int x = spawnPoint["x"].asInt();
	int y = spawnPoint["y"].asInt();

	dradonPosition = Vec2(x, y);

	this->createDragon();

	return true;
}

void HelloWorld::createDragon()
{
	auto texture = Director::getInstance()->getTextureCache()->addImage("Images/dragon_animation.png");

	auto animation = Animation::create();
	animation->setDelayPerUnit(0.1f);

	for (int i = 0; i < 6; i++)
	{
		int index = i % 4;
		int rowindex = i / 4;

		animation->addSpriteFrameWithTexture(
			texture,
			Rect(index * 130, rowindex * 140, 130, 140));

	}
	// 스프라이트 생성 및 초기화
	dragon = Sprite::createWithTexture(texture, Rect(0, 0, 130, 140));
	dragon->setPosition(dradonPosition);
	this->addChild(dragon);

	dragon->setFlippedX(true);

	dragon->setScale(0.5);

	auto animate = Animate::create(animation);
	auto rep = RepeatForever::create(animate);
	dragon->runAction(rep);

}

void HelloWorld::onEnter()
{
	Scene::onEnter();

	//싱글 터치모드로 터치 리스너 등록

	//swallow touches only available in OneByOne mode.
	//핸들링 된 터치 이벤트를 터치 이벤트 array에서 지우겠다는 의미다.
	listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);

	listener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
	listener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);



	//the priority of the touch listener is based on the draw order of sprite 
	//터치 리스너의 우선순위를 (노드가) 화면에 그려진 순서대로 한다.

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}



void HelloWorld::onExit()
{

	_eventDispatcher->removeEventListener(listener);
	//_eventDispatcher->removeALLEventListener();
	//_eventDispatcher->removeEventListenersForType
	//(EventListeners::Type::TOUCH_ONE_BY_ONE);

	Scene::onExit();

}

bool HelloWorld::onTouchBegan(Touch*touch, Event*event)
{


	return true;
}

//손가락을 화면에서 떼지 않고 이리저리 움직일 때 계속해서 호출된다.
// 얼마나 자주 호출되느냐는 전적으로
//이벤트를 핸들링하는 애플리케이션의 Run Loop에 달렸다.

void HelloWorld::onTouchEnded(Touch*touch, Event*event)
{

	auto touchPoint = touch->getLocation();
	touchPoint = this->convertToNodeSpace(touchPoint);

	Vec2 playerPos = dragon->getPosition();

	Vec2 diff = touchPoint - playerPos;

	if (abs(diff.x) >abs(diff.y))
	{
		if (diff.x >0)
		{
			playerPos.x += tmap->getTileSize().width;
			dragon->setFlippedX(true);
		}
		else
		{
			playerPos.x -= tmap->getTileSize().width;
			dragon->setFlippedX(false);
		}
	}
	else
	{
		if (diff.y > 0)
		{
			playerPos.y += tmap->getTileSize().height;
		}
		else
		{
			playerPos.y -= tmap->getTileSize().height;
		}
	}

	if (playerPos.x <= (tmap->getMapSize().width * tmap->getTileSize().width) &&
		playerPos.y <= (tmap->getMapSize().height * tmap->getTileSize().height) &&
		playerPos.y >= 0 &&
		playerPos.x >= 0)
	{
		this->setPlayerPosition(playerPos);
	}

	this->setViewpointCenter(dragon->getPosition());
}

void HelloWorld::setViewpointCenter(cocos2d::Vec2 position)
{
	//파라미터로 들어오는 위치에 맞춰 화면을 움직인다. 

	int x = MAX(position.x, winSize.width / 2);
	int y = MAX(position.y, winSize.height / 2);

	x = MIN(x, (tmap->getMapSize().width * tmap->getTileSize().width) - winSize.width / 2);

	y = MIN(y, (tmap->getMapSize().height * tmap->getTileSize().height) - winSize.height / 2);

	Vec2 acutalPosition = Vec2(x, y);
	Vec2 centerOfView = Vec2(winSize.width / 2, winSize.height / 2);
	Vec2 viewPoint = centerOfView - acutalPosition;

	this->setPosition(viewPoint);

}

Vec2 HelloWorld::tileCoordForPosition(Vec2 position)
{
	int x = position.x / tmap->getTileSize().width;
	int y = ((tmap->getMapSize().height * tmap->getTileSize().height) - position.y) / tmap->getTileSize().height;

	return Vec2(x, y);
}

void HelloWorld::setPlayerPosition(Vec2 position)
{
	Vec2 tileCoord = this->tileCoordForPosition(position);

	int tileGid = this->metainfo->getTileGIDAt(tileCoord);

	if (tileGid)
	{
		Value& properties = tmap->getPropertiesForGID(tileGid);

		if (!properties.isNull())
		{

			std::string item1 = properties.asValueMap()["Items"].asString();
			if (item1 == "apple")
			{
				this->metainfo->removeTileAt(tileCoord);
				items->removeTileAt(tileCoord);
				log("apple 아이템 획득!!!");
			}

			if (item1 == "banana")
			{
				this->metainfo->removeTileAt(tileCoord);
				items->removeTileAt(tileCoord);
				log("banana 아이템 획득!!!");

			}
		}
	}

	dragon->setPosition(position);
}