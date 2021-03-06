#pragma once

#include "cocos2d.h"
USING_NS_CC;
class Success : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);

	// implement the "static create()" method manually
	CREATE_FUNC(Success);

	Vec2 origin;
};

