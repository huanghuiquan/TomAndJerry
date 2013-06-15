//
//  PauseLayer.cpp
//  MoonWarriorsx
//
//  Created by 王 磊 on 13-1-18.
//
//

#include "PauseLayer.h"
#include "SimpleAudioEngine.h"
#include <limits>
#include "resource.h"

using namespace CocosDenshion;

CCMenu *menu;
bool PauseLayer::init()
{
	// 擦哦，ccc4的最后一个参数才是透明度，有点坑
	if (!CCLayerColor::initWithColor(ccc4(0, 0, 0, 100))) {
		return  false;
	}
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	CCMenuItemImage *play = CCMenuItemImage::create(s_play, s_play);
	play->setAnchorPoint(ccp(1, 0));
	play->setTag(10);
	play->setPosition(ccp(winSize.width, 0));


	menu = CCMenu::create(play, NULL);
	menu->setAnchorPoint(ccp(0, 0));
	addChild(menu, 1, 10);
	menu->setPosition(CCPointZero);

	return true;
}

// 触摸被吞掉了，这个回调不会调用哦
void PauseLayer::doResume(CCObject *pSender)
{
	CCLog("resume!");
}



