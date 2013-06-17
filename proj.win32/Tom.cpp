#include "Tom.h"
#include "Resource.h"
#include "Effect.h"
#include "SimpleAudioEngine.h"


using namespace cocos2d;

Tom::Tom():m_size(100,100),m_speed(32),m_zOder(10),isWalking(false)
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
	
	actions = CCAction::create();

	// init life
	CCTexture2D * TomTextureCache = CCTextureCache::sharedTextureCache()->addImage(s_tomRight2);
	CCRect rec = CCRectMake(0, 0, m_size.width, m_size.height);
	this->initWithTexture(TomTextureCache,  rec);
	TomTextureCache->release();

	this->scheduleUpdate();
	return true;
}

void Tom::move(Direction dir){
	if(!isWalking){
		CCPoint nextPos = this->getPosition();
		if(dir == UP){
			nextPos.y = nextPos.y + m_speed;
		}
		else if (dir == DOWN)
		{
			nextPos.y = nextPos.y - m_speed;
		}
		else if(dir == LEFT){
			nextPos.x =nextPos.x - m_speed;
		}
		else if(dir == RIGHT){
			nextPos.x = nextPos.x + m_speed;
		}

		CCActionInterval *actionTo = CCMoveTo::actionWithDuration(0.50f, nextPos); 	
		actions = CCSequence::actions(actionTo,  
			CCCallFunc::actionWithTarget(this, callfunc_selector(Tom::setWalkStop)),NULL);  
		this->runAction(actions);
		CCLOG("runAction");
		//bool done = actions->isDone();
		isWalking = true;
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

void Tom::setWalkStop(){
	isWalking = false;
}

void Tom::update(float dt){
	//CCLOG("No walk");
}