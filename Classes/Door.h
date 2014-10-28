#ifndef _DOOR_H_
#define _DOOR_H_

#include "GameObject.h"

class Door : public GameObject
{
public:
	virtual bool init(float x, float y, float width, float height);
	CREATE_FUNC_4(Door, float, float, float, float);

	virtual void BeginContact(GameObject* other, b2Contact* contact);
};

#endif