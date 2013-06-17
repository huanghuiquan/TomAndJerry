#ifndef __TOM_H__
#define __TOM_H__

#include "cocos2d.h"
USING_NS_CC;

class Tom : public CCSprite{
private:
	CCSize m_size;

	// 速度
	int m_speed;

	int m_zOder;

public:
	Tom();
	~Tom();

	// 初始化
	virtual bool init();

	void moveTo(CCPoint);

	// 碰撞矩形
	virtual CCRect collideRect();

	int getZoder();

	// 构造器
	CREATE_FUNC(Tom);
};

#endif 
