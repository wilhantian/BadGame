#include "Brick.h"
#include "StaticData.h"

USING_NS_CC;

void Brick::initBrick()
{
	this->getBody()->SetType(b2_staticBody);
	//物体类型
	this->setType(TYPE_BRICK);
	//会和谁发生碰撞
	this->setMask(
		TYPE_HERO |
		TYPE_ANIMAL |
		TYPE_COIN | 
		TYPE_MONSTER |
		TYPE_ARTICLE |
		TYPE_WEAPON);
	//设置纹理-一般不用
	//this->setTexture(SD_STRING("brick_path_texture"));
}

bool Brick::init(float x, float y, float width, float height)
{
	if(!GameObject::init(x, y, width, height))
	{
		return false;
	}
	initBrick();
	return true;
}

bool Brick::init(float x, float y, b2Vec2* points, int count)
{
	if(!GameObject::init(x, y, points, count))
	{
		return false;
	}
	initBrick();
	return true;
}

void Brick::PreSolve(GameObject* other, b2Contact* contact, const b2Manifold* oldManifold)
{
	if(other->getType() == TYPE_HERO || other->getType() == TYPE_MONSTER)
	{
		//如果在砖块下方，那么穿透，也就是实现了地板的单向碰撞
		float otherHeight = other->getBodyBoundingBoxHeight();
		float otherY = other->getPositionY() - otherHeight/2.0f;
		float y = this->getPositionY() + height/2.0f;
		if(otherY < y)
			contact->SetEnabled(false);
	}
}
