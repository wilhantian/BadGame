#ifndef _MONSTER_H_
#define _MONSTER_H_
/*
·ÏÆúÀà
*/
#include "Hero.h"

class Monster : public Hero
{
private:
	int countGun;
public:
	virtual void initParam();

	virtual bool init(float x, float y, float width, float height) override;
	CREATE_FUNC_4(Monster, float, float, float, float);

	virtual bool init(float x, float y, b2Vec2* points, int count) override;
	CREATE_FUNC_4(Monster, float, float, b2Vec2*, int);

	virtual void fire();

	virtual void update(float ft) override;

	virtual void ended() override;
};

#endif