#pragma once
#include "prop.h"
#include "cocos2d.h"

class Cheese : public Prop
{
public:
	Cheese(void);
	~Cheese(void);
public:
	bool init();
	CREATE_FUNC(Cheese);
};

