#include "HelloWorldScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

bool HelloWorld::init()
{
    if ( !Scene::init() )
    {
        return false;
    }

	/////////////////////////////////

	tmap = TMXTiledMap::create("TileMaps/TestDesert.tmx");
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
