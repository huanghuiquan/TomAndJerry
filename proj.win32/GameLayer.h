#ifndef __GameLayer_H__
#define __GameLayer_H__

#include "cocos2d.h"
#include "LevelManager.h"
USING_NS_CC;

enum Sate{
	statePlaying = 0,
	stateGameOver= 1,
};


class GameLayer : public CCLayer {

private:
	CCSize winSize;
	LevelManager *m_levelManager;

public:
	GameLayer();
	~GameLayer();
	virtual bool init();
	virtual void update(float dt);
	void checkIsCollide();
	bool collide(CCSprite *a, CCSprite *b);
	void updateUI();
	void gameOver();
	void doPause(CCObject *pSender);
// 	virtual void onEnter();
// 	virtual void onExit();
	void initBackground();
	void menuCloseCallback(CCObject* pSender);

	CREATE_FUNC(GameLayer);
};

#endif 
