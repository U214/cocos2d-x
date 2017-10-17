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

	auto wlayer = LayerColor::create(Color4B(255, 255, 255, 255));
	this->addChild(wlayer);
    
	/////////////////////////////////

	log("********************init value *************");

	UserDefault::getInstance()->setStringForKey("str_key", "value1");
	UserDefault::getInstance()->setIntegerForKey("int_key", 10);
	UserDefault::getInstance()->setFloatForKey("float_key", 2.3f);
	UserDefault::getInstance()->setDoubleForKey("double_key", 2.4f);
	UserDefault::getInstance()->setBoolForKey("bool_key", true);
	UserDefault::getInstance()->flush();

	std::string ret = UserDefault::getInstance()->getStringForKey("str_key");
	log("string is %s", ret.c_str());

	int i = UserDefault::getInstance()->getIntegerForKey("int_key");
	log("integer is %d", i);

	float f = UserDefault::getInstance()->getFloatForKey("float_key");
	log("float is %f", f);

	double d = UserDefault::getInstance()->getDoubleForKey("double_key");
	log("double is %f", d);

	bool b = UserDefault::getInstance()->getBoolForKey("bool_key");

	if (b) {
		log("bool is true");
	}
	else {
		log("bool is false");
	}

	log("**************************after change value******************");

	UserDefault::getInstance()->setStringForKey("str_key", "value2");
	UserDefault::getInstance()->setIntegerForKey("int_key", 11);
	UserDefault::getInstance()->setFloatForKey("float_key", 2.5f);
	UserDefault::getInstance()->setDoubleForKey("double_key", 2.6f);
	UserDefault::getInstance()->setBoolForKey("bool_key", false);
	UserDefault::getInstance()->flush();

	ret = UserDefault::getInstance()->getStringForKey("str_key");
	log("string is %s", ret.c_str());

	i = UserDefault::getInstance()->getIntegerForKey("int_key");
	log("integer is %d", i);

	f = UserDefault::getInstance()->getFloatForKey("float_key");
	log("float is %f", f);

	d = UserDefault::getInstance()->getDoubleForKey("double_key");
	log("double is %f", d);

	b = UserDefault::getInstance()->getBoolForKey("bool_key");

	if (b) {
		log("bool is true");
	}
	else {
		log("bool is false");
	}

    return true;
}
