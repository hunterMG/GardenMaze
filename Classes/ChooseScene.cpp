#include "ChooseScene.h"

USING_NS_CC;

Scene* Choose::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = Choose::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool Choose::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();

	/////////////////////////////
	// 2. add a menu item with "X" image, which is clicked to quit the program
	//    you may modify it.

	// add a "close" icon to exit the progress. it's an autorelease object
	auto closeItem = MenuItemImage::create(
		"back.png",
		"back.png",
		CC_CALLBACK_1(Choose::menuCloseCallback, this));

	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width / 2,
		origin.y + closeItem->getContentSize().height / 2));

	// create menu, it's an autorelease object
	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	/////////////////////////////
	// 3. add your codes below...

	// add "ChooseWorld" splash screen"
	auto sprite = Sprite::create("hellobg.png");

	// position the sprite on the center of the screen
	sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

	// add the sprite as a child to this layer
	this->addChild(sprite, 0);

	buildUI();

	return true;
}
void Choose::buildUI()
{
	//第一关图片
	auto firstSpriteNormal = Sprite::create("first.png");
	auto firstSpriteSelected = Sprite::create("first.png");
	auto firstMenuItem = MenuItemSprite::create(firstSpriteNormal, firstSpriteSelected, CC_CALLBACK_1(Choose::firstLerverCallback, this));
	firstMenuItem->setPosition(Vec2(origin.x + visibleSize.width *3/ 4, origin.y + visibleSize.height * 5 / 8));
	//第二关图片
	auto  * secondMenuItem = MenuItemImage::create("second.png", "second.png", CC_CALLBACK_1(Choose::secondLerverCallback, this));
	secondMenuItem->setPosition(Vec2(firstMenuItem->getPositionX(), origin.y + visibleSize.height * 4 / 8));
	//第三关图片
	auto *thirdMenuItem = MenuItemImage::create("third.png", "third.png", CC_CALLBACK_1(Choose::ThirdLerverCallback, this));
	thirdMenuItem->setPosition(Vec2(firstMenuItem->getPositionX(), origin.y + visibleSize.height * 3 / 8));
	//第四关图片
	auto *forthMenuItem = MenuItemImage::create("forth.png", "forth.png", CC_CALLBACK_1(Choose::ForthLerverCallback, this));
	forthMenuItem->setPosition(Vec2(firstMenuItem->getPositionX(), origin.y + visibleSize.height * 2 / 8));
	Menu * mu = Menu::create(firstMenuItem, secondMenuItem, thirdMenuItem,forthMenuItem, NULL);
	mu->setPosition(Vec2::ZERO);
	this->addChild(mu);
}
void Choose::menuCloseCallback(Ref* pSender)
{
	Director::getInstance()->popScene();
}
void Choose::firstLerverCallback(Ref *pSender)
{
	lerver = first;
	auto gameScene = MyGame::createScene();
	auto reScene = TransitionRotoZoom::create(1.0f, gameScene);
	Director::getInstance()->pushScene(reScene);
}
void Choose::secondLerverCallback(Ref *pSender)
{
	lerver = secondd;
	auto gameScene = MyGame::createScene();
	auto reScene = TransitionRotoZoom::create(1.0f, gameScene);
	Director::getInstance()->pushScene(reScene);
}
void Choose::ThirdLerverCallback(Ref *pSender)
{
	lerver = third;
	auto gameScene = MyGame::createScene();
	auto reScene = TransitionRotoZoom::create(1.0f, gameScene);
	Director::getInstance()->pushScene(reScene);
}
void Choose::ForthLerverCallback(Ref *pSender)
{
	lerver = forth;
	auto gameScene = MyGame::createScene();
	auto reScene = TransitionRotoZoom::create(1.0f, gameScene);
	Director::getInstance()->pushScene(reScene);
}
