#pragma once

#include "cocos2d.h"
USING_NS_CC;
class Help : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);

	// implement the "static create()" method manually
	CREATE_FUNC(Help);

	//展示齐软图标
	void displayQR();
	Vec2 origin;
};

