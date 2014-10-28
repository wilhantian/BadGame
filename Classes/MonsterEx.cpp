#include "MonsterEx.h"
#include "Weapon.h"
#include "GameManager.h"
#include "Hero.h"
#include "StaticData.h"

USING_NS_CC;

void MonsterEx::initParam()
{
	startTag = true;
	jumpCount = 0;
	countGun = 0;

	fireTime = SD_FLOAT("monster_float_fireTime");	//开火倒计时
	fireTimeCount = fireTime;	

	speed = SD_FLOAT("monster_float_speed");
	spring = SD_FLOAT("monster_float_spring");
	moveState = MOVE_STOP;
	//设置朝向
	this->setDir(DIR_RIGHT);
	//设置血量
	this->setHp(SD_INT("monster_int_hp"));

	this->getBody()->SetFixedRotation(true);//固定旋转
	//质量质心 扭转力
	b2MassData mass;
	mass.mass = SD_FLOAT("monster_float_mass");
	mass.I = SD_FLOAT("monster_float_i");
	mass.center = this->getBody()->GetLocalCenter();
	this->getBody()->SetMassData(&mass);

	//物体的类型
	this->setType(TYPE_MONSTER);
	//会和哪些物体方式碰撞
	this->setMask(
		TYPE_BRICK |
		TYPE_COIN |
		TYPE_HERO |
		TYPE_PRIZE |
		TYPE_ARTICLE |
		TYPE_WEAPON);
	//触动停止动画
	moveStop();
}

bool MonsterEx::init(float x, float y, float width, float height)
{
	if (!Aware::init(x, y, width, height))
	{
		return false;
	}
	initParam();

	return true;
}

bool MonsterEx::init(float x, float y, b2Vec2* points, int count)
{
	if (!Aware::init(x, y, points, count))
	{
		return false;
	}
	initParam();
	return true;
}

void MonsterEx::dead()
{
	Aware::dead();

	//重新设置碰撞
	setMask(TYPE_BRICK);
	//死亡时停止
	this->moveStop();
	//todo 此处应该修改
	Animate* animate = GameManager::getInstance()->getAnimate(SD_CHARS("monster_animate_dead"), SD_FLOAT("monster_float_dead_speed"));
	Action* action = Sequence::createWithTwoActions(animate, CallFunc::create(CC_CALLBACK_0(MonsterEx::ended, this)));
	this->stopAllActions();
	this->runAction(action);
}

void MonsterEx::ended()
{
	Aware::ended();
	this->autoRemovePhysicsSprite();
}

void MonsterEx::moveStop()
{
	//如果不是第一次stop  且未移动 那么不播放停止动作
	if (!startTag && moveState == MOVE_STOP)
	{
		return;
	}
	startTag = false;	//第一次标识更改false
	moveState = MOVE_STOP;
	b2Vec2 vec = this->getBody()->GetLinearVelocity();
	vec.x = 0;
	this->getBody()->SetLinearVelocity(vec);
	//todo 此处应该修改
	Animate* animate = GameManager::getInstance()->getAnimate(SD_CHARS("monster_animate_stop"), SD_FLOAT("monster_float_stop_speed"));
	this->stopAllActions();
	this->runAction(RepeatForever::create(animate));
}

void MonsterEx::moveLeft()
{
	if (moveState == MOVE_LEFT)
		return;
	if (isDie() || isOver())
		return;

	this->setDir(DIR_LEFT);
	moveState = MOVE_LEFT;
}

void MonsterEx::moveRight()
{
	if (moveState == MOVE_RIGHT)
		return;
	if (isDie() || isOver())
		return;

	this->setDir(DIR_RIGHT);
	moveState = MOVE_RIGHT;
}

void MonsterEx::jump()
{
	if (jumpCount >= 1)
		return;
	if (isDie() || isOver())
		return;

	b2Vec2 vec = this->getBody()->GetLinearVelocity();
	vec.y = spring;
	this->getBody()->SetLinearVelocity(vec);

	jumpCount++;
}

void MonsterEx::update(float ft)
{
	Aware::update(ft);

	/*向左移动*/
	if (moveState == MOVE_LEFT)
	{
		b2Vec2 vec = this->getBody()->GetLinearVelocity();
		vec.x = -speed;
		this->getBody()->SetLinearVelocity(vec);
	}
	/*向右移动*/
	else if (moveState == MOVE_RIGHT)
	{
		b2Vec2 vec = this->getBody()->GetLinearVelocity();
		vec.x = speed;
		this->getBody()->SetLinearVelocity(vec);
	}
	//todo///////////AI///////////////////
	Hero* hero = GameManager::getInstance()->hero;

	fireTimeCount = fireTimeCount - ft;
	//什么时候发射一颗子弹
	if (fireTimeCount <= 0)
	{
		fireTimeCount = fireTime;
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

void MonsterEx::BeginContact(GameObject* other, b2Contact* contact)
{
	if (other->getType() == TYPE_BRICK || other->getType() == TYPE_ARTICLE)
	{//踩到地板或者物体时候
		//获取碰撞后产生的合力方向
		float y = contact->GetManifold()->localNormal.y;
		if (y > 0)
		{ //踩到地板
			jumpCount = 0;	//跳跃清零
		}
	}
}

void MonsterEx::fire()
{
	if (isDie() || isOver())
		return;
	Weapon* w = Weapon::create(this);
	//添加到herolayer上
	GameManager::getInstance()->heroLayer->addChild(w, 50);
}
