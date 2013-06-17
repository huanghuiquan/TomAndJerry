#ifndef __TOM_H__
#define __TOM_H__

#include "cocos2d.h"
USING_NS_CC;


enum Direction {UP, DOWN, LEFT, RIGHT, NONE};


class Tom : public CCSprite{
private:
	CCSize m_size;

	// �ٶ�
	int m_speed;

	int m_zOder;
	CCAction *actions;

	bool isWalking;

public:
	Tom();
	~Tom();

	// ��ʼ��
	virtual bool init();

	void move(Direction);

	// ��ײ����
	virtual CCRect collideRect();

	int getZoder();

	virtual void update(float dt);

	void setWalkStop();
	// ������
	CREATE_FUNC(Tom);
};

#endif 
