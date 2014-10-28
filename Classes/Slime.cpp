#include "Slime.h"
#include "GameManager.h"
#include "Hero.h"
#include "StaticData.h"

USING_NS_CC;

bool Slime::init(float x, float y, float width, float height)
{
	if (!Aware::init(x, y, width, height))
	{
		return false;
	}

	this->setHp(SD_INT("slime_int_hp"));
	this->getBody()->SetType(b2_dynamicBody);
	this->setType(TYPE_MONSTER);
	this->setMask(
		TYPE_ARTICLE |
		TYPE_BRICK |
		TYPE_HERO |
		TYPE_WEAPON	);
	this->setDir(DIR_LEFT);
	this->setSpeed(SD_FLOAT("slime_float_speed"));

	return true;
}

void Slime::update(float ft)
{
	Aware::update(ft);

	if (this->isDie())
		return;
	//向着英雄靠拢
	b2Vec2 vec = this->getBody()->GetLinearVelocity();

	float heroX = GameManager::getInstance()->hero->getPositionX();
	float heroY = GameManager::getInstance()->hero->getPositionY();
	//作用范围
	if (abs(this->getPosition().x - heroX) > SD_FLOAT("slime_float_sight_distance") || abs(this->getPosition().y - heroY) > SD_FLOAT("slime_float_sight_distance"))
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

	this->getBody()->SetLinearVelocity(vec);
}

void Slime::moveLeft()
{
	//设置动画
	Animate* action = GameManager::getInstance()->getAnimate(SD_CHARS("slime_animate_walk_left"), SD_FLOAT("slime_float_walk_left_speed"));
	this->stopAllActions();
	this->runAction(RepeatForever::create(action));
}

void Slime::moveRight()
{
	//设置动画
	Animate* action = GameManager::getInstance()->getAnimate(SD_CHARS("slime_animate_walk_right"), SD_FLOAT("slime_float_walk_right_speed"));
	this->stopAllActions();
	this->runAction(RepeatForever::create(action));
}

void Slime::dead()
{
	Aware::dead();
	setMask(
		0);

	Animate* animate = GameManager::getInstance()->getAnimate(SD_CHARS("slime_animate_dead"), SD_FLOAT("slime_float_dead_speed"));
	Sequence* action = Sequence::createWithTwoActions(
		animate,
		CallFunc::create(CC_CALLBACK_0(Slime::ended, this)));
	this->stopAllActions();
	this->runAction(action);
	this->getBody()->SetLinearVelocity(b2Vec2(0, 5));
}

void Slime::ended()
{
	Aware::ended();
	this->autoRemovePhysicsSprite();
}
/*
void Slime::BeginContact(GameObject* other, b2Contact* contact)
{
	if (other->getType() == TYPE_HERO)
	{
		Hero* hero = GameManager::getInstance()->hero;
		if (hero->isDie())
			return;
		hero->setHp(hero->getHp() - SD_INT("slime_int_atk"));
		//英雄无敌0.5秒
		hero->setUnbeatable(0.5);

		//获取碰撞后产生的合力方向
		float y = contact->GetManifold()->localNormal.y;
		if (y > 0)
		{
			b2Vec2 vec = hero->getBody()->GetLinearVelocity();
			vec.y = SD_FLOAT("slime_float_atk_jump");
			//使英雄跳跃
			hero->getBody()->SetLinearVelocity(vec);
			//伤害史莱姆
			this->setHp(getHp()-1);
		}
	}
}
*/
void Slime::PreSolve(GameObject* other, b2Contact* contact, const b2Manifold* oldManifold)
{
	if (other->getType() == TYPE_HERO)
	{
		Hero* hero = GameManager::getInstance()->hero;
		if (hero->isDie())
			return;
		hero->setHp(hero->getHp() - SD_INT("slime_int_atk"));
		//英雄无敌0.5秒
		hero->setUnbeatable(SD_FLOAT("slime_float_unbeatable"));

		//获取碰撞后产生的合力方向
		float y = contact->GetManifold()->localNormal.y;
		if (y > 0)
		{
			b2Vec2 vec = hero->getBody()->GetLinearVelocity();
			vec.y = SD_FLOAT("slime_float_atk_jump");
			//使英雄跳跃
			hero->getBody()->SetLinearVelocity(vec);
			//伤害史莱姆
			this->setHp(getHp()-1);
		}
	}
}
