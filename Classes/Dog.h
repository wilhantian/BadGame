#ifndef _DOG_H_
#define _DOG_H_

#include "cocos2d.h"
#include "GameObject.h"
//class GameObject;

class Dog : public GameObject
{
public:
	int count;
	virtual bool init();

	CREATE_FUNC(Dog);

	virtual void interactive(GameObject* other);
};

#endif