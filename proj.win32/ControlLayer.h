#ifndef __CONTROLLAYER_H__
#define __CONTROLLAYER_H__

#include "cocos2d.h"
#include "Tom.h"
#include "Floor.h"
#include "Jerry.h"
#include "resource.h"
USING_NS_CC;

class ControlLayer : public CCLayer  
{  
private:  
	CCPoint centre;  
	CCSprite *yg2;//摇杆小圆圈,在类中创建是因为其他函数还会用到,不像背景只需要初始化加载就行  
	float radius;  
	Direction curDir;
	//精灵相关  
	Tom* tom;
	bool isMove;  

public:  
	virtual bool init();  
	void setControledSprite(CCSprite* pSprite);
	//触摸相关的处理函数  
	virtual void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);  
	virtual void ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent);  
	virtual void ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent);  
	virtual void update(float dt);
	Direction getYgDirection();

	CREATE_FUNC(ControlLayer);
	//CREATE_FUNC(ControlLayer);  

};  

#endif