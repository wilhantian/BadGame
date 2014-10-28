#include "GameObject.h"

USING_NS_CC;

bool GameObject::init(float x, float y, float width, float height)
{
	if(!PhysicsSprite::init(x, y, width, height))
		return false;

	return true;
}

bool GameObject::init(float x, float y, b2Vec2* points, int count)
{
	if(!PhysicsSprite::init(x, y, points, count))
		return false;

	return true;
}

void GameObject::BeginContact(GameObject* other, b2Contact* contact)
{
}

void GameObject::EndContact(GameObject* other, b2Contact* contact)
{
}

void GameObject::PreSolve(GameObject* other, b2Contact* contact, const b2Manifold* oldManifold)
{
}

void GameObject::PostSolve(GameObject* other, b2Contact* contact, const b2ContactImpulse* impulse)
{
}
