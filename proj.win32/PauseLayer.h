#ifndef __PauseLayer__
#define __PauseLayer__

#include "cocos2d.h"
USING_NS_CC;

class PauseLayer : public CCLayerColor {

public:
	virtual bool init();

	void doResume(CCObject *pSender);
	CREATE_FUNC(PauseLayer);
};


#endif /* defined(__MoonWarriorsx__PauseLayer__) */
