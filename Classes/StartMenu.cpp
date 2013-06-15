#include "StartMenu.h"

using namespace cocos2d;

CCScene* StartMenu::scene()
{
    CCScene * scene = NULL;
    do 
    {
        // 'scene' is an autorelease object
        scene = CCScene::create();
        CC_BREAK_IF(! scene);

        // 'layer' is an autorelease object
        StartMenu *layer = StartMenu::create();
        CC_BREAK_IF(! layer);

        // add layer as a child to scene
        scene->addChild(layer);
    } while (0);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool StartMenu::init()
{
    bool bRet = false;
    do 
    {
        CC_BREAK_IF(! CCLayer::init());

		CCSize winSize = CCDirector::sharedDirector()->getWinSize();
		
		CCSprite* newGameNormal = CCSprite::create(s_menu, CCRectMake(0, 0, 126, 33));
		CCSprite* newGameSelected = CCSprite::create(s_menu, CCRectMake(0, 33, 126, 33));
		CCSprite* newGameDisabled = CCSprite::create(s_menu, CCRectMake(0, 33*2, 126, 33));

		CCSprite* gameSettingNormal = CCSprite::create(s_menu, CCRectMake(126, 0, 126, 33));
		CCSprite* gameSettingNSelected = CCSprite::create(s_menu, CCRectMake(126, 33, 126, 33));
		CCSprite* gameSettingDesabled = CCSprite::create(s_menu, CCRectMake(126, 33*2, 126, 33));

		CCSprite* aboutNormal = CCSprite::create(s_menu, CCRectMake(252, 0, 126, 33));
		CCSprite* aboutSelected = CCSprite::create(s_menu, CCRectMake(252, 33, 126, 33));
		CCSprite* aboutDesabled = CCSprite::create(s_menu, CCRectMake(252, 33*2, 126, 33));

		CCMenuItemSprite* newGame = CCMenuItemSprite::create(newGameNormal, newGameSelected, newGameDisabled, this, menu_selector(StartMenu::menuCallback));
		CCMenuItemSprite* gameSetting = CCMenuItemSprite::create(gameSettingNormal, gameSettingNSelected, gameSettingDesabled, this, menu_selector(StartMenu::menuCallback));
		CCMenuItemSprite* about = CCMenuItemSprite::create(aboutNormal, aboutSelected, aboutDesabled, this, menu_selector(StartMenu::menuCallback));

		gameSetting->setTag(1);
		about->setTag(2);

		CCMenu* menu = CCMenu::create(newGame, gameSetting, about, NULL);
		menu->alignItemsVerticallyWithPadding(20);
		this->addChild(menu);
		menu->setPosition(ccp(winSize.width / 2, winSize.height / 2 - 80));
		//this->schedule(schedule_selector(StartMenu::update), 0.1);

		bRet = true;
    } while (0);

    return bRet;
}

void StartMenu::menuCallback(CCObject* pSender)
{
	switch(((CCNode*)pSender)->getTag()){
	case 1:// 进入游戏
		CCLog("Into Game");
		//CCDirector::sharedDirector()->replaceScene(GameLayer::scene());
		break;
	case 2://进入帮助
		CCLog("Into About");
		//CCDirector::sharedDirector()->replaceScene(About::scene());
		break;
	case 3:
		CCDirector::sharedDirector()->end();
	};  

}

void StartMenu::menuCloseCallback(CCObject* pSender)
{
    // "close" menu item clicked
    CCDirector::sharedDirector()->end();
}

