#ifndef __TOM_H__
#define __TOM_H__

#include "cocos2d.h"
#include "resource.h"
USING_NS_CC;

class Tom : public CCSprite{
private:
	CCSize winSize;

	CCSize m_size;

	// �ٶ�
	int m_speed;

	CCAction *actions;

	bool isWalking;

	CCTexture2D * TomTextureCache;

	int m_step;


public:
	Tom();
	~Tom();

	// ��ʼ��
	virtual bool init();

	void move(Direction);

	// ��ײ����
	virtual CCRect collideRect();

	virtual void update(float dt);

	void setWalkStop();

	int getSpeed();

	void changePicture(Direction dir, int step);

	// ������
	CREATE_FUNC(Tom);
};

#endif 
