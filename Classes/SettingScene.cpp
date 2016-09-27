#include "SettingScene.h"
#include "SimpleAudioEngine.h"
#include "Globle.h"
USING_NS_CC;
using namespace CocosDenshion;

Scene* Setting::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = Setting::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool Setting::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	/////////////////////////////
	// 2. add a menu item with "X" image, which is clicked to quit the program
	//    you may modify it.

	// add a "close" icon to exit the progress. it's an autorelease object
	auto closeItem = MenuItemImage::create(
		"back.png",
		"back.png",
		CC_CALLBACK_1(Setting::menuCloseCallback, this));

	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width / 2,
		origin.y + closeItem->getContentSize().height / 2));

	// create menu, it's an autorelease object
	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	/////////////////////////////
	// 3. add your codes below...
	auto *bg = Sprite::create("settingbg.png");
	bg->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	addChild(bg);

	//音效
	/*auto soundOnMenuItem = MenuItemImage::create("on.png", "on.png");
	auto soundOffMenuItem = MenuItemImage::create("off.png", "off.png");
	auto soundToggleMenuItem = MenuItemToggle::createWithCallback(CC_CALLBACK_1(Setting::menuSoundToggleCallback, this), soundOnMenuItem, soundOffMenuItem, NULL);
	auto center = Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);
	soundToggleMenuItem->setPosition(center.x, visibleSize.height*4);*/
	//音乐
	if (musicOn == true)
	{
		auto musicOnMenuItem = MenuItemImage::create("on.png", "on.png");
		auto musicOffMenuItem = MenuItemImage::create("off.png", "off.png");
		auto musicToggleMenuItem = MenuItemToggle::createWithCallback(CC_CALLBACK_1(Setting::menuMusicToggleCallback, this), musicOnMenuItem, musicOffMenuItem, NULL);
		musicToggleMenuItem->setPosition(visibleSize.width / 2, visibleSize.height / 2);
		//OK按钮
		auto okMenuItem = MenuItemImage::create("ok.png", "ok.png", CC_CALLBACK_1(Setting::menuOkCallback, this));
		okMenuItem->setPosition(visibleSize.width / 2, visibleSize.height / 3);
		Menu * mn = Menu::create(musicToggleMenuItem, okMenuItem, NULL);
		mn->setPosition(Vec2::ZERO);
		addChild(mn);
	}
	else
	{
		auto musicOffMenuItem = MenuItemImage::create("on.png", "on.png");
		auto musicOnMenuItem = MenuItemImage::create("off.png", "off.png");
		auto musicToggleMenuItem = MenuItemToggle::createWithCallback(CC_CALLBACK_1(Setting::menuMusicToggleCallback, this), musicOnMenuItem, musicOffMenuItem, NULL);
		musicToggleMenuItem->setPosition(visibleSize.width / 2, visibleSize.height / 2);
		//OK按钮
		auto okMenuItem = MenuItemImage::create("ok.png", "ok.png", CC_CALLBACK_1(Setting::menuOkCallback, this));
		okMenuItem->setPosition(visibleSize.width / 2, visibleSize.height / 3);
		Menu * mn = Menu::create(musicToggleMenuItem, okMenuItem, NULL);
		mn->setPosition(Vec2::ZERO);
		addChild(mn);
	}
	return true;
}

void Setting::menuCloseCallback(Ref* pSender)
{
	Director::getInstance()->popScene();
}

void Setting::menuSoundToggleCallback(cocos2d::Ref * pSender)
{
}

void Setting::menuMusicToggleCallback(cocos2d::Ref * pSender)
{
	/*
	auto musicToggleMenuItem = (MenuItemToggle *)pSender;
	if (musicToggleMenuItem->getSelectedIndex() == 1)
	{
	SimpleAudioEngine::getInstance()->stopBackgroundMusic("music/mein.wav");
	//::getInstance()->setBackgroundMusicVolume(0);
	}
	else {
	SimpleAudioEngine::getInstance()->playBackgroundMusic("music/mein.wav");
	}
	*/
	if (musicOn)
	{
		SimpleAudioEngine::getInstance()->stopBackgroundMusic(bgmName);
	}
	else
	{
		SimpleAudioEngine::getInstance()->playBackgroundMusic(bgmName, true);

	}
	musicOn = !musicOn;
}

void Setting::menuOkCallback(cocos2d::Ref * pSender)
{
	Director::getInstance()->popScene();
}
