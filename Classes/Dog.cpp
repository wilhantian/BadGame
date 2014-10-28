#include "Dog.h"

USING_NS_CC;

bool Dog::init()
{
	if(!GameObject::init(500, 500, 30, 30))
		return false;

	count = 0;
	
	this->setTexture("fl.png");
	
	return true;
}

void Dog::interactive(GameObject* other)
{
	log("dog%d", count++);
}
