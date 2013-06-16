#ifndef __FLOOR_H__
#define __FLOOR_H__

#include "cocos2d.h"
USING_NS_CC;

class Floor : public CCSprite{
private:
	CCSize m_size;
	int m_zOder;

public:
	Floor();
	~Floor();

	// 初始化
	virtual bool init();

	// 碰撞矩形
	virtual CCRect collideRect();

	int getZoder();

	// 构造器
	CREATE_FUNC(Floor);
};

#endif 
