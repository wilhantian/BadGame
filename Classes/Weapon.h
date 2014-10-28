#ifndef _WEAPON_H_
#define _WEAPON_H_

#include "LifeObject.h"
class Aware;

class Weapon : public LifeObject
{
protected:
	Aware* object;	//所属对象
	DIR dir;		//子弹方向
	int speed;		//速度
	float startY;		//初始Y
	bool startTag;	//初始标识
public:
	virtual bool init(Aware* object);
	CREATE_FUNC_1(Weapon, Aware*);
	/*设置子弹速度*/
	virtual void setSpeed(float speed);
	/*获取子弹速度*/
	virtual int getSpeed();

	virtual void update(float ft);
	virtual void dead();
	virtual void ended();
	
	virtual void PreSolve(GameObject* othera, b2Contact* contact, const b2Manifold* oldManifold);

};

#endif