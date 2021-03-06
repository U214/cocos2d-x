//
//  Entity.h
//  CCActionGame
//
//  Created by hrd321_00 on 13. 7. 12..
//
//

#pragma once

#include "cocos2d.h"

USING_NS_CC;

class CEntity : public Sprite
{
public:
	static CEntity *create(Scene *scene, const char *pszFileName, const Vec2 &position,
                           int zOrder = 0, Node *parent = NULL);
	static CEntity *create(Scene *scene, CEntity *pobSprite, const char *pszFileName,
                           const Vec2 &position, int zOrder = 0, Node *parent = NULL);
};