#ifndef __MYGAME_SCENE_H__
#define __MYGAME_SCENE_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "HRocker.h"
#include "Hero.h"
class MyGame : public cocos2d::Layer
{
	Layer *gameView;//将_player和_tileMap添加到这一个节点中，方便滚动地图时同时改变位置，同时摇杆位置不动
	HRocker *rocker;
	cocos2d::TMXTiledMap* _tileMap;
	cocos2d::TMXLayer* _collidable;
	cocos2d::TMXLayer* _end;
	TMXLayer* _background;
	cocos2d::Sprite *_player;
	Hero *hero;
public:
	static cocos2d::Scene* createScene();

	virtual bool init();
	//判断是否到达终点
	bool isEnded(Vec2 pos);
	bool check(Point position);
	bool check2(Point position);
	virtual void update(float delta);

	void setPlayerPosition(cocos2d::Vec2 position);
	cocos2d::Vec2 tileCoordFromPosition(cocos2d::Vec2 position);
	void setViewpointCenter(cocos2d::Vec2 position);

	void menuCloseCallback(Ref * pSender);

	// implement the "static create()" method manually
	CREATE_FUNC(MyGame);
};

#endif // __MYGAME_SCENE_H__
