#include "StartMenu.h"
#include "GameLayer.h"
#include "Options.h"

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
		
		CCSprite *background = CCSprite::create(s_bg);
		background->setPosition(ccp(winSize.width / 2, winSize.height / 2));
		addChild(background, 0);

		CCSprite* newGameNormal = CCSprite::create(s_play);
		CCSprite* newGameSelected = CCSprite::create(s_play);
		CCSprite* newGameDisabled = CCSprite::create(s_play);

		CCSprite* gameSettingNormal = CCSprite::create(s_option);
		CCSprite* gameSettingNSelected = CCSprite::create(s_option);
		CCSprite* gameSettingDesabled = CCSprite::create(s_option);

		CCSprite* exitNormal = CCSprite::create(s_exit);
		CCSprite* exitSelected = CCSprite::create(s_exit);
		CCSprite* exitDesabled = CCSprite::create(s_exit);

		CCMenuItemSprite* newGame = CCMenuItemSprite::create(newGameNormal, newGameSelected, newGameDisabled, this, menu_selector(StartMenu::menuCallback));
		CCMenuItemSprite* gameSetting = CCMenuItemSprite::create(gameSettingNormal, gameSettingNSelected, gameSettingDesabled, this, menu_selector(StartMenu::menuCallback));
		CCMenuItemSprite* exit = CCMenuItemSprite::create(exitNormal, exitSelected, exitDesabled, this, menu_selector(StartMenu::menuCallback));

		newGame->setTag(0);
		gameSetting->setTag(1);
		exit->setTag(2);

		CCMenu* menu = CCMenu::create(newGame, gameSetting, exit, NULL);
		menu->alignItemsVerticallyWithPadding(20);
		this->addChild(menu);
		menu->setPosition(ccp(winSize.width / 2, winSize.height / 2));
		//this->schedule(schedule_selector(StartMenu::update), 0.1);


		bRet = true;
    } while (0);

    return bRet;
}

void StartMenu::menuCallback(CCObject* pSender)
{
	int tag = dynamic_cast<CCNode*>(pSender)->getTag();
	if(tag == 0){
		CCScene *scene = CCScene::create();
		scene->addChild(GameLayer::create());
		CCDirector::sharedDirector()->replaceScene(CCTransitionMoveInR::transitionWithDuration(1.2,scene));
	}
	else if (tag == 1) {
		CCScene *scene = Options::scene();
		CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(1.2, scene));

	}
	else if(tag == 2)
	{
		CCDirector::sharedDirector()->end();
		//CCScene *scene = About::scene();
		//CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(1.2, scene));
	}

}

void StartMenu::menuCloseCallback(CCObject* pSender)
{
    // "close" menu item clicked
    CCDirector::sharedDirector()->end();
}

