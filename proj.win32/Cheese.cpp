#include "Cheese.h"


Cheese::Cheese(void):Prop(20,5)  //速度加成20， 10s出现周期
{
}

Cheese::~Cheese(void)
{
}

bool Cheese::init(){
	m_duration = 5;
	speedBonus = 20;
	propTextureCache = CCTextureCache::sharedTextureCache()->addImage(s_cheese);
	CCRect rec = CCRectMake(0, 0, m_size.width, m_size.height);
	this->initWithTexture(propTextureCache,  rec);
	return true;
}
