#include "Tom.h"
#include "Resource.h"
#include "Effect.h"
#include "SimpleAudioEngine.h"


using namespace cocos2d;

Tom::Tom():m_size(100,100),m_speed(10),m_zOder(10)
{

}

Tom::~Tom()
{
}

bool Tom::init()
{
	// super init first
	if ( !CCSprite::init() )
	{
		return false;
	}
	

	// init life
	CCTexture2D * TomTextureCache = CCTextureCache::sharedTextureCache()->addImage(s_tomRight2);
	CCRect rec = CCRectMake(0, 0, m_size.width, m_size.height);
	this->initWithTexture(TomTextureCache,  rec);
	TomTextureCache->release();

	return true;
}

void Tom::moveTo(CCPoint pos){
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	CCActionInterval *actionTo = CCMoveTo::actionWithDuration(2.0f,   
		CCPointMake(winSize.width * 3 / 4, winSize.height / 2));  
	CCActionInterval *actionBy = CCMoveBy::actionWithDuration(2.0f,  
		CCPointMake(-winSize.width / 2, 0));  
	CCActionInterval *actionByCopy = (CCActionInterval *) actionBy->copy();  
	CCActionInterval *actionBack = actionBy->reverse();  

	this->runAction(CCSequence::actions(actionTo, actionByCopy, NULL));  
	this->runAction(CCSequence::actions(actionBy, actionBack, NULL));  
}
}


CCRect Tom::collideRect()
{
	CCPoint pos = getPosition();
	CCSize cs = getContentSize();
	return CCRectMake(pos.x - cs.width / 2 , pos.y - cs.height / 2, cs.width, cs.height / 2);
}

int Tom::getZoder()
{
	return m_zOder;
}