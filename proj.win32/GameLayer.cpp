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
#include "ControlLayer.h"

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

	CCLOG("Game Init...");

	winSize = CCDirector::sharedDirector()->getWinSize();
	m_levelManager = new LevelManager(this);
	initBackground();

	//pause item
	CCMenuItemImage *pause = CCMenuItemImage::create(s_pause, s_pause, this, menu_selector(GameLayer::doPause));
	pause->setAnchorPoint(ccp(1, 0));
	pause->setPosition(ccp(winSize.width, 0));
	CCMenu *menu = CCMenu::create(pause, NULL);
	menu->setAnchorPoint(ccp(0, 0));
	addChild(menu, 1, 10);
	menu->setPosition(CCPointZero);

	m_levelManager->loadLevelResource(1);
	controlLayer = ControlLayer::create();
	controlLayer->setControledSprite(m_levelManager->tom);
	this->addChild(controlLayer,9999);

	this->scheduleUpdate();
	
	return true;
}

void GameLayer::update(float dt)
{
	// 控制Tom的移动
	ygDir = controlLayer->getYgDirection();
	canTomMove(ygDir);
	if(ygDir != NONE && canTomMove(ygDir)){
		m_levelManager->tom->move(ygDir);
	}

	//检测猫是否抓到老鼠
	if(isCatchJerry()){
		gameOver();
// 		CCDirector::sharedDirector()->pause();
// 		CCDirector::sharedDirector()->resume();

		//SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
		//SimpleAudioEngine::sharedEngine()->pauseAllEffects();
// 		GameOver *gameOver = GameOver::create();
// 		addChild(gameOver,9999);
	}
}

void GameLayer::initBackground()
{
	CCSprite *background = CCSprite::create(s_gameBg);
	background->setPosition(ccp(winSize.width / 2, winSize.height / 2));
	addChild(background, 0);
}

void GameLayer::gameOver()
{
	CCScene * scene = GameOver::scene();
	CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5, scene));
}

void GameLayer::doPause(CCObject *pSender)
{
	CCDirector::sharedDirector()->pause();
	//SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
	//SimpleAudioEngine::sharedEngine()->pauseAllEffects();
	PauseLayer *pauseLayer = PauseLayer::create();
	addChild(pauseLayer,9999);
}

void GameLayer::menuCloseCallback(CCObject* pSender)
{
	// "close" menu item clicked
	CCDirector::sharedDirector()->end();
}

bool GameLayer::canTomMove(Direction dir){
	vector<Floor*> floors = m_levelManager->floors;
	int len = floors.size();
	CCRect aRect = m_levelManager->tom->collideRect();
	CCRect bRect;
	int speed = (m_levelManager->tom)->getSpeed();
	if(dir == UP){
		aRect.origin.y += speed;
	}
	else if(dir == DOWN){
		aRect.origin.y -= speed;
	}
	else if(dir == LEFT){
		aRect.origin.x -= speed;
	}
	else if(dir == RIGHT){
		aRect.origin.x += speed;
	}

	for(int i = 0; i < len; i++){
		bRect = floors.at(i)->collideRect();
		if (aRect.intersectsRect(bRect)) {
			return false;
		}
	}
	return true;
}

float GameLayer::isCatchJerry()
{
	CCRect aRect = m_levelManager->tom->collideRect();
	CCRect bRect = m_levelManager->jerry->collideRect();
	if (aRect.intersectsRect(bRect)) {
		return true;
	}
	return false;
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


bool GameLayer::ccTouchBegan(CCTouch *touch, CCEvent *event)
{
	return false;
}

void GameLayer::ccTouchMoved(cocos2d::CCTouch *touch, cocos2d::CCEvent *event)
{
}

void GameLayer::ccTouchEnded(cocos2d::CCTouch *touch, cocos2d::CCEvent *event)
{
	//    CCLog("touch end!");
}
