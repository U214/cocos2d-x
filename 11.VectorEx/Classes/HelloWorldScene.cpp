#include "HelloWorldScene.h"

USING_NS_CC;
using namespace std;

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

	auto wlayer = LayerColor::create(Color4B(255, 255, 255, 255));
	this->addChild(wlayer);

	/////////////////////////////////

	myVector1();
	myVector2();
	myVector3();
	return true;
}

void HelloWorld::myVector1() {
	std::vector<std::string> names;

	names.push_back("ABC");
	names.push_back("123");
	names.push_back("xyz");

	vector<string>::iterator it = names.begin();

	for (; it != names.end(); ++it) {
		log("%s", (*it).c_str());
	}

	for (vector<string>::iterator it = names.begin(); it != names.end(); ++it) {
		log("%s", (*it).c_str());
	}

	for (int i = 0; i < names.size(); i++) {
		log("%s", names[i].c_str());
		log("%s", names.at(i).c_str());
		names.erase(names.begin() + i);
	}
	names.clear();

	log("myVector1 종료");
}

void HelloWorld::myVector2() {
	auto img11 = Sprite::create("Images/grossini.png");
	auto img12 = Sprite::create("Images/grossinis_sister1.png");
	auto img13 = Sprite::create("Images/grossinis_sister2.png");

	img11->setTag(11);
	img12->setTag(12);
	img13->setTag(13);

	std::vector<cocos2d::Sprite*> pictures1;

	pictures1.push_back(img11);
	pictures1.push_back(img12);
	pictures1.push_back(img13);

	vector<Sprite*>::iterator it = pictures1.begin();

	int i = 1;
	for (; it != pictures1.end(); ++it) {
		auto obj = (Sprite*)(*it);
		obj->setScale(0.5f);
		obj->setPosition(Vec2(120 * i, 240));
		this->addChild(obj);
		i++;
	}
	for (vector<Sprite*>::iterator it = pictures1.begin(); it != pictures1.end(); ++it) {
		auto obj = (Sprite*)(*it);
		log("Tag1 ... %d", obj->getTag());
	}

	for (int i = 0; i < pictures1.size(); i++) {
		pictures1.erase(pictures1.begin() + i);
	}

	log("Count1 .. %d", pictures1.size());

	pictures1.clear();
	log("myVector2 종료");
}

void HelloWorld::myVector3() {
	auto img21 = Sprite::create("Images/grossini.png");
	auto img22 = Sprite::create("Images/grossinis_sister1.png");
	auto img23 = Sprite::create("Images/grossinis_sister2.png");

	img21->setTag(21);
	img22->setTag(22);
	img23->setTag(23);

	cocos2d::Vector<cocos2d::Sprite*> pictures2;

	pictures2.pushBack(img21);
	pictures2.pushBack(img22);
	pictures2.pushBack(img23);

	vector<Sprite*>::iterator it = pictures2.begin();

	int i = 1;
	for (; it != pictures2.end(); ++it) {
		auto obj = (Sprite*)(*it);
		obj->setScale(0.5f);
		obj->setPosition(Vec2(120 * i, 240));
		this->addChild(obj);
		i++;
	}
	this->release();
	for (vector<Sprite*>::iterator it = pictures2.begin(); it != pictures2.end(); ++it) {
		auto obj = (Sprite*)(*it);
		log("Tag2 ... %d", obj->getTag());
	}

	for (int i = 0; i < pictures2.size(); i++) {
		auto obj = (Sprite*)pictures2.at(i);
		pictures2.eraseObject(obj);

		//코코스벡터에는 객체자체를 지우는게 있다
	}

	log("Count2 .. %d", pictures2.size());

	pictures2.clear();
	log("myVector3 종료");
}