#include "Monster.h"
#include "Weapon.h"
/*
废弃类
*/
USING_NS_CC;

void Monster::initParam()
{
	countGun = 0;
	jumpCount = 0;
	speed = 1;
	spring = 5;
	moveState = MOVE_STOP;
	//设置朝向
	this->setDir(DIR_RIGHT);
	//物体的类型
	this->setType(TYPE_MONSTER);
	//会和哪些物体方式碰撞
	this->setMask(
		TYPE_BRICK		| 
		TYPE_COIN		| 
		TYPE_HERO		| 
		TYPE_PRIZE		| 
		TYPE_ARTICLE	|
		TYPE_WEAPON);
	//触动停止动画
	moveStop();
}

bool Monster::init(float x, float y, float width, float height)
{
	if(!Hero::init(x, y, width, height))
	{
		return false;
	}
	initParam();
	return true;
}

bool Monster::init(float x, float y, b2Vec2* points, int count)
{
	if(!Hero::init(x, y, points, count))
	{
		return false;
	}
	initParam();
	return true;
}

void Monster::fire()
{
	if(isDie() || isOver())
		return;
	Weapon* w = Weapon::create(this);
	GameManager::getInstance()->monsterLayer->addChild(w, 50);
}

void Monster::update(float ft)
{
	Hero::update(ft);
	Hero* hero = GameManager::getInstance()->hero;
	
	if(countGun >= 60*4)
	{
		countGun = 0;
		fire();
	}
	countGun++;

	if (this->getPositionX() < hero->getPositionX())
	{
		this->moveRight();
	}
	else
	{
		this->moveLeft();
	}
}

void Monster::ended()
{
	Hero::ended();
	this->autoRemovePhysicsSprite();
}