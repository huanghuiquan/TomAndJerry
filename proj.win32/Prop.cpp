#include "Prop.h"
#include "Effect.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;

Prop::Prop(int speedBonus, float m_duration):m_size(64,64),//m_speed must < 64
	winSize(CCDirector::sharedDirector()->getWinSize())
{
}

Prop::~Prop()
{
}

bool Prop::init()
{
	if ( !CCSprite::init() ){
		return false;
	}
	//this->setContentSize(CCSize(64,64));
// 	propTextureCache = CCTextureCache::sharedTextureCache()->addImage(s_fish);
// 	CCRect rec = CCRectMake(0, 0, m_size.width, m_size.height);
// 	this->initWithTexture(propTextureCache,  rec);
	return true;
}

CCRect Prop::collideRect()
{
	CCPoint pos = getPosition();
	CCSize cs = getContentSize();
	return CCRectMake(pos.x - cs.width / 2, pos.y - cs.height / 2 , cs.height, cs.width);
}

int Prop::getSpeedBonus(){
	return speedBonus;
}


float Prop::getDuration()
{
	return m_duration;
}

