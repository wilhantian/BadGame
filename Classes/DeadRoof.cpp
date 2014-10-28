#include "DeadRoof.h"
#include "Hero.h"

USING_NS_CC;

bool DeadRoof::init(float x, float y, float width, float height)
{
	if (!GameObject::init(x, y, width, height))
	{
		return false;
	}

	this->getBody()->SetType(b2_staticBody);
	this->setType(TYPE_BRICK);
	this->setMask(TYPE_HERO);
	return true;
}

void DeadRoof::PreSolve(GameObject* other, b2Contact* contact, const b2Manifold* oldManifold)
{
	contact->SetEnabled(false);
	if (other->getType() == TYPE_HERO)
	{
		Hero* hero = (Hero*)other;
		hero->dead();
		log("ddddddddddddddd");
	}
}
