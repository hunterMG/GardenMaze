#ifndef __HELLO_SCENE_H__
#define __HELLO_SCENE_H__

#include "cocos2d.h"

#include "MainScene.h"

class Hello : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(Hello);

	void nextScene(float dt);
	//展示齐软图标
	void displayQR();
	Vec2 origin;
};

#endif // __HELLO_SCENE_H__
