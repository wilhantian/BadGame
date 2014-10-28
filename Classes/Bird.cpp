#include "Bird.h"
#include "GameManager.h"
#include "Hero.h"
#include "StaticData.h"

USING_NS_CC;

bool Bird::init(float x, float y, float width, float height)
{
	if (!Aware::init(x, y, width, height))
	{
		return false;
	}
	startTag = true;
	this->setType(TYPE_ANIMAL);
	//视野
	sight = SD_INT("bird_int_sight_distance")*SD_INT("bird_int_sight_distance");	

	flyStop();

	return true;
}

void Bird::dead()
{
	Aware::dead();
	//todo
	ended();
}

void Bird::ended()
{
	Aware::ended();
	this->autoRemovePhysicsSprite();
}

void Bird::flyStop()
{
	fly = false;
	this->getBody()->SetType(b2_dynamicBody);
	Animate* action = GameManager::getInstance()->getAnimate(SD_CHARS("bird_animate_stop"), SD_FLOAT("bird_float_stop_speed"));
	this->setMask(TYPE_WEAPON | TYPE_BRICK);
	this->stopAllActions();
	this->runAction(RepeatForever::create(action));
}

void Bird::flyTo(cocos2d::Vec2 vec)
{
	fly = true;
	this->getBody()->SetType(b2_kinematicBody);
	this->setMask(TYPE_WEAPON);
	//todo 这里应该设置随机时间、5
	MoveTo* action1 = MoveTo::create(5, vec);
	Animate* action2 = GameManager::getInstance()->getAnimate(SD_CHARS("bird_animate_fly"), SD_FLOAT("bird_float_fly_speed"));
	this->stopAllActions();
	this->runAction(action1);
	this->runAction(RepeatForever::create(action2));
}

bool Bird::isFly()
{
	return fly;
}

void Bird::update(float ft)
{
	Aware::update(ft);
	if (isFly())
	{
		this->setPhysicsPosition(this->getPosition());
	}
	else
	{	//如果英雄靠近鸟儿，那么飞
		Hero* hero = GameManager::getInstance()->hero;
		Vec2 heroVec = hero->getPosition();
		Vec2 birdVec = this->getPosition();
		//如果在视野之内
		if (birdVec.getDistanceSq(heroVec) < sight && !startTag)
			flyTo(Vec2(-100, 960));	//todo	应该随机飞到屏幕外后消失，待实现
		else
			startTag = false;
	}
}