#ifndef __MAIN_SCENE_H__
#define __MAIN_SCENE_H__

#include "cocos2d.h"
#include "MyGameScene.h"
#include "ChooseScene.h"
typedef enum {
	PLACE_TAG = 102,
	FLIPX_TAG,
	FLIPY_TAG,
	HIDE_SHOW_TAG,
	TOGGLE_TAG
} ActionTypes;

class Main: public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);

	void menuItemStartCallback(Ref * pSender);

	void menuItemHelpCallback(Ref * pSender);

	void menuItemSettingCallback(Ref * pSender);

	// implement the "static create()" method manually
	CREATE_FUNC(Main);
};

#endif // __MAIN_SCENE_H__
