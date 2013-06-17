#include "ControlLayer.h"
#include "resource.h"

float heronsformula(float x1,float y1,float x2,float y2,float x3,float y3)
{
	float a=sqrt(pow(x1-x2,2)+pow(y1-y2,2));
	float b=sqrt(pow(x2-x3,2)+pow(y2-y3,2));
	float c=sqrt(pow(x3-x1,2)+pow(y3-y1,2));
	float s=(a+b+c)/2;

	return sqrt(s*(s-a)*(s-b)*(s-c));
}

bool triangleContainPoint(float x1,float y1,float x2,float y2,float x3,float y3,float px,float py)
{
	float s1=heronsformula(x1,y1,x2,y2,px,py);
	float s2=heronsformula(x2,y2,x3,y3,px,py);
	float s3=heronsformula(x3,y3,x1,y1,px,py);
	float s=heronsformula(x1,y1,x2,y2,x3,y3);

	return abs(s-(s1+s2+s3))<0.001f;
}

bool ControlLayer::init()  
{  
	curDir = NONE;
	bool bRet = false;  
	do   
	{  
		CC_BREAK_IF(! CCLayer::init());  
		CCSize s = CCDirector::sharedDirector()->getWinSize();//获得屏幕大小，保持到s中  

		CCSprite *yg1 = CCSprite::spriteWithFile(s_ygBG);//加载摇杆背景图  
		yg1->setOpacity(190);                        //设置透明度  
		yg1->setAnchorPoint(ccp(0,0));               //设置锚点位置  
		yg1->setPosition(ccp(0,0));                  //设置显示位置  
		radius = yg1->getContentSize().width/2;      //背景半径  
		centre = ccp(radius,radius);                 //计算背景中心  
		this->addChild(yg1,1);                       //添加到场景中  

		yg2 = CCSprite::spriteWithFile(s_yg);//加载摇杆小圈  
		yg2->setPosition(ccp(centre.x, centre.y));  
		this->addChild(yg2,2);  

		this->setTouchEnabled(true);               //开启触摸,不开的话点击屏幕是没用的  
		//this->schedule(schedule_selector(HelloWorld::moveing));//这句理解为开启逻辑吧,这里的逻辑是处理精灵的移动 

		this->scheduleUpdate(); //update
		bRet = true;  
	} while (0);  

	return bRet;  
}  

//触摸开始..也就是点击屏幕
void ControlLayer::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent)
{
	CCTouch *touch = (CCTouch*)pTouches->anyObject();
	CCPoint location = touch->locationInView();
	CCPoint convertedLocation = CCDirector::sharedDirector()->convertToGL(location);

	CCRect rect=yg2->boundingBox();
	if (CCRect::CCRectContainsPoint(rect,convertedLocation))//判断触摸的范围。如果是在摇杆内的话，才响应
	{
		//判断在那个方向；
		isMove = true;
	}
}

//触摸移动的处理...也就是按下后再移动
void ControlLayer::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent)
{
	CCTouch *touch = (CCTouch*)pTouches->anyObject();
	CCPoint location = touch->locationInView();
	CCPoint convertedLocation = CCDirector::sharedDirector()->convertToGL(location);

	bool inRange=pow(centre.x-convertedLocation.x,2)+pow(centre.y-convertedLocation.y,2)<pow(radius,2);
	Direction dir;
	if(isMove&&inRange)
	{
		yg2->setPosition(convertedLocation);

		float radius1=radius*2/6;//摇杆的半径
		float side=radius*2/3;//九宫格中一个格子的边长

		CCPoint yg2Position = yg2->getPosition();
		//我们使用海伦公式来计算面积，进而判断十字键中心区的精确方向
		//向上
		if( CCRect::CCRectContainsPoint(CCRectMake(centre.x-radius1,centre.y+radius1,side,side), yg2Position) )  
		{
			curDir = UP;
		}
		//向下
		else if( CCRect::CCRectContainsPoint(CCRectMake(centre.x-radius1, centre.y-radius1-side,side,side), yg2Position) )
		{
			curDir = DOWN;
		}
		//向左
		else if(CCRect::CCRectContainsPoint(CCRectMake(centre.x-radius1-side, centre.y-radius1,side,side), yg2Position))
		{
			curDir = LEFT;
		}
		//向右
		else if (CCRect::CCRectContainsPoint(CCRectMake(centre.x+radius1, centre.y-radius1,side,side), yg2Position))  
		{  
			curDir = RIGHT;
		}
		else if(CCRect::CCRectContainsPoint(CCRectMake(centre.x-radius1, centre.y-radius1,side,side), yg2Position)){
			curDir = NONE;
		}
	}
}

//触摸结束..也就是松开后的处理
void ControlLayer::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent)
{
	isMove=false;			 //关闭移动逻辑
	yg2->setPosition(centre);//把摇杆小圈初始化为中心
	curDir = NONE;
}

void ControlLayer::setControledSprite(CCSprite* pSprite){
	tom = (Tom*)pSprite;
}

void ControlLayer::update(float dt){
// 	if(curDir != NONE){
// 		tom->move(curDir);
// 		//CCLOG("curDir = %d", curDir);
// 	}
}

Direction ControlLayer::getYgDirection(){
	return curDir;
}