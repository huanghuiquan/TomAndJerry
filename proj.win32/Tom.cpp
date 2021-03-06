#include "Tom.h"
#include "Effect.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;

Tom::Tom():m_size(100,100),m_speed(15),m_step(0),//m_speed must < 64
	isWalking(false) 
{
	winSize = CCDirector::sharedDirector()->getWinSize();
	originSpeed = m_speed;
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

	//this->setContentSize(CCSize(64,64));
	TomTextureCache = CCTextureCache::sharedTextureCache()->addImage(s_tomRight[2]);
	CCRect rec = CCRectMake(0, 0, m_size.width, m_size.height);
	this->initWithTexture(TomTextureCache,  rec);

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


		//�߽���
		if(nextPos.x > winSize.width - this->getContentSize().width / 2+18){
			nextPos.x = winSize.width  - this->getContentSize().width /2 +18;
		}
		else if(nextPos.x < this->getContentSize().width/2-18){
			nextPos.x = this->getContentSize().width/2-18;
		}
		else if(nextPos.y > winSize.height - this->getContentSize().height/2+18){
			nextPos.y = winSize.height - this->getContentSize().height/2+18;
		}
		else if(nextPos.y < this->getContentSize().height/2-18){
			nextPos.y = this->getContentSize().height/2-18;
		}

		CCActionInterval *actionTo = CCMoveTo::actionWithDuration(0.05f, nextPos); 	
		actions = CCSequence::actions(actionTo,  
			CCCallFunc::actionWithTarget(this, callfunc_selector(Tom::setWalkStop)),NULL);  
		this->runAction(actions);
		m_step = (m_step + 1) % 4;

		changePicture(dir, m_step);

		isWalking = true;
	}
}

CCRect Tom::collideRect()
{
	CCPoint pos = getPosition();
	CCSize cs = getContentSize();
	return CCRectMake(pos.x - cs.width / 2 + 18, pos.y - cs.height / 2 + 18, 64, 64);
}

void Tom::setWalkStop(){
	isWalking = false;
}

int Tom::getSpeed()
{
	return m_speed;
}

void Tom::update(float dt){
	//CCLOG("No walk");
}

// Add animation of Tom's moving.
void Tom::changePicture(Direction dir, int step)
{
	//CCTexture2D * TomTextureCache;
	switch(dir)
	{
	case UP:
		TomTextureCache = CCTextureCache::sharedTextureCache()->addImage(s_tomUp[step]);
		break;
	case DOWN:
		TomTextureCache = CCTextureCache::sharedTextureCache()->addImage(s_tomDown[step]);
		break;
	case LEFT:
		TomTextureCache = CCTextureCache::sharedTextureCache()->addImage(s_tomLeft[step]);
		break;
	case RIGHT:
		TomTextureCache = CCTextureCache::sharedTextureCache()->addImage(s_tomRight[step]);
		break;
	case NONE:
		return;
	}
	this->setTexture(TomTextureCache);
	//TomTextureCache->release();
}

void Tom::addSpeed( int t )
{
	m_speed += t;;
}

void Tom::resetSpeed()
{
	m_speed = originSpeed;
}

