#ifndef __GameLayer_H__
#define __GameLayer_H__

#include "cocos2d.h"
#include "LevelManager.h"
#include "ControlLayer.h"
USING_NS_CC;

enum Sate{
	statePlaying = 0,
	stateGameOver= 1,
};

class GameLayer : public CCLayer {

private:
	CCSize winSize;
	LevelManager *m_levelManager;
	Direction ygDir;
	ControlLayer *controlLayer;
	bool start;

public:
	GameLayer();
	~GameLayer();
	virtual bool init();
	virtual void update(float dt);
	void gameOver();
	void doPause(CCObject *pSender);
	void initBackground();
	bool isStart();
	void setStart();
	void menuCloseCallback(CCObject* pSender);
	virtual void onEnter();
	virtual void onExit();
	virtual bool ccTouchBegan(CCTouch* touch, CCEvent* event);
	virtual void ccTouchMoved(CCTouch* touch, CCEvent* event);
	virtual void ccTouchEnded(CCTouch* touch, CCEvent* event);
	//检测Tom是否可以移到下个方向
	bool canTomMove(Direction);
	bool isCatchJerry();
	bool canJerryMove(Direction);

	//Jerry 自动控制函数
	void autoControlJerry(float);

	bool isFartherAwayFromTom(Direction dir); 

	CREATE_FUNC(GameLayer);
};

#endif 
