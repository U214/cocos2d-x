//
//  GameManager.h
//

#pragma once

#include "cocos2d.h"

USING_NS_CC;

class GameManager : public cocos2d::Node
{
public:
	GameManager();
    ~GameManager();

    static GameManager* getInstance();

private:
	int nCount;

public:
	void setCount(int num);
	int getCount();
};
