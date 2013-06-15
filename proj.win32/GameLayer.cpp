//
//  GameLayer.cpp
//  MoonWarriorsx
//
//  Created by 王 磊 on 12-12-29.
//
//

#include "GameLayer.h"
#include "SimpleAudioEngine.h"
#include "resource.h"
#include "Effect.h"
#include "GameOver.h"
#include "PauseLayer.h"


using namespace cocos2d;
using namespace CocosDenshion;


bool isPaused = false;

GameLayer::GameLayer()
{

}
GameLayer::~GameLayer()
{
}

bool GameLayer::init()
{
	if (!CCLayer::init()) {
		return false;
	}

	return true;
}



void GameLayer::update(float dt)
{


}


void GameLayer::checkIsCollide()
{

}



bool GameLayer::collide(CCSprite *a, CCSprite *b)
{
	if(!a || !b)
	{
		return false;
	}
	//CCRect aRect = a->collideRect();
	//CCRect bRect = b->collideRect();
	//if (aRect.intersectsRect(bRect)) {
	//	return true;
	//}
	return false;
}

void GameLayer::updateUI()
{

}

void GameLayer::onEnter()
{
	CCDirector* pDirector = CCDirector::sharedDirector();
	pDirector->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
	CCLayer::onEnter();
}

void GameLayer::onExit()
{
	CCDirector* pDirector = CCDirector::sharedDirector();
	pDirector->getTouchDispatcher()->removeDelegate(this);
	CCLayer::onExit();
}


// 无限滚动地图，采用两张图循环加载滚动
void GameLayer::initBackground()
{

}

void GameLayer::gameOver()
{
	CCScene * scene = GameOver::scene();
	CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(1.2, scene));
}

void GameLayer::doPause(CCObject *pSender)
{
	CCDirector::sharedDirector()->pause();
	SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
	SimpleAudioEngine::sharedEngine()->pauseAllEffects();
	PauseLayer *pauseLayer = PauseLayer::create();
	addChild(pauseLayer,9999);
}
