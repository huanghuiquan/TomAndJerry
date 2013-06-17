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

using namespace std;

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

void PauseLayer::registerWithTouchDispatcher()
{
	// NDK���룬�����ͷ #include <limits>
	// ���ȼ�������Ϊ��С����ô����������ȼ�����������Ϊtrue�������ᱻ�����̵�������Ĳ㲻����յ������¼�
	//int i_min = numeric_limits<int>::min();
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, -2147483648,true);
	CCLayer::registerWithTouchDispatcher();
}

bool PauseLayer::ccTouchBegan(cocos2d::CCTouch *touch, cocos2d::CCEvent *event)
{
	// ��Ϊ�ص��������ˣ�����resumeд��������
	CCRect rect =  menu->getChildByTag(10)->boundingBox();
	if (rect.containsPoint(touch->getLocation())) {
		CCLog("touch play");
		CCDirector::sharedDirector()->resume();
// 		SimpleAudioEngine::sharedEngine()->resumeAllEffects();
// 		SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
		this->removeFromParentAndCleanup(false);
	}
	return true;
}
void PauseLayer::ccTouchMoved(cocos2d::CCTouch *touch, cocos2d::CCEvent *event)
{

}
void PauseLayer::ccTouchEnded(cocos2d::CCTouch *touch, cocos2d::CCEvent *event)
{

}


