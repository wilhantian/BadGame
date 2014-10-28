#include "LifeObject.h"

USING_NS_CC;

bool LifeObject::init(float x, float y, float width, float height)
{
	if(!GameObject::init(x, y, width, height))
		return false;
	hp = 1;
	atk = 0;
	die = false;
	over = false;

	//开启逐帧回调
	scheduleUpdate();
	return true;
}

bool LifeObject::init(float x, float y, b2Vec2* points, int count)
{
	if(!GameObject::init(x, y, points, count))
		return false;
	hp = 1;
	atk = 0;
	die = false;
	over = false;
	
	//开启逐帧回调
	scheduleUpdate();
	return true;
}

void LifeObject::setDie(bool die)
{
	this->die = die;
}

bool LifeObject::isDie() const
{
	return die;
}

void LifeObject::setOver(bool over)
{
	this->over = over;
}

bool LifeObject::isOver() const
{
	return over;
}

void LifeObject::update(float ft)
{
	if(hp <= 0 && !die)
	{//血量低于0 且未死亡时 
		dead();
	}
}

void LifeObject::dead()
{
	die = true;
	//重新设置碰撞
	//this->setMask(0x000000);
	//死亡动画 死亡动画结束后调用ended()
}

void LifeObject::ended()
{
	//设置结束标识
	over = true;
	//删除所有 默认不删除
	//this->autoRemovePhysicsSprite();
}