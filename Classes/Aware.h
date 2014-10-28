#ifndef _AWARE_H_
#define _AWARE_H_

#include "LifeObject.h"

/*有智慧的生命体 可以自主移动等*/
class Aware : public LifeObject
{
protected:
public:
	//英雄所朝方向
	CC_SYNTHESIZE(DIR, dir, Dir);
};
#endif