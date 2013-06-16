#ifndef __JERRY_H__
#define __JERRY_H__

#include "cocos2d.h"
USING_NS_CC;

class Jerry : public CCSprite{
private:
	CCSize m_size;

	// 速度
	int m_speed;

	int m_zOder;

public:
	Jerry();
	~Jerry();

	// 初始化
	virtual bool init();

	// 碰撞矩形
	virtual CCRect collideRect();

	int getZoder();

	// 构造器
	CREATE_FUNC(Jerry);
};

#endif 
