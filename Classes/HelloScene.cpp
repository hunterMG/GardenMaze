#include "HelloScene.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;
using namespace CocosDenshion;
Scene* Hello::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = Hello::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool Hello::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();
    /////////////////////////////
    // 3. add your codes below...

    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("hello.png");
	if (musicOn)
	{
		SimpleAudioEngine::getInstance()->playBackgroundMusic("music/mein.wav");
	}
    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(sprite, 0);

	displayQR();
    //2s后切换进入主场景
	scheduleOnce(schedule_selector(Hello::nextScene), 2.0f);
    return true;
}

void Hello::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
void Hello::nextScene(float dt)
{
	auto mainScene = Main::createScene();
	Director::getInstance()->replaceScene(mainScene);
}
void Hello::displayQR()
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