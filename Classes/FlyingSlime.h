#ifndef _FLYING_SLIME_H_
#define _FLYING_SLIME_H_

#include "Aware.h"

class FlyingSlime : public Aware
{
protected:
	CC_SYNTHESIZE(float, speed, Speed);
public:
	virtual bool init(float x, float y, float width, float height) override;
	CREATE_FUNC_4(FlyingSlime, float, float, float, float);

	virtual void update(float ft);

	virtual void dead();

	virtual void ended();
/*
	virtual void BeginContact(GameObject* other, b2Contact* contact);
*/
	/*test EX*/
	virtual void PreSolve(GameObject* other, b2Contact* contact, const b2Manifold* oldManifold);
	/*向左移动*/
	virtual void moveLeft();
	/*向右移动*/
	virtual void moveRight();

};

#endif
