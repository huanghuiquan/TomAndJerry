#ifndef __TOM_H__
#define __TOM_H__

#include "cocos2d.h"
#include "resource.h"
USING_NS_CC;

class Tom : public CCSprite{
private:
	CCSize winSize;

	CCSize m_size;

	// 速度
	int m_speed;

	CCAction *actions;

	bool isWalking;

	CCTexture2D * TomTextureCache;

	int m_step;


public:
	Tom();
	~Tom();

	// 初始化
	virtual bool init();

	void move(Direction);

	// 碰撞矩形
	virtual CCRect collideRect();

	virtual void update(float dt);

	void setWalkStop();

	int getSpeed();

	void changePicture(Direction dir, int step);

	// 构造器
	CREATE_FUNC(Tom);
};

#endif 
