#include "FlyingSlime.h"
#include "Hero.h"
#include "GameManager.h"
#include "StaticData.h"

USING_NS_CC;

bool FlyingSlime::init(float x, float y, float width, float height)
{
	if (!Aware::init(x, y, width, height))
	{
		return false;
	}
	//设置速度
	setSpeed(SD_FLOAT("flyingslime_float_speed"));

	this->getBody()->SetFixedRotation(true);
	this->getBody()->SetType(b2_kinematicBody);

	setType(TYPE_MONSTER);
	setMask(
		TYPE_WEAPON |
		TYPE_HERO);

	setAtk(SD_INT("flyingslime_int_atk"));
	setHp(SD_INT("flyingslime_int_hp"));
	//设置方向
	this->setDir(DIR_LEFT);
	//设置动画
	Animate* action = GameManager::getInstance()->getAnimate(SD_CHARS("flyingslime_animate_fly_left"), SD_FLOAT("flyingslime_float_fly_left_speed"));
	this->runAction(RepeatForever::create(action));

	return true;
}

void FlyingSlime::update(float ft)
{
	Aware::update(ft);

	if (this->isDie())
		return;
	//向着英雄靠拢
	b2Vec2 vec;

	float heroX = GameManager::getInstance()->hero->getPositionX();
	float heroY = GameManager::getInstance()->hero->getPositionY();
	//作用范围
	if (abs(this->getPosition().x - heroX) > SD_FLOAT("flyingslime_float_sight_distance") || abs(this->getPosition().y - heroY) > SD_FLOAT("flyingslime_float_sight_distance"))
	{
		vec.x = 0;
		vec.y = 0;
		this->getBody()->SetLinearVelocity(vec);
		return;
	}

	if (heroX < this->getPositionX())
	{
		if (getDir() != DIR_LEFT)
		{
			setDir(DIR_LEFT);
			moveLeft();
		}
		vec.x = -getSpeed();
	}
	else
	{
		if (getDir() != DIR_RIGHT)
		{
			setDir(DIR_RIGHT);
			moveRight();
		}
		vec.x = getSpeed();
	}
	
	if (heroY > this->getPositionY())
		vec.y = getSpeed();
	else
		vec.y = -getSpeed();
	
	this->getBody()->SetLinearVelocity(vec);
}

void FlyingSlime::dead()
{
	Aware::dead();
	this->getBody()->SetType(b2_dynamicBody);
	setMask(
		TYPE_BRICK|
		TYPE_HERO);

	Animate* animate = GameManager::getInstance()->getAnimate(SD_CHARS("flyingslime_animate_dead"), SD_FLOAT("flyingslime_float_dead_speed"));
	Sequence* action = Sequence::createWithTwoActions(
		animate,
		CallFunc::create(CC_CALLBACK_0(FlyingSlime::ended, this)));
	this->stopAllActions();
	this->runAction(action);
}

void FlyingSlime::ended()
{
	Aware::ended();
	this->autoRemovePhysicsSprite();
}
/*
void FlyingSlime::BeginContact(GameObject* other, b2Contact* contact)
{
//	if (other->getType() == TYPE_HERO)
//	{
//		Hero* hero = (Hero*)other;
//		hero->setHp(hero->getHp() - getAtk());
//		//设置无敌
//		if (!hero->isUnbeatable())
//			hero->setUnbeatable(SD_FLOAT("flyingslime_float_unbeatable"));
//
//		b2Vec2 vec = this->getBody()->GetLinearVelocity();
//		vec.x = -vec.x;
//		this->getBody()->SetLinearVelocity(vec);
//	}
}
*/
void FlyingSlime::PreSolve(GameObject* other, b2Contact* contact, const b2Manifold* oldManifold)
{
	if (other->getType() == TYPE_HERO)
	{
		Hero* hero = (Hero*)other;
		hero->setHp(hero->getHp() - getAtk());
		//设置无敌
		if (!hero->isUnbeatable())
			hero->setUnbeatable(SD_FLOAT("flyingslime_float_unbeatable"));

		b2Vec2 vec = this->getBody()->GetLinearVelocity();
		vec.x = -vec.x;
		this->getBody()->SetLinearVelocity(vec);
	}
}

void FlyingSlime::moveLeft()
{
	//设置动画
	Animate* action = GameManager::getInstance()->getAnimate(SD_CHARS("flyingslime_animate_fly_left"), SD_FLOAT("flyingslime_float_fly_left_speed"));
	this->stopAllActions();
	this->runAction(RepeatForever::create(action));
}

void FlyingSlime::moveRight()
{
	//设置动画
	Animate* action = GameManager::getInstance()->getAnimate(SD_CHARS("flyingslime_animate_fly_right"), SD_FLOAT("flyingslime_float_fly_right_speed"));
	this->stopAllActions();
	this->runAction(RepeatForever::create(action));
}

