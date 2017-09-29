#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

//USING_NS_CC;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#define EFFECT_FILE		"Sounds/effect2.ogg"
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_MARMALADE)
#define EFFECT_FILE		"Sounds/effect1.raw"
#else
#define	EFFECT_FILE		"Sounds/effect1.wav"
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#define	MUSIC_FILE		"Sounds/music.mid"
#elif(CC_TARGET_PLATFORM == CC_PLATFORM_BLACKBERRY)
#define	MUSIC_FILE		"Sounds/background.ogg"
#else
#define	MUSIC_FILE		"Sounds/background.mp3"
#endif // (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)

std::string menuItems[] = {
	"play background music",
	"pause background music",
	"resume background music",
	"stop background music",
	"play effect",
	"play effect repeatly",
	"pause effect",
	"resume effect",
	"stop effect"
};

using namespace cocos2d;
using namespace CocosDenshion;

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
	auto pMenu = Menu::create();
	int nMenuCount = sizeof(menuItems) / sizeof(menuItems[0]);

	for (int i = 0; i < nMenuCount; ++i) {
		auto label = LabelTTF::create(menuItems[i].c_str(), "Arial", 24);
		label->setColor(Color3B::BLACK);
		auto pMenuItem = MenuItemLabel::create(
			label,
			CC_CALLBACK_1(HelloWorld::doSoundActon, this));
		pMenu->addChild(pMenuItem, i + 10000);
	}

	pMenu->alignItemsVertically();

	this->addChild(pMenu);

	SimpleAudioEngine::getInstance()->preloadBackgroundMusic(MUSIC_FILE);
	SimpleAudioEngine::getInstance()->preloadEffect(EFFECT_FILE);

	SimpleAudioEngine::getInstance()->setEffectsVolume(0.5);
	SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.5);

    return true;
}

void HelloWorld::onExit() {
	SimpleAudioEngine::getInstance()->unloadEffect(EFFECT_FILE);
	SimpleAudioEngine::getInstance()->stopBackgroundMusic(true);

	SimpleAudioEngine::getInstance()->end();

	Scene::onExit();
}

void HelloWorld::doSoundActon(Ref* pSender) {
	auto pMenuItem = (MenuItem *)(pSender);
	int nIdx = pMenuItem->getLocalZOrder() - 10000;

	switch (nIdx)
	{
	case 0:
		SimpleAudioEngine::getInstance()->playBackgroundMusic(MUSIC_FILE, true);
		break;

	case 1:
		SimpleAudioEngine::getInstance()->pauseBackgroundMusic(); // 윈도우에서 동작x
		break;

	case 2:
		SimpleAudioEngine::getInstance()->resumeBackgroundMusic(); // 윈도우에서 동작x
		break;

	case 3:
		SimpleAudioEngine::getInstance()->stopBackgroundMusic();
		break;

	case 4:
		SimpleAudioEngine::getInstance()->playEffect(EFFECT_FILE);
		break;

	case 5:
		SimpleAudioEngine::getInstance()->playEffect(EFFECT_FILE, true);
		break;

	case 6:
		SimpleAudioEngine::getInstance()->pauseEffect(m_nSoundId);
		break;

	case 7:
		SimpleAudioEngine::getInstance()->resumeEffect(m_nSoundId);
		break;

	case 8:
		SimpleAudioEngine::getInstance()->stopEffect(m_nSoundId);
		break;
	default:
		break;
	}
}