#ifndef __CONTROLLAYER_H__
#define __CONTROLLAYER_H__

#include "cocos2d.h"
#include "Tom.h"
USING_NS_CC;

class ControlLayer : public CCLayer  
{  
private:  
	CCPoint centre;  
	CCSprite *yg2;//ҡ��СԲȦ,�����д�������Ϊ�������������õ�,���񱳾�ֻ��Ҫ��ʼ�����ؾ���  
	float radius;  
	Direction curDir;
	//�������  
	Tom* tom;
	float speedX;  
	float speedY;  
	bool isMove;  

public:  
	virtual bool init();  
	void setControledSprite(CCSprite* pSprite);
	//������صĴ�����  
	virtual void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);  
	virtual void ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent);  
	virtual void ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent);  
	virtual void update(float dt);
	CREATE_FUNC(ControlLayer);
	//CREATE_FUNC(ControlLayer);  

};  

#endif