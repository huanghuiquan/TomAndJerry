#include "Floor.h"
#include "Resource.h"
#include "Effect.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;

Floor::Floor():m_size(32,32),m_zOder(10)
{

}

Floor::~Floor()
{
}

bool Floor::init()
{
	// super init first
	if ( !CCSprite::init() )
	{
		return false;
	}


	// init life
	CCTexture2D * FloorTextureCache = CCTextureCache::sharedTextureCache()->addImage(s_floor);
	CCRect rec = CCRectMake(0, 0, m_size.width, m_size.height);
	this->initWithTexture(FloorTextureCache,  rec);
	FloorTextureCache->release();

	return true;
}


CCRect Floor::collideRect()
{
	CCPoint pos = getPosition();
	CCSize cs = getContentSize();
	return CCRectMake(pos.x - cs.width / 2 , pos.y - cs.height / 2, cs.width, cs.height / 2);
}

int Floor::getZoder()
{
	return m_zOder;
}