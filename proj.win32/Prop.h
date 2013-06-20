#ifndef __PROP_H__
#define __PROP_H__

#include "cocos2d.h"
#include "resource.h"
USING_NS_CC;

class Prop : public CCSprite{
protected:
	CCSize winSize;

	CCSize m_size;

	CCTexture2D *propTextureCache;

	int speedBonus; //速度加成

	float m_duration; //出现时间 

public:
	Prop(int speedBonus, float appearCircle); //初始化出现周期跟速度
	~Prop();

	virtual bool init();

	virtual CCRect collideRect();// 碰撞矩形

	virtual int getSpeedBonus();

	float getDuration();
	//CREATE_FUNC(Prop);
};

#endif 
