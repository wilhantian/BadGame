#ifndef _DEAD_ROOF_H_
#define _DEAD_ROOF_H_

#include "GameObject.h"

/*·æ´Ì*/
class DeadRoof : public GameObject
{
private:
public:
	virtual bool init(float x, float y, float width, float height);
	CREATE_FUNC_4(DeadRoof, float, float, float, float);

	virtual void PreSolve(GameObject* other, b2Contact* contact, const b2Manifold* oldManifold);
};
#endif