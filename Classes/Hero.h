#ifndef _HERO_H_
#define _HERO_H_

#include "GameManager.h"
#include "Aware.h"
#include "Weapon.h"

class Hero : public Aware
{
protected:
	bool startTag;	//第一次开始标识
	int jumpCount;
	int coin;	//金币
	//无敌标识
	bool unbeatable;
	//无敌时间
	float unbeatableTime;

	/*运动状态 moveState*/
	CC_SYNTHESIZE(MOVE, moveState, MoveState);
	/*弹跳力 spring*/
	CC_SYNTHESIZE(float , spring, Spring);
	/*速度 speed*/
	CC_SYNTHESIZE(float , speed, Speed);
public:
	/*初始化英雄 只为了方便多态*/
	virtual void initParam();

	virtual bool init(float x, float y, float width, float height) override;
	CREATE_FUNC_4(Hero, float, float, float, float);

	virtual bool init(float x, float y, b2Vec2* points, int count) override;
	CREATE_FUNC_4(Hero, float, float, b2Vec2*, int);

	virtual void dead() override;
	virtual void ended() override;

	/*金币*/
	void setCoin(int coin);
	int getCoin();

	/*停止移动*/
	virtual void moveStop();
	/*向左移动*/
	virtual void moveLeft();
	/*向右移动*/
	virtual void moveRight();
	/*跳跃*/
	virtual void jump();
	/*开火*/
	virtual void fire();
	/*无敌 参数：无敌时间*/
	virtual void setUnbeatable(float unbeatableTime);
	virtual bool isUnbeatable();

	virtual void update(float ft) override;

	virtual void BeginContact(GameObject* other, b2Contact* contact);

	virtual void setHp(int var);

};

#endif