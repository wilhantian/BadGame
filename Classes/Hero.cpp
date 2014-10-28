#include "Hero.h"
#include "Grenade.h"
#include "StaticData.h"
#include "HudLayer.h"
#include "FinishScene.h"

USING_NS_CC;

void Hero::initParam()
{
	startTag = true;
	jumpCount = 0;
	setCoin(0);//金币 todo
	unbeatable = false; //无敌标识
	unbeatableTime = 0;	//无敌时间
	
	speed = SD_FLOAT("hero_float_speed");	//行走速度
	spring = SD_FLOAT("hero_float_spring");	//弹跳力
	moveState = MOVE_STOP;
	//设置朝向
	this->setDir(DIR_RIGHT);
	//设置血量
	this->setHp(SD_INT("hero_int_hp"));

	this->getBody()->SetFixedRotation(true);

	b2MassData mass;
	mass.mass = SD_FLOAT("hero_float_mass");
	mass.I = SD_FLOAT("hero_float_i");
	mass.center = this->getBody()->GetLocalCenter();
	this->getBody()->SetMassData(&mass);

	//物体的类型
	this->setType(TYPE_HERO);
	//会和哪些物体方式碰撞
	this->setMask(
		TYPE_BRICK |
		TYPE_COIN |
		TYPE_MONSTER |
		TYPE_PRIZE |
		TYPE_ARTICLE |
		TYPE_WEAPON);
	//触动停止动画
	moveStop();
}

bool Hero::init(float x, float y, float width, float height)
{
	if(!Aware::init(x, y, width, height))
	{
		return false;
	}
	initParam();

	return true;
}

bool Hero::init(float x, float y, b2Vec2* points, int count)
{
	if(!Aware::init(x, y, points, count))
	{
		return false;
	}
	initParam();
	return true;
}

void Hero::dead()
{
	Aware::dead();
	//重新设置碰撞
	setMask(TYPE_BRICK);
	//死亡时停止
	this->moveStop();
	Animate* animate = GameManager::getInstance()->getAnimate(SD_CHARS("hero_animate_dead"), SD_FLOAT("hero_float_dead_speed"));
	Action* action = Sequence::createWithTwoActions(animate, CallFunc::create(CC_CALLBACK_0(Hero::ended, this)));
	this->stopAllActions();
	this->runAction(action);
}

void Hero::ended()
{
	Aware::ended();
	//跳转到结束场景
	auto finish = FinishScene::createScene(coin);
	Director::getInstance()->replaceScene(finish);
}

void Hero::moveStop()
{
	//如果不是第一次stop  且未移动 那么不播放停止动作
	if(!startTag && moveState == MOVE_STOP)
	{
		return;
	}
	startTag = false;	//第一次标识更改false
	moveState = MOVE_STOP;
	b2Vec2 vec = this->getBody()->GetLinearVelocity();
	vec.x = 0;
	this->getBody()->SetLinearVelocity(vec);

	Animate* animate = GameManager::getInstance()->getAnimate(SD_CHARS("hero_animate_stop"), SD_FLOAT("hero_float_stop_speed"));
	this->stopAllActions();
	this->runAction(RepeatForever::create(animate));
}

void Hero::moveLeft()
{
	if(moveState == MOVE_LEFT)
		return;
	if(isDie() || isOver())
		return;

	this->setDir(DIR_LEFT);
	moveState = MOVE_LEFT;
	//播放动画
	Animate* animate = GameManager::getInstance()->getAnimate(SD_CHARS("hero_animate_walk_left"), SD_FLOAT("hero_float_walk_left_speed"));
	this->stopAllActions();
	this->runAction(RepeatForever::create(animate));
}

void Hero::moveRight()
{
	if(moveState == MOVE_RIGHT)
		return;
	if(isDie() || isOver())
		return;

	this->setDir(DIR_RIGHT);
	moveState = MOVE_RIGHT;
	//播放动画
	Animate* animate = GameManager::getInstance()->getAnimate(SD_CHARS("hero_animate_walk_right"), SD_FLOAT("hero_float_walk_right_speed"));
	this->stopAllActions();
	this->runAction(RepeatForever::create(animate));
}

void Hero::jump()
{
	if(jumpCount >= 2)
		return;
	if(isDie() || isOver())
		return;
	
	b2Vec2 vec = this->getBody()->GetLinearVelocity();
	vec.y = spring;
	this->getBody()->SetLinearVelocity(vec);
	
	jumpCount++; //累加 二段跳用
}

void Hero::update(float ft)
{
	Aware::update(ft);
	/*向左移动*/
	if(moveState == MOVE_LEFT)
	{
		b2Vec2 vec = this->getBody()->GetLinearVelocity();
		vec.x = -speed;
		this->getBody()->SetLinearVelocity(vec);
	}
	/*向右移动*/
	else if(moveState == MOVE_RIGHT)
	{
		b2Vec2 vec = this->getBody()->GetLinearVelocity();
		vec.x = speed;
		this->getBody()->SetLinearVelocity(vec);
	}
	/*修改无敌时间*/
	unbeatableTime = unbeatableTime - ft;
	if (unbeatableTime <= 0)
		unbeatable = false;
}

void Hero::BeginContact(GameObject* other, b2Contact* contact)
{
	if(other->getType() == TYPE_BRICK )
	{//踩到地板或者物体时候
		//获取碰撞后产生的合力方向
		float y = contact->GetManifold()->localNormal.y;
		if (y > 0)
		{ //踩到地板
			jumpCount = 0;	//跳跃清零
		}
	}
	else if (other->getType() == TYPE_ARTICLE)
	{
		jumpCount = 0;
	}
}

void Hero::fire()
{
	if (isDie() || isOver())
		return;
// 	Weapon* w = Weapon::create(this);
// 	GameManager::getInstance()->heroLayer->addChild(w, 50);

	Grenade* g = Grenade::create(this);
	GameManager::getInstance()->heroLayer->addChild(g, 51);
}

void Hero::setCoin(int coin)
{
	this->coin = coin;
	//重新绘制钱包数量
	GameManager::getInstance()->hudLayer->replaceCoinHud();
}

int Hero::getCoin()
{
	return coin;
}

void Hero::setUnbeatable(float unbeatableTime)
{
	if(!unbeatable)
		this->unbeatableTime = unbeatableTime;
	unbeatable = true;
}

bool Hero::isUnbeatable()
{
	return unbeatable;
}

void Hero::setHp(int var)
{
	if (isUnbeatable()) //如果无敌 就不设置血量了
		return;
	Aware::setHp(var);
	//更新HUD
	GameManager::getInstance()->hudLayer->replaceHpHud();
}
