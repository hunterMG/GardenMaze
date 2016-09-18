#include "MainScene.h"
#include "SettingScene.h"
#include "HelpScene.h"
USING_NS_CC;

Scene* Main::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = Main::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool Main::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();

	/////////////////////////////
	// 2. add a menu item with "X" image, which is clicked to quit the program
	//    you may modify it.

	// add a "close" icon to exit the progress. it's an autorelease object
	auto closeItem = MenuItemImage::create(
		"back.png",
		"back.png",
		CC_CALLBACK_1(Main::menuCloseCallback, this));

	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width / 2,
		origin.y + closeItem->getContentSize().height / 2));

	// create menu, it's an autorelease object
	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	/////////////////////////////
	// 3. add your codes below...
	auto *bg = Sprite::create("hellobg.png");
	bg->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	addChild(bg);
	//开始精灵
	auto startSpriteNormal = Sprite::create("start.png");
	auto startSpriteSelected = Sprite::create("start.png");
	auto startMenuItem = MenuItemSprite::create(startSpriteNormal, startSpriteSelected, CC_CALLBACK_1(Main::menuItemStartCallback, this));
	startMenuItem->setPosition(Vec2(origin.x + visibleSize.width *6/ 9, origin.y + visibleSize.height * 5 / 8));
	//设置图片菜单
	auto  * settingMenuItem = MenuItemImage::create("setting.png", "setting.png", CC_CALLBACK_1(Main::menuItemSettingCallback, this));
	settingMenuItem->setPosition(Vec2(startMenuItem->getPositionX(), visibleSize.height*3/8));
	//帮助图片菜单
	auto *helpMenuItem = MenuItemImage::create("help.png", "help.png", CC_CALLBACK_1(Main::menuItemHelpCallback, this));
	helpMenuItem->setPosition(Vec2(startMenuItem->getPositionX(), visibleSize.height*1/8));
	Menu * mu = Menu::create(startMenuItem, settingMenuItem, helpMenuItem, NULL);
	mu->setPosition(Vec2::ZERO);
	this->addChild(mu);
	displayQR();
	return true;
}

void Main::menuCloseCallback(Ref* pSender)
{
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}

void Main::menuItemStartCallback(Ref *pSender)
{
	MenuItem * item = (MenuItem *)pSender;
	log("Touch start %p", item);
	auto sc = Choose::createScene();
	//Director.getInstance()->replaceScene(sc);
	auto reScene = TransitionMoveInL::create(0.5f, sc);
	Director::getInstance()->pushScene(reScene);
}

void Main::menuItemHelpCallback(Ref *pSender)
{
	MenuItem * item = (MenuItem *)pSender;
	log("Touch help %p", item);
	auto sc = Help::createScene();
	Director::getInstance()->pushScene(sc);
}

void Main::menuItemSettingCallback(Ref * pSender)
{
	auto sc = Setting::createScene();
	//Director.getInstance()->replaceScene(sc);
	auto reScene = TransitionSlideInL::create(0.5f, sc);
	Director::getInstance()->pushScene(reScene);
}
void Main::displayQR()
{
	auto label = Sprite::create("l1.png");
	label->setPosition(Vec2(origin.x + label->getContentSize().width / 2, origin.y + label->getContentSize().height / 2));
	this->addChild(label);
	//将图片加载到精灵帧缓存池
	SpriteFrameCache *m_frameCache = SpriteFrameCache::getInstance();
	m_frameCache->addSpriteFramesWithFile("label.plist", "label.png");
	//用一个列表保存所有的CCSpriteFrameCache
	Vector<SpriteFrame*> frameArray;
	unsigned int i;
	for (i = 1; i <= 4; i++)
	{
		SpriteFrame *frame = m_frameCache->getSpriteFrameByName(__String::createWithFormat("%s%d.png", "l", i)->getCString());
		frameArray.pushBack(frame);
	}

	//使用列表创建动画对象
	Animation *animation = Animation::createWithSpriteFrames(frameArray);
	//表示无限循环播放
	animation->setLoops(-1);
	//每两张图片的时间隔，图片数目越少，间隔最小就越小
	animation->setDelayPerUnit(1.0f);

	//将动画包装成一个动作
	Animate *animate = Animate::create(animation);
	label->runAction(animate);
}
