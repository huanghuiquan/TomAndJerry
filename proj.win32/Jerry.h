#ifndef __JERRY_H__
#define __JERRY_H__

#include "cocos2d.h"
USING_NS_CC;

class Jerry : public CCSprite{
private:
	CCSize m_size;

	// �ٶ�
	int m_speed;

	int m_zOder;

public:
	Jerry();
	~Jerry();

	// ��ʼ��
	virtual bool init();

	// ��ײ����
	virtual CCRect collideRect();

	int getZoder();

	// ������
	CREATE_FUNC(Jerry);
};

#endif 
