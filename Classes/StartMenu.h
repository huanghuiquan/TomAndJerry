#ifndef __STARTMENU_H__
#define __STARTMENU_H__

#include "cocos2d.h"
#include "resource.h"
#include "SimpleAudioEngine.h"

class StartMenu : public cocos2d::CCLayer
{
private:
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommand to return the exactly class pointer
    static cocos2d::CCScene* scene();
    
	void menuCallback(CCObject* pSender);

    // a selector callback
    void menuCloseCallback(CCObject* pSender);


    // implement the "static node()" method manually
    CREATE_FUNC(StartMenu);
};

#endif  // __HELLOWORLD_SCENE_H__