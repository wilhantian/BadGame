#ifndef _COIN_H_
#define _COIN_H_

#include "LifeObject.h"

class Coin : public LifeObject
{
public:
	//½ð±ÒÊý
	CC_SYNTHESIZE(int, coin, Coin);	

	virtual bool init(float x, float y, float width, float height) override;
	CREATE_FUNC_4(Coin, float, float, float, float);

	virtual void dead() override;
	virtual void ended() override;

	virtual void PreSolve(GameObject* other, b2Contact* contact, const b2Manifold* oldManifold);

};
#endif