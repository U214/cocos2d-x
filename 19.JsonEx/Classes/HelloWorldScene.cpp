#include "HelloWorldScene.h"
#include "json/rapidjson.h"
#include "json/document.h"
#include "json/stringbuffer.h"
#include "json/prettywriter.h"

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

	std::string jsonData = FileUtils::getInstance()->getStringFromFile("data/test_data.json");
	log("%s\n", jsonData.c_str());

	rapidjson::Document doc;
	doc.Parse<0>(jsonData.c_str());

	if (doc.HasParseError()) {
		log("GetParseError %s\n", doc.GetParseError());
		return false;
	}

	std::string str = doc["string"].GetString();
	log("name = %s", str.c_str());

	int n1 = doc["integer"].GetInt();
	log("i = %d", n1);

	bool isTF = doc["bool"].GetBool();
	log("t = %d", isTF);

	float n2 = doc["float"].GetFloat();
	log("f = %.2f", n2);

	const rapidjson::Value &arr = doc["array"];
	if (arr.IsArray()) {
		for (rapidjson::SizeType i = 0; i < arr.Size(); ++i) {
			auto name = arr[i]["name"].GetString();
			auto age = arr[i]["age"].GetInt();
			log("name : %s, age : %d", name, age);
		}
	}

    return true;
}
