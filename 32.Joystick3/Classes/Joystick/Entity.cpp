//
//  Entity.cpp
//  CCActionGame
//
//  Created by hrd321_00 on 13. 7. 12..
//
//

#include "Entity.h"

CEntity *CEntity::create(Scene *scene, const char *pszFileName, const Vec2 &position, int zOrder, Node *parent)
{
	return CEntity::create(scene, NULL, pszFileName, position, zOrder, parent);
}

CEntity *CEntity::create(Scene *scene, CEntity *pobSprite, const char *pszFileName, const Vec2 &position, int zOrder, Node *parent)
{
	if (!pobSprite)
		pobSprite = new CEntity;
	
	if (pobSprite && pobSprite->initWithFile(pszFileName))
    {
        pobSprite->autorelease();
		pobSprite->setPosition(position);
		
        if (parent) {
            parent->addChild(pobSprite, zOrder);
        }
        else {
            scene->addChild(pobSprite, zOrder);
        }
        return pobSprite;
    }
    CC_SAFE_DELETE(pobSprite);
    return NULL;
}
