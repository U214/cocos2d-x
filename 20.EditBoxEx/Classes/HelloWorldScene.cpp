#include "HelloWorldScene.h"

USING_NS_CC;

using namespace cocos2d::extension;

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

	Size editBoxSize = Size(300, 60);

	m_pEditName = EditBox::create(editBoxSize,
		Scale9Sprite::create("extensions/orange_edit.png"));
	m_pEditName->setPosition(Vec2(240, 250));
	m_pEditName->setFontColor(Color3B::GREEN);
	m_pEditName->setPlaceHolder("Name :");
	m_pEditName->setMaxLength(8);
	m_pEditName->setReturnType(EditBox::KeyboardReturnType::DONE);
	m_pEditName->setDelegate(this);
	addChild(m_pEditName);

	m_pEditPassword = EditBox::create(editBoxSize,
		Scale9Sprite::create("extensions/green_edit.png"));
	m_pEditPassword->setPosition(Vec2(240, 150));
	m_pEditPassword->setFontColor(Color3B::RED);
	m_pEditPassword->setPlaceHolder("Password :");
	m_pEditPassword->setMaxLength(6);
	m_pEditPassword->setInputFlag(EditBox::InputFlag::PASSWORD);
	m_pEditPassword->setInputMode(EditBox::InputMode::SINGLE_LINE);
	m_pEditPassword->setDelegate(this);
	addChild(m_pEditPassword);

	m_pEditEmail = EditBox::create(editBoxSize,
		Scale9Sprite::create("extensions/yellow_edit.png"));
	m_pEditEmail->setPosition(Vec2(240, 50));
	m_pEditEmail->setFontColor(Color3B::GREEN);
	m_pEditEmail->setPlaceHolder("Email :");
	m_pEditEmail->setInputMode(EditBox::InputMode::EMAIL_ADDRESS);
	m_pEditEmail->setDelegate(this);
	addChild(m_pEditEmail);

    return true;
}

void HelloWorld::editBoxEditingDidBegin(cocos2d::extension::EditBox* editBox) {
	log("editBox %p DigBegin !", editBox);
}

void HelloWorld::editBoxEditingDidEnd(cocos2d::extension::EditBox* editBox) {
	log("editBox %p DidEnd !", editBox);
}

void HelloWorld::editBoxTextChanged(cocos2d::extension::EditBox* editBox, const std::string& text) {
	log("editBox %p TextChanged, text : %s !", editBox, text.c_str());
}

void HelloWorld::editBoxReturn(cocos2d::extension::EditBox* editBox) {
	log("editBox Return !");
}