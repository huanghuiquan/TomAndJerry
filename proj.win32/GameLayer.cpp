#include "GameLayer.h"
#include "SimpleAudioEngine.h"
#include "resource.h"
#include "Effect.h"
#include "GameOver.h"
#include "PauseLayer.h"
#include "ControlLayer.h"
#include <math.h>

using namespace cocos2d;
using namespace CocosDenshion;

bool isPaused = false;

GameLayer::GameLayer():start(false)
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
		if(!start){ //tom 第一次动，表示开始
			start = true;
			this->schedule(schedule_selector(GameLayer::autoControlJerry),0.01);
		}
	}

	//检测猫是否抓到老鼠
	if(isCatchJerry()){
		gameOver();
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
	CCDirector::sharedDirector()->pause();
	this->addChild(GameOver::create(),10);
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

bool GameLayer::canJerryMove(Direction dir){
	vector<Floor*> floors = m_levelManager->floors;
	int len = floors.size();
	CCRect aRect = m_levelManager->jerry->collideRect();
	CCRect bRect;
	int speed = (m_levelManager->jerry)->getSpeed();
	CCPoint nextPos = (m_levelManager->jerry)->getPosition();

	if(dir == UP){
		nextPos.y +=1;
		if(nextPos.y > winSize.height - m_levelManager->jerry->getContentSize().height/2){
			return false;
		}
		aRect.origin.y += speed;
	}
	else if(dir == DOWN){
		nextPos.y -=1;
		if(nextPos.y < m_levelManager->jerry->getContentSize().height/2){
			return false;
		}
		aRect.origin.y -= speed;
	}
	else if(dir == LEFT){
		nextPos.x -=1;
		if(nextPos.x < m_levelManager->jerry->getContentSize().width/2){
			return false;
		}
		aRect.origin.x -= speed;
	}
	else if(dir == RIGHT){
		nextPos.x +=1;
		if(nextPos.x > winSize.width - m_levelManager->jerry->getContentSize().width){
			return false;
		}
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

bool GameLayer::isCatchJerry()
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

bool GameLayer::isStart(){
	return start;
}

void GameLayer::setStart(){
	start = true;
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

void GameLayer::autoControlJerry(float dt){
	if(canJerryMove(m_levelManager->jerry->getDirection())){
		m_levelManager->jerry->move(m_levelManager->jerry->getDirection());
	}
	else {
		Direction dir = m_levelManager->jerry->getDirection();
		int count = 0;
		while(1){
			count ++;
			dir = (Direction)((dir + 1) % 4);
			if(canJerryMove(dir) && isFartherAwayFromTom(dir)){
				m_levelManager->jerry->move(dir);
				m_levelManager->jerry->setDirection(dir);
				break;
			}
			if(count > 5){
				break;
			}
		}
	}
}

float dist(CCPoint a, CCPoint b){
	return sqrt((float)((a.x - b.x)*(a.x - b.x) + (a.y-b.y)*(a.y-b.y)));
}

bool GameLayer::isFartherAwayFromTom(Direction dir){
	CCPoint tomPos = m_levelManager->tom->getPosition();
	CCPoint jerryPos = m_levelManager->jerry->getPosition();
	CCPoint jerryNextPos = jerryPos;
	float orgDis = dist(tomPos,jerryPos);
	int detectLen = 200;
	if(dir == UP){
		jerryNextPos.y += detectLen;
		if(dist(tomPos, jerryNextPos) > orgDis){
			return true;
		}
	}
	else if(dir == DOWN){
		jerryNextPos.y -= detectLen;
		if(dist(tomPos, jerryNextPos) > orgDis){
			return true;
		}
	}
	else if(dir == RIGHT){
		jerryNextPos.x += detectLen;
		float t = dist(tomPos, jerryNextPos);
		if(dist(tomPos, jerryNextPos) > orgDis){
			return true;
		}
	}
	else if(dir == LEFT){
		jerryNextPos.x -= detectLen;
		if(dist(tomPos, jerryNextPos) > orgDis){
			return true;
		}
	}
	return false;
}

