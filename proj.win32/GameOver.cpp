#include "GameOver.h"
#include "resource.h"
#include "SimpleAudioEngine.h"
#include "GameLayer.h"

CCScene* GameOver::scene()
{
	CCScene *scene = CCScene::create();
	GameOver *gameOver = GameOver::create();
	scene->addChild(gameOver);

	return  scene;
}

bool GameOver::init()
{
	CCLog("GameOver Init...");
	if (!CCLayer::init()) {
		return false;
	}

	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	//±³¾°
	CCSprite *background = CCSprite::create(s_bg);
	background->setPosition(ccp(winSize.width / 2, winSize.height / 2));
	addChild(background, 0);

	//ÖØÍæ²Ëµ¥
	CCSprite *playAgainNormal = CCSprite::create(s_menu, CCRectMake(378, 0, 126, 33));
	CCSprite *playAgainSelected = CCSprite::create(s_menu, CCRectMake(378, 33, 126, 33));
	CCSprite *playAgainDisabled = CCSprite::create(s_menu, CCRectMake(378, 33*2, 126, 33));
	CCMenuItemSprite *playAgain = CCMenuItemSprite::create(playAgainNormal, playAgainSelected, playAgainDisabled, this,
		menu_selector(GameOver::playAgain));
	CCMenu *menu = CCMenu::create(playAgain, NULL);
	addChild(menu, 2);
	menu->setPosition(winSize.width / 2, 220);

	return true;

}

void GameOver::playAgain(CCObject* pSender)
{
	CCScene *scene = CCScene::create();
	scene->addChild(GameLayer::create());
	CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(1.2, scene));
}
