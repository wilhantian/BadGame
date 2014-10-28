#ifndef _GRENADE_H_
#define _GRENADE_H_
/*
	 ÷¡ÒµØ
*/
#include "Aware.h"

class Grenade : public Aware
{
protected:
	float countTime;
	float bombTime;
public:
	virtual bool init(Aware* aware);
	CREATE_FUNC_1(Grenade, Aware*);

	virtual void dead();

	virtual void ended();

	virtual void update(float ft);

};

#endif