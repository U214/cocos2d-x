#include "HelloWorldScene.h"
#include "tinyxml2/tinyxml2.h"

USING_NS_CC;
using namespace tinyxml2;

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

	std::string path = FileUtils::getInstance()->fullPathForFilename("data/test_data.xml");
	tinyxml2::XMLDocument* doc = new tinyxml2::XMLDocument();
	XMLError error = doc->LoadFile(path.c_str());

	if (error != 0) {
		log("Error Number : %d", error);
		return false;
	}

	XMLElement* root = doc->RootElement();

	XMLElement* value = root->FirstChildElement("total");

	if (value) {
		log("value element = %s", value->GetText());
	}

	value = value->NextSiblingElement("page");

	if (value) {
		log("value element = %s", value->GetText());
	}

	value = value->NextSiblingElement("per");

	if (value) {
		log("value element = %s", value->GetText());
	}

	XMLElement* array = value->NextSiblingElement();
	XMLElement* child = array->FirstChildElement();

	while (child) {
		XMLElement* child2 = child->FirstChildElement();

		while (child2) {
			log("child element = %s", child2->GetText());
			child2 = child2->NextSiblingElement();
		}

		child = child->NextSiblingElement();
	}

	delete doc;

    return true;
}
