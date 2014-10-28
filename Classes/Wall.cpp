#include "Wall.h"
#include "StaticData.h"

USING_NS_CC;

void Wall::initParam()
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
	//this->setTexture(SD_STRING("wall_path_texture"));
}

bool Wall::init(float x, float y, float width, float height)
{
	if (!GameObject::init(x, y, width, height))
	{
		return false;
	}
	initParam();
	return true;
}

bool Wall::init(float x, float y, b2Vec2* points, int count)
{
	if (!GameObject::init(x, y, points, count))
	{
		return false;
	}
	initParam();
	return true;
}

