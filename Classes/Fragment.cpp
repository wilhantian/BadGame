#include "Fragment.h"
#include "LifeObject.h"
#include "StaticData.h"

USING_NS_CC;

bool Fragment::init(float x, float y, b2Vec2 speed, int size, bool killHero)
{
	if(!GameObject::init(x, y, size, size))
	{
		return false;
	}
	atk = SD_INT("fragment_int_atk");	//伤害
	bombSize = SD_INT("fragment_int_distance");	//作用距离	像素单位
	startPosition = this->getPosition();	//初始坐标
	this->killHero = killHero;

	//应用力
	this->getBody()->SetLinearVelocity(speed);
	this->getBody()->SetSleepingAllowed(true);
	this->getBody()->SetBullet(true);
	
	this->setType(TYPE_WEAPON);
	this->setMask(
		TYPE_ANIMAL|
		TYPE_BRICK|
		TYPE_COIN|
		TYPE_HERO|
		TYPE_PRIZE|
		TYPE_ARTICLE|
		TYPE_MONSTER);

	//开启逐帧回调
	scheduleUpdate();

	return true;
}

void Fragment::BeginContact(GameObject* other, b2Contact* contact)
{
	if(killHero)	//如果可以对英雄伤害
	{
		if(other->getType() == TYPE_ANIMAL
			||other->getType() == TYPE_HERO
			|| other->getType() == TYPE_ARTICLE
			||other->getType() == TYPE_MONSTER)
		{
			LifeObject* liftObject = (LifeObject*)other;
			liftObject->setHp(liftObject->getHp() - atk);
		}
	}
	else
	{
		if(other->getType() == TYPE_ANIMAL
			||other->getType() == TYPE_MONSTER
			||other->getType() == TYPE_ARTICLE)
		{
			LifeObject* liftObject = (LifeObject*)other;
			liftObject->setHp(liftObject->getHp() - atk);
		}
	}
	//碰撞后清除
	this->autoRemovePhysicsSprite();
}

void Fragment::update(float ft)
{
	if (startPosition.getDistanceSq(this->getPosition()) > bombSize * bombSize)
	{ //超过作用范围清除
		this->autoRemovePhysicsSprite();
	}
}