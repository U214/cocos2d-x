#include "Monster.h"

USING_NS_CC;

Monster::Monster()
	: _listener(nullptr)
	, _fixedPriority(0)
	, _useNodePriority(false) {
	bool b0k = initWithTexture(nullptr, Rect::ZERO);
	if (b0k) {
		this->autorelease();
	}
}

void Monster::setPriority(int fixedPriority) {
	_fixedPriority = fixedPriority;
	_useNodePriority = false;
}

void Monster::setPriorityWithThis(bool useNodePriority) {
	_useNodePriority = useNodePriority;
}

void Monster::onEnter() {
	Sprite::onEnter();

	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);

	listener->onTouchBegan = [=](Touch* touch, Event* event) {
		log("touch began");

		Vec2 locationInNode = this->convertToNodeSpace(touch->getLocation());
		Size s = this->getContentSize();
		Rect rect = Rect(0, 0, s.width, s.height);

		if (rect.containsPoint(locationInNode)) {
			this->setColor(Color3B::RED);
			return true;
		}
		return false;
	};

	listener->onTouchMoved = [=](Touch* touch, Event* event) {
	};

	listener->onTouchEnded = [=](Touch* touch, Event* event) {
		this->setColor(Color3B::WHITE);
	};

	if (_useNodePriority) {
		_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	}
	else {
		_eventDispatcher->addEventListenerWithFixedPriority(listener, _fixedPriority);
	}
	_listener = listener;
}

void Monster::onExit() {
	_eventDispatcher->removeEventListener(_listener);
	Sprite::onExit();
}