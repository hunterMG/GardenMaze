#include "MyGameScene.h"
#include "MainScene.h"
#include "Globle.h"
#include "SimpleAudioEngine.h"
#include "SuccessScene.h"
USING_NS_CC;
using namespace CocosDenshion;
Scene* MyGame::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = MyGame::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}
// on "init" you need to initialize your instance
bool MyGame::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}
	if (musicOn)
	{
		SimpleAudioEngine::getInstance()->playBackgroundMusic(gmName, true);
	}
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	log("visibleSize(%f, %f)", visibleSize.width, visibleSize.height);
	/////////////////////////////
	// 2. add a menu item with "X" image, which is clicked to quit the program
	//    you may modify it.

	// add a "close" icon to exit the progress. it's an autorelease object
	auto closeItem = MenuItemImage::create(
		"back.png",
		"back.png",
		CC_CALLBACK_1(MyGame::menuCloseCallback, this));

	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width / 2,
		origin.y + closeItem->getContentSize().height / 2));

	// create menu, it's an autorelease object
	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 4);
	menu->setTag(123);
	/////////////////////////////
	// 3. add your codes below...

	gameView = Layer::create();
	//瓦片地图
	char* mapname;
	switch (lerver)
	{
	case first:
		mapname = "map/maze01.tmx";
		break;
	case secondd:
		mapname = "map/maze02.tmx";
		break;
	case third:
		mapname = "map/maze03.tmx";
		break;
	case forth:
		mapname = "map/maze04.tmx";
		break;
	default:
		mapname = "map/maze01.tmx";
		break;
	}
	_tileMap = TMXTiledMap::create(mapname);

	gameView->addChild(_tileMap, 0, 100);
	TMXObjectGroup* group = _tileMap->getObjectGroup("objects");
	ValueMap spawnPoint = group->getObject("ninja");

	float x = spawnPoint["x"].asFloat();
	float y = spawnPoint["y"].asFloat();

	hero = Hero::create();
	hero->InitHeroSprite("run1.png");
	hero->setPosition(ccp(x, y));
	gameView->addChild(hero, 1);

	this->addChild(gameView, 0);
	this->scheduleUpdate();

	_background = _tileMap->getLayer("background");
	_end = _tileMap->getLayer("end");
	_collidable = _tileMap->getLayer("collidable");
	_collidable->setVisible(false);

	//防止在手机上地图上下滚动时出现黑线
	_background->getTexture()->setAliasTexParameters();
	_end->getTexture()->setAliasTexParameters();
	_collidable->getTexture()->setAliasTexParameters();

	//摇杆  
	auto tmp = Sprite::create("rockerbg.png");
	rocker = HRocker::createHRocker("rocker.png", "rockerbg.png", Vec2(tmp->getContentSize().width/2, tmp->getContentSize().height/2));
	this->addChild(rocker, 2);
	rocker->startRoker(true);

	setTouchEnabled(true);
	//设置为单点触摸
	setTouchMode(Touch::DispatchMode::ONE_BY_ONE);

	return true;
}
void MyGame::update(float delta)
{
	Point pos = hero->getPosition();
	int dis = 3;
	switch (rocker->rockerDirection)
	{
	case 1:
		pos.x += dis;
		hero->SetAnnimation("run.plist", "run.png", "run", 4, rocker->rockerRun);
		break;
	case 2:
		pos.y += dis;
		hero->SetAnnimation("run.plist", "run.png", "run", 4, rocker->rockerRun);
		break;
	case 3:
		pos.x -= dis;
		hero->SetAnnimation("run.plist", "run.png", "run", 4, rocker->rockerRun);
		break;
	case 4:
		pos.y -= dis;
		hero->SetAnnimation("run.plist", "run.png", "run", 4, rocker->rockerRun);
		break;
	default:
		hero->StopAnimation();
		break;
	}
	this->setPlayerPosition(pos);
}
bool MyGame::check(Point position)
{
	//从像素点坐标转化为瓦片坐标
	Vec2 tileCoord1 = this->tileCoordFromPosition(position);
	//获得瓦片的GID
	int tileGid1 = _end->getTileGIDAt(tileCoord1);
	if (tileGid1 > 0) {
		Value prop = _tileMap->getPropertiesForGID(tileGid1);
		if (!prop.isNull())
		{
			ValueMap propValueMap = prop.asValueMap();
			std::string collision = propValueMap["end"].asString();

			if (collision == "true") { //成功
				log("Success!!!");
				//CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("empty.wav");
				return true;
			}
		}
	}
	else
		return false;
}
bool MyGame::check2(Point position)
{
	//从像素点坐标转化为瓦片坐标
	Vec2 tileCoord1 = this->tileCoordFromPosition(position);
	//获得瓦片的GID
	int tileGid1 = _collidable->getTileGIDAt(tileCoord1);
	if (tileGid1 > 0) {
		Value prop = _tileMap->getPropertiesForGID(tileGid1);
		if (!prop.isNull())
		{
			ValueMap propValueMap = prop.asValueMap();
			std::string collision = propValueMap["Collidable"].asString();
			if (collision == "true") { //成功
				log("collision!!!");
				//CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("empty.wav");
				return true;
			}
		}
	}
	else 
		return false;
}
bool MyGame::isEnded(Vec2 position)
{
	int dis = 20;
	Point pos = Vec2(position.x, position.y);
	Point pos1 = Vec2(position.x , position.y - dis);
	Point pos2 = Vec2(position.x , position.y + dis);
	Point pos3 = Vec2(position.x - dis, position.y );
	Point pos4 = Vec2(position.x + dis, position.y );
	Point pos5 = Vec2(position.x - dis, position.y - dis);
	Point pos6 = Vec2(position.x - dis, position.y + dis);
	Point pos7 = Vec2(position.x + dis, position.y - dis);
	Point pos8 = Vec2(position.x + dis, position.y + dis);
	if (check(pos)||check(pos1)||check(pos2)||check(pos3)||check(pos4) || check(pos5) || check(pos6) || check(pos7) || check(pos8))
		return true;
	else
		return false;
	
}
void MyGame::setPlayerPosition(Vec2 position)
{
	//log("playerPos(%f, %f)", position.x, position.y);
	if (isEnded(position))
	{
		log("end");
		auto sc = Success::createScene();
		Director::getInstance()->replaceScene(sc);
		if (musicOn)
		{
			SimpleAudioEngine::getInstance()->stopBackgroundMusic(gmName);
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(scName);
		}
		return;
	}
	int dis = 20;
	Point pos = Vec2(position.x, position.y);
	Point pos1 = Vec2(position.x, position.y - dis);
	Point pos2 = Vec2(position.x, position.y + dis);
	Point pos3 = Vec2(position.x - dis, position.y);
	Point pos4 = Vec2(position.x + dis, position.y);
	Point pos5 = Vec2(position.x - dis, position.y - dis);
	Point pos6 = Vec2(position.x - dis, position.y + dis);
	Point pos7 = Vec2(position.x + dis, position.y - dis);
	Point pos8 = Vec2(position.x + dis, position.y + dis);
	if (check2(pos)||check2(pos1) || check2(pos2) || check2(pos3) || check2(pos4) || check2(pos5) || check2(pos6) || check2(pos7) || check2(pos8))
		return;

	//移动精灵
	hero->setPosition(position);
	//滚动地图
	this->setViewpointCenter(hero->getPosition());
}

Vec2 MyGame::tileCoordFromPosition(Vec2 pos)
{
	int x = pos.x / _tileMap->getTileSize().width;
	int y = ((_tileMap->getMapSize().height * _tileMap->getTileSize().height) - pos.y) / _tileMap->getTileSize().height;
	return Vec2(x, y);
}

void MyGame::setViewpointCenter(Vec2 position)
{
	//log("setViewpointCenter");
	//log("position (%f ,%f) ", position.x, position.y);

	Size visibleSize = Director::getInstance()->getVisibleSize();
	//可以防止，视图左边超出屏幕之外。
	int x = MAX(position.x, visibleSize.width / 2);
	int y = MAX(position.y, visibleSize.height / 2);
	//可以防止，视图右边超出屏幕之外。
	x = MIN(x, (_tileMap->getMapSize().width * _tileMap->getTileSize().width)
		- visibleSize.width / 2);
	y = MIN(y, (_tileMap->getMapSize().height * _tileMap->getTileSize().height)
		- visibleSize.height / 2);

	//屏幕中心点
	Vec2 pointA = Vec2(visibleSize.width / 2, visibleSize.height / 2);
	//使精灵处于屏幕中心，移动地图目标位置
	Vec2 pointB = Vec2(x, y);
	//log("目标位置 (%f ,%f) ", pointB.x, pointB.y);

	//地图移动偏移量
	Vec2 offset = pointA - pointB;
	//log("offset (%f ,%f) ", offset.x, offset.y);
	gameView->setPosition(offset);

}

void MyGame::menuCloseCallback(Ref* pSender)
{
	if (musicOn)
	{
		SimpleAudioEngine::getInstance()->playBackgroundMusic(bgmName, true);
	}
	Director::getInstance()->popScene();
	/*
	Director::getInstance()->end();

	#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
	#endif
	*/

}
