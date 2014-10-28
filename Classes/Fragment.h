#ifndef _FRAGMENT_H_
#define _FRAGMENT_H_
/*
	碎片
	爆炸后具有伤害和作用距离的碎片
*/
#include "GameObject.h"

class Fragment : public GameObject
{
protected:
	int atk;
	int bombSize;	//作用距离	像素单位
	bool killHero;
	cocos2d::Vec2 startPosition;
public:
	virtual bool init(float x, float y, b2Vec2 speed, int size, bool killHero);
	CREATE_FUNC_5(Fragment, float, float, b2Vec2, int, bool);	//位置X、位置Y, 方向速度,碎片大小,是否对英雄造成伤害

	virtual void BeginContact(GameObject* other, b2Contact* contact);

	virtual void update(float ft) override;
};

#endif