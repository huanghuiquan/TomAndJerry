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
		CCSize s = CCDirector::sharedDirector()->getWinSize();//�����Ļ��С�����ֵ�s��  

		CCSprite *yg1 = CCSprite::spriteWithFile(s_ygBG);//����ҡ�˱���ͼ  
		yg1->setOpacity(190);                        //����͸����  
		yg1->setAnchorPoint(ccp(0,0));               //����ê��λ��  
		yg1->setPosition(ccp(0,0));                  //������ʾλ��  
		radius = yg1->getContentSize().width/2;      //�����뾶  
		centre = ccp(radius,radius);                 //���㱳������  
		this->addChild(yg1,1);                       //��ӵ�������  

		yg2 = CCSprite::spriteWithFile(s_yg);//����ҡ��СȦ  
		yg2->setPosition(ccp(centre.x, centre.y));  
		this->addChild(yg2,2);  

		this->setTouchEnabled(true);               //��������,�����Ļ������Ļ��û�õ�  
		//this->schedule(schedule_selector(HelloWorld::moveing));//������Ϊ�����߼���,������߼��Ǵ�������ƶ� 

		this->scheduleUpdate(); //update
		bRet = true;  
	} while (0);  

	return bRet;  
}  

//������ʼ..Ҳ���ǵ����Ļ
void ControlLayer::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent)
{
	CCTouch *touch = (CCTouch*)pTouches->anyObject();
	CCPoint location = touch->locationInView();
	CCPoint convertedLocation = CCDirector::sharedDirector()->convertToGL(location);

	CCRect rect=yg2->boundingBox();
	if (CCRect::CCRectContainsPoint(rect,convertedLocation))//�жϴ����ķ�Χ���������ҡ���ڵĻ�������Ӧ
	{
		//�ж����Ǹ�����
		isMove = true;
	}
}

//�����ƶ��Ĵ���...Ҳ���ǰ��º����ƶ�
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

		float radius1=radius*2/6;//ҡ�˵İ뾶
		float side=radius*2/3;//�Ź�����һ�����ӵı߳�

		CCPoint yg2Position = yg2->getPosition();
		//����ʹ�ú��׹�ʽ����������������ж�ʮ�ּ��������ľ�ȷ����
		//����
		if( CCRect::CCRectContainsPoint(CCRectMake(centre.x-radius1,centre.y+radius1,side,side), yg2Position) )  
		{
			curDir = UP;
		}
		//����
		else if( CCRect::CCRectContainsPoint(CCRectMake(centre.x-radius1, centre.y-radius1-side,side,side), yg2Position) )
		{
			curDir = DOWN;
		}
		//����
		else if(CCRect::CCRectContainsPoint(CCRectMake(centre.x-radius1-side, centre.y-radius1,side,side), yg2Position))
		{
			curDir = LEFT;
		}
		//����
		else if (CCRect::CCRectContainsPoint(CCRectMake(centre.x+radius1, centre.y-radius1,side,side), yg2Position))  
		{  
			curDir = RIGHT;
		}
		else if(CCRect::CCRectContainsPoint(CCRectMake(centre.x-radius1, centre.y-radius1,side,side), yg2Position)){
			curDir = NONE;
		}
	}
}

//��������..Ҳ�����ɿ���Ĵ���
void ControlLayer::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent)
{
	isMove=false;			 //�ر��ƶ��߼�
	yg2->setPosition(centre);//��ҡ��СȦ��ʼ��Ϊ����
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