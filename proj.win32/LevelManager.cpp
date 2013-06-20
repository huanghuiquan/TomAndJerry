#include "LevelManager.h"
#include "GameLayer.h"
#include "resource.h"
#include <fstream>
#include <string>
#include <sstream>

using namespace std;
using namespace cocos2d;

LevelManager::LevelManager(CCLayer *gameLayer)
{
	CCAssert(gameLayer != NULL, "game layer must be non-null");
	m_gameLayer = gameLayer;
	winSize = CCDirector::sharedDirector()->getWinSize();
	props.push_back(NULL); //index 0 for fish
	props.push_back(NULL); //index 1 for cheese
}

LevelManager::~LevelManager()
{
}

void LevelManager::loadLevelResource(int level)
{
	//load position
	char tmp[256];
	char c;
	int dataX, dataY;
	stringstream ss;
	ifstream fin(s_level1);//读取文件“2.txt”注意，文件须放在工作空间下。读取后产生 流型 文件fin
	//load Floors
	fin.getline(tmp, 256, '\n');
	CCAssert(strcmp(tmp, "floor:") == 0, "Level Data Format Wrong!");
	fin.getline(tmp, 256, '\n');
	while (strcmp(tmp, "")){
		ss.clear();  //记得clear， fuck！
		ss << tmp;
		ss >> dataX;
		ss >> c;
		ss >> dataY;
		m_floorPositions.push_back(ccp(dataX*64 + 32, winSize.height-dataY*64-32));
		i_map[rows - dataY][cols -dataX] = 3;  //用3表示墙
		fin.getline(tmp, 256, '\n');
	}

	//load Tom
	fin.getline(tmp, 256, '\n');
	CCAssert(strcmp(tmp, "tom:") == 0, "Level Data Format Wrong!");
	fin.getline(tmp, 256, '\n');
	ss.clear();  //记得clear， fuck！
	ss << tmp;
	ss >> dataX;
	ss >> c;
	ss >> dataY;
	m_tomPosition = ccp(dataX*64 + 32, winSize.height -dataY*64-32);
	i_map[rows - dataY][cols -dataX] = 9;  //用9表示Tom
	fin.getline(tmp, 256, '\n');

	//load jerry
	fin.getline(tmp, 256, '\n');
	CCAssert(strcmp(tmp, "jerry:") == 0, "Level Data Format Wrong!");
	fin.getline(tmp, 256, '\n');
	ss.clear();  //记得clear， fuck！
	ss << tmp;
	ss >> dataX;
	ss >> c;
	ss >> dataY;
	i_map[rows - dataY][cols -dataX] = 7;  //用7表示jerry
	m_jerryPosition = ccp(dataX * 64 + 32, winSize.height-dataY*64-32);
	fin.getline(tmp, 256, '\n');

	fin.close();

	//load tom
	Tom * tm = Tom::create();
	tm->setPosition(m_tomPosition);
	tom = tm;
	m_gameLayer->addChild(tm,2);

	//load Jerry
	Jerry *jy = Jerry::create();
	jy->setPosition(m_jerryPosition);
 	jerry = jy;
	m_gameLayer->addChild(jy,2);

	// load floor
	for (int i = 0; i < m_floorPositions.size(); i++){
		Floor* f = Floor::create();
		f->setPosition(m_floorPositions.at(i));
		m_gameLayer->addChild(f,1);
		floors.push_back(f);
	}
}

void LevelManager::addProp(){
	int x, y; //产生一个空位置
	x = ((int)(CCRANDOM_0_1()*1024 / 64));
	y = ((int)(CCRANDOM_0_1()*768 / 64));
	CCPoint pos;
	while(1){
		if(i_map[y][x] == 0){
			pos = ccp(x*64 + 32, y*64+32);
			break;
		}
		x = ((int)(CCRANDOM_0_1()*1024 / 64));
		y = ((int)(CCRANDOM_0_1()*768 / 64));
	}
	i_map[y][x] = 5; //将该位置设置为5，表示道具

	int amountProp = props.size();
	//随机产生一个种类
	int idx = ((int)(CCRANDOM_0_1() * amountProp));


	if(props.at(idx)){ //如果该道具已经存在，则删除
		CCPoint pos2 ;
		pos2 = props.at(idx)->getPosition();
		m_gameLayer->removeChild(props.at(idx),true);
		i_map[(int)(pos2.y / 64)][(int)(pos2.x / 64)] = 0;
		props.at(idx) = NULL;
	}
	if (idx == 0)
	{
		props.at(idx) = (Fish*)Fish::create();
		props.at(idx)->setPosition(pos); 
		m_gameLayer->addChild(props.at(idx));
		i_map[(int)(pos.y / 64)][(int)(pos.x / 64)] = 5;
	}
	if (idx == 1)
	{
		props.at(idx) = (Cheese*)Cheese::create();
		props.at(idx)->setPosition(pos); 
		m_gameLayer->addChild(props.at(idx));
		i_map[(int)(pos.y / 64)][(int)(pos.x / 64)] = 5;
	}
}