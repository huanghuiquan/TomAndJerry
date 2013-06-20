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

	CCTexture2D * jerryTextureCache;

	int originSpeed;

	int m_step;

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
	void changePicture(Direction dir, int step);

	void addSpeed( int t );
	void resetSpeed();

	CREATE_FUNC(Jerry);
};

#endif 
