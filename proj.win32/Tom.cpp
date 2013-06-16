#include "Tom.h"
#include "Resource.h"
#include "Effect.h"
#include "SimpleAudioEngine.h"


using namespace cocos2d;

Tom::Tom():m_size(32,32),m_speed(10),m_zOder(10)
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
	CCTexture2D * TomTextureCache = CCTextureCache::sharedTextureCache()->addImage(s_tom);
	CCRect rec = CCRectMake(0, 0, m_size.width, m_size.height);
	this->initWithTexture(TomTextureCache,  rec);
	TomTextureCache->release();

	return true;
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