#ifndef __LevelManager_H__
#define __LevelManager_H__

#include <iostream>
#include <string>
#include <vector>
#include "cocos2d.h"
#include "Config.h"
#include "Tom.h"
#include "Jerry.h"
#include "Floor.h"
#include "Prop.h"
#include "Fish.h"
#include "Cheese.h"

USING_NS_CC;
using namespace std;


class LevelManager{
private:
	cocos2d::CCLayer *m_gameLayer;

	CCPoint m_jerryPosition;
	CCPoint m_tomPosition;
	vector<CCPoint> m_floorPositions;
public:
	Jerry *jerry;
	Tom *tom;
	vector<Floor*> floors;

	//道具s
	vector<Prop*> props;
	CCSize winSize;

public:
	LevelManager(cocos2d::CCLayer *gameLayer);
	~LevelManager();

	void addProp(); //增加一个道具

	void loadLevelResource(int level);
};
#endif /* defined(__MoonWarriorsx__LevelManager__) */
