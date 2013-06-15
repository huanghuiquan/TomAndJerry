//
//  PauseLayer.cpp
//  MoonWarriorsx
//
//  Created by �� �� on 13-1-18.
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
	// ��Ŷ��ccc4�����һ����������͸���ȣ��е��
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

// �������̵��ˣ�����ص��������Ŷ
void PauseLayer::doResume(CCObject *pSender)
{
	CCLog("resume!");
}



