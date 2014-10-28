#ifndef _LIFE_BOJECT_H_
#define _LIFE_BOJECT_H_

#include "GameObject.h"

class LifeObject : public GameObject{
protected:
	bool die;
	bool over;
public:
	virtual bool init(float x, float y, float width, float height) override;
	CREATE_FUNC_4(LifeObject, float, float, float, float);

	virtual bool init(float x, float y, b2Vec2* points, int count) override;
	CREATE_FUNC_4(LifeObject, float, float, b2Vec2*, int);

	//血量
	CC_SYNTHESIZE(int, hp, Hp);	
	//攻击力
	CC_SYNTHESIZE(int, atk, Atk);	

	/*设置死亡状态*/
	virtual void setDie(bool die);
	/*判断当前生命体是否死亡*/
	virtual bool isDie() const;
	/*设置结束状态*/
	virtual void setOver(bool over);
	/*该生命体是否结束*/
	virtual bool isOver() const;

	/*逐帧回调函数*/
	virtual void update(float ft);
	
	/* 自动调用 死亡时的回调函数 动画神马的重写该函数即可 该函数会在hp低于0时自动调用一次*/
	virtual void dead();
	/* 注意注意，本函数不会自动调用~ 推荐将本函数写入动作毁掉函数中
	 * 甚至可以通过延迟动作保留尸体到一定时间
	 * 调用此方法会直接删除物理精灵,并设置over=true
	 * 按道理此方法不应该出现在本类中，以后的重构中应该修改此问题
	 */
	virtual void ended();
};

#endif