#ifndef __TOM_H__
#define __TOM_H__

#include "cocos2d.h"
USING_NS_CC;

class Tom : public CCSprite{
private:
	CCSize m_size;

	// �ٶ�
	int m_speed;

	int m_zOder;

public:
	Tom();
	~Tom();

	// ��ʼ��
	virtual bool init();

	void moveTo(CCPoint);

	// ��ײ����
	virtual CCRect collideRect();

	int getZoder();

	// ������
	CREATE_FUNC(Tom);
};

#endif 
