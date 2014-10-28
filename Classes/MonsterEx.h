#ifndef _MONSTER_EX_H_
#define _MONSTER_EX_H_

#include "Aware.h"

class MonsterEx : public Aware
{
protected:
	bool startTag;	//第一次开始标识
	int jumpCount;
	int countGun;
	float fireTimeCount;	//开火倒计时
	float fireTime;			//开火倒计时
	/*运动状态 moveState*/
	CC_SYNTHESIZE(MOVE, moveState, MoveState);
	/*弹跳力 spring*/
	CC_SYNTHESIZE(int, spring, Spring);
	/*速度 speed*/
	CC_SYNTHESIZE(int, speed, Speed);
public:
	/*初始化英雄 只为了方便多态*/
	virtual void initParam();

	virtual bool init(float x, float y, float width, float height) override;
	CREATE_FUNC_4(MonsterEx, float, float, float, float);

	virtual bool init(float x, float y, b2Vec2* points, int count) override;
	CREATE_FUNC_4(MonsterEx, float, float, b2Vec2*, int);

	virtual void dead() override;
	virtual void ended() override;

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

	virtual void update(float ft) override;

	virtual void BeginContact(GameObject* other, b2Contact* contact);
};

#endif