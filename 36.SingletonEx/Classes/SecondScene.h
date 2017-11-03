#ifndef __SceneTrans1_SecondScene__
#define __SceneTrans1_SecondScene__

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#pragma execution_character_set("utf-8")
#endif

#include "cocos2d.h"

class SecondScene : public cocos2d::Scene
{
public:

	static cocos2d::Scene* createScene(int num);
	virtual bool init(int num);
	//CREATE_FUNC(SecondScene);

	static SecondScene* create(int num);
	/*{ 
		SecondScene *pRet = new(std::nothrow) SecondScene(); 
		if (pRet && pRet->init()) 
		{ 
			pRet->autorelease(); 
			return pRet; 
		} 
		else 
		{ 
			delete pRet; 
			pRet = nullptr; 
			return nullptr; 
		} 
	};*/

	void doClose(Ref* pSender);
};

#endif // __HELLOWORLD_SCENE_H__
