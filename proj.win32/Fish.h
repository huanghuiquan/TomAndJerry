#pragma once
#include "prop.h"
#include "cocos2d.h"

class Fish : public Prop
{
public:
	Fish(void);
	~Fish(void);
public:
	bool init();
	CREATE_FUNC(Fish);
};

