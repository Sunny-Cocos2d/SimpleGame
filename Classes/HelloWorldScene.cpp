#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
  // 'scene' is an autorelease object
  auto scene = Scene::create();
  
  // 'layer' is an autorelease object
  auto layer = HelloWorld::create();
  
  // add layer as a child to scene
  scene->addChild(layer);
  
  // return the scene
  return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
  //////////////////////////////
  // 1. super init first
  if ( !Layer::init() )
  {
    return false;
  }
  
  auto visibleSize = Director::getInstance()->getVisibleSize();
  Vec2 origin = Director::getInstance()->getVisibleOrigin();
  
  auto background = DrawNode::create();
  background->drawSolidRect(origin, visibleSize, Color4F(0.6,0.6,0.6,1.0));
  this->addChild(background);
  
  // 4
  _player = Sprite::create("player.png");
  _player->setPosition(Vec2(visibleSize.width * 0.1, visibleSize.height * 0.5));
  this->addChild(_player);
  
  return true;
}

void HelloWorld::addMonster(float dt) {
  auto monster = Sprite::create("monster.png");
  
  // 1
  auto monsterContentSize = monster->getContentSize();
  auto selfContentSize = this->getContentSize();
  int minY = monsterContentSize.height/2;
  int maxY = selfContentSize.height - monsterContentSize.height/2;
  int rangeY = maxY - minY;
  int randomY = (rand() % rangeY) + minY;
  
  monster->setPosition(Vec2(selfContentSize.width + monsterContentSize.width/2, randomY));
  this->addChild(monster);
  
  // 2
  int minDuration = 2.0;
  int maxDuration = 4.0;
  int rangeDuration = maxDuration - minDuration;
  int randomDuration = (rand() % rangeDuration) + minDuration;
  
  // 3
  auto actionMove = MoveTo::create(randomDuration, Vec2(-monsterContentSize.width/2, randomY));
  auto actionRemove = RemoveSelf::create();
  monster->runAction(Sequence::create(actionMove,actionRemove, nullptr));
}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
  //Close the cocos2d-x game scene and quit the application
  Director::getInstance()->end();
  
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
  exit(0);
#endif
  
}
