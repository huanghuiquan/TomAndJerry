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
	fin.getline(tmp, 256, '\n');
	CCAssert(strcmp(tmp, "floor:") == 0, "Level Data Format Wrong!");
	fin.getline(tmp, 256, '\n');
	while (strcmp(tmp, "")){
		ss.clear();  //记得clear， fuck！
		ss << tmp;
		ss >> dataX;
		ss >> c;
		ss >> dataY;
		m_floorPositions.push_back(ccp(dataX*32 + 16, winSize.height-dataY*32-16));
		fin.getline(tmp, 256, '\n');
	}

	fin.getline(tmp, 256, '\n');
	CCAssert(strcmp(tmp, "tom:") == 0, "Level Data Format Wrong!");
	fin.getline(tmp, 256, '\n');
	ss.clear();  //记得clear， fuck！
	ss << tmp;
	ss >> dataX;
	ss >> c;
	ss >> dataY;
	m_tomPosition = ccp(dataX*32 + 16, winSize.height -dataY*32-16);
	fin.getline(tmp, 256, '\n');

	fin.getline(tmp, 256, '\n');
	CCAssert(strcmp(tmp, "jerry:") == 0, "Level Data Format Wrong!");
	fin.getline(tmp, 256, '\n');
	ss.clear();  //记得clear， fuck！
	ss << tmp;
	ss >> dataX;
	ss >> c;
	ss >> dataY;
	m_jerryPosition = ccp(dataX*32 + 16, winSize.height-dataY*32-16);
	fin.getline(tmp, 256, '\n');

	fin.close();

	//load tom
	Tom * tm = Tom::create();
	tm->setPosition(m_tomPosition);
	tom = tm;
	m_gameLayer->addChild(tm);

	//load Jerry
	Jerry *jy = Jerry::create();
	jy->setPosition(m_jerryPosition);
 	jerry = jy;
	m_gameLayer->addChild(jy);

	// load floor
	for (int i = 0; i < m_floorPositions.size(); i++){
		Floor* f = Floor::create();
		f->setPosition(m_floorPositions.at(i));
		m_gameLayer->addChild(f);
	}

}

