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

	int speedBonus; //�ٶȼӳ�

	float m_duration; //����ʱ�� 

public:
	Prop(int speedBonus, float appearCircle); //��ʼ���������ڸ��ٶ�
	~Prop();

	virtual bool init();

	virtual CCRect collideRect();// ��ײ����

	virtual int getSpeedBonus();

	float getDuration();
	//CREATE_FUNC(Prop);
};

#endif 
