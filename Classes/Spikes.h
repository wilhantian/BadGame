#ifndef _SPIKES_H_
#define _SPIKES_H_

#include "GameObject.h"

/*·æ´Ì*/
class Spikes : public GameObject
{
private:
	int atk;
public:
	virtual bool init(float x, float y, float width, float height);
	CREATE_FUNC_4(Spikes, float, float, float, float);

	virtual void PreSolve(GameObject* other, b2Contact* contact, const b2Manifold* oldManifold);
};
#endif