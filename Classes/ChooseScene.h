#ifndef __CHOOSE_SCENE_H__
#define __CHOOSE_SCENE_H__

#include "cocos2d.h"
#include "MyGameScene.h"
#include "Globle.h"
//用于选择关卡的场景
class Choose : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);

	// implement the "static create()" method manually
	CREATE_FUNC(Choose);

	void buildUI();
	void firstLerverCallback(Ref *pSender);
	void secondLerverCallback(Ref *pSender);
	void ThirdLerverCallback(Ref *pSender);
	void ForthLerverCallback(Ref *pSender);
	Size visibleSize;
	Vec2 origin;

};

#endif // __CHOOSE_SCENE_H__
