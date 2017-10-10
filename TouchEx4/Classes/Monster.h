#ifndef __SPRITEEXTENDEX_MONSTER_H__
#define __SPRITEEXTENDEX_MONSTER_H__

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#pragma execution_character_set("utf-8")
#endif

#include "cocos2d.h"

class Monster : public cocos2d::Sprite
{
public:
	Monster();

	void setPriority(int fixedPriority);
	void setPriorityWithThis(bool useNodePriority);

	virtual void onEnter();
	virtual void onExit();

private:
	cocos2d::EventListener* _listener;
	int _fixedPriority;
	bool _useNodePriority;
};

#endif // __SPRITEEXTENDEX_MONSTER_H__
