#include "Effect.h"
#include "resource.h"
#include <string>
USING_NS_CC;
using namespace std;

Effect::Effect()
{
}

Effect::~Effect()
{
}

Effect* Effect::create()
{
    Effect* effect = new Effect();
    if (effect) {
        effect->autorelease();
        return effect;
    }
	else{
        delete effect;
        effect = NULL;
        return NULL;
    }
}

