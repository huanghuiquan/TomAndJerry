#include "Jerry.h"
#include "Effect.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;

Jerry::Jerry():m_size(64,64),m_speed(30),isWalking(false),curDir(DOWN)
{
	winSize = CCDirector::sharedDirector()->getWinSize();
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

/************************************************************************/
/* 给一个方向，沿着这个方向移动一个speed */
/************************************************************************/
void Jerry::move(Direction dir){
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

		//边界检测
		if(nextPos.x > winSize.width - this->getContentSize().width / 2){
			nextPos.x = winSize.width  - this->getContentSize().width /2;
		}
		else if(nextPos.x < this->getContentSize().width/2){
			nextPos.x = this->getContentSize().width/2;
		}
		else if(nextPos.y > winSize.height - this->getContentSize().height/2){
			nextPos.y = winSize.height - this->getContentSize().height/2;
		}
		else if(nextPos.y < this->getContentSize().height/2){
			nextPos.y = this->getContentSize().height/2;
		}

		CCActionInterval *actionTo = CCMoveTo::actionWithDuration(0.050f, nextPos); 	
		actions = CCSequence::actions(actionTo,  
			CCCallFunc::actionWithTarget(this, callfunc_selector(Jerry::setWalkStop)),NULL);  
		this->runAction(actions);
		isWalking = true;
	}
}

void Jerry::setWalkStop(){
	isWalking = false;
}

int Jerry::getSpeed()
{
	return m_speed;
}

Direction Jerry::getDirection()
{
	return curDir;
}

void Jerry::setDirection(Direction dir){
	curDir = dir;
}


