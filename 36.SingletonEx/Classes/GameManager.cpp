//
// GameManager.cpp
//

#include "GameManager.h"

GameManager::GameManager()
{
	nCount = 0;
}

GameManager::~GameManager()
{
}

static GameManager* pSingleton;

GameManager* GameManager::getInstance()
{
    if (!pSingleton)
    {
        pSingleton = new GameManager();
    }

    return pSingleton;
}

void GameManager::setCount(int num) {
	nCount = nCount + num;
}

int GameManager::getCount() {
	return nCount;
}