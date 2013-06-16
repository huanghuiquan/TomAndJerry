#include "Jerry.h"
#include "Resource.h"
#include "Effect.h"
#include "SimpleAudioEngine.h"


using namespace cocos2d;

Jerry::Jerry():m_size(32,32),m_speed(10),m_zOder(10)
{

}

Jerry::~Jerry()
{
}

bool Jerry::init()
{
	// super init first
	if ( !CCSprite::init() )
	{
		return false;
	}


	// init life
	CCTexture2D * JerryTextureCache = CCTextureCache::sharedTextureCache()->addImage(s_jerry);
	CCRect rec = CCRectMake(0, 0, m_size.width, m_size.height);
	this->initWithTexture(JerryTextureCache,  rec);
	JerryTextureCache->release();

	return true;
}


CCRect Jerry::collideRect()
{
	CCPoint pos = getPosition();
	CCSize cs = getContentSize();
	return CCRectMake(pos.x - cs.width / 2 , pos.y - cs.height / 2, cs.width, cs.height / 2);
}

int Jerry::getZoder()
{
	return m_zOder;
}