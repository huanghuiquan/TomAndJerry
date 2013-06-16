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

	// ��ʼ��
	virtual bool init();

	// ��ײ����
	virtual CCRect collideRect();

	int getZoder();

	// ������
	CREATE_FUNC(Floor);
};

#endif 
