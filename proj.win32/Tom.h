#ifndef __TOM_H__
#define __TOM_H__

#include "cocos2d.h"
USING_NS_CC;


enum Direction {UP, DOWN, LEFT, RIGHT, NONE};


class Tom : public CCSprite{
private:
	CCSize m_size;

	// 速度
	int m_speed;

	int m_zOder;
	CCAction *actions;

	bool isWalking;

public:
	Tom();
	~Tom();

	// 初始化
	virtual bool init();

	void move(Direction);

	// 碰撞矩形
	virtual CCRect collideRect();

	int getZoder();

	virtual void update(float dt);

	void setWalkStop();
	// 构造器
	CREATE_FUNC(Tom);
};

#endif 
