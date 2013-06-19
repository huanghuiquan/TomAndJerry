#include "Jerry.h"
#include "Effect.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;

Jerry::Jerry():m_size(64,64),m_speed(15),isWalking(false),curDir(DOWN),m_step(0)
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
	jerryTextureCache = CCTextureCache::sharedTextureCache()->addImage(s_jerryRight[2]);
	CCRect rec = CCRectMake(0, 0, m_size.width, m_size.height);
	this->initWithTexture(jerryTextureCache,  rec);

	return true;
}

CCRect Jerry::collideRect()
{
	CCPoint pos = getPosition();
	CCSize cs = getContentSize();
	return CCRectMake(pos.x - cs.width / 2 + 1 , pos.y - cs.height / 2 + 1, 63, 63);
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

void Jerry::changePicture(Direction dir, int step)
{
	//CCTexture2D * TomTextureCache;
	switch(dir)
	{
	case UP:
		jerryTextureCache = CCTextureCache::sharedTextureCache()->addImage(s_jerryUp[step]);
		break;
	case DOWN:
		jerryTextureCache = CCTextureCache::sharedTextureCache()->addImage(s_jerryDown[step]);
		break;
	case LEFT:
		jerryTextureCache = CCTextureCache::sharedTextureCache()->addImage(s_jerryLeft[step]);
		break;
	case RIGHT:
		jerryTextureCache = CCTextureCache::sharedTextureCache()->addImage(s_jerryRight[step]);
		break;
	case NONE:
		return;
	}
	this->setTexture(jerryTextureCache);
	//TomTextureCache->release();
}

