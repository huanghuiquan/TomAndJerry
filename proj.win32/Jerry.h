#ifndef __JERRY_H__
#define __JERRY_H__

#include "cocos2d.h"
#include "resource.h"
USING_NS_CC;

class Jerry : public CCSprite{
private:
	CCSize winSize;

	CCSize m_size;

	int m_speed; // ËÙ¶È

	CCAction *actions;

	bool isWalking;

	Direction curDir;

public:
	Jerry();
	~Jerry();
	virtual bool init();

	virtual CCRect collideRect();// Åö×²¾ØÐÎ

	void move(Direction);	

	void setWalkStop();

	int getSpeed();

	Direction getDirection();
	void setDirection(Direction dir);

	CREATE_FUNC(Jerry);
};

#endif 
