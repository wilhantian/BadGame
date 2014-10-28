#ifndef _PHYSICS_SPRITE_H_
#define _PHYSICS_SPRITE_H_

#include "cocos2d.h"
#include "Box2D/Box2D.h"
//#include "StaticData.h"

#define GRAVITY		10
#define PTM_RATIO	96.0f //96
/////////////////////////////////////////////////////////////////
//懒人宏1
#define CREATE_FUNC_1(varType, var1)\
public: static varType* create(var1 x)\
{\
	varType *pRet = new varType(); \
	if (pRet && pRet->init(x)) \
	{ \
	pRet->autorelease(); \
	return pRet; \
	} \
	else \
	{ \
	delete pRet; \
	pRet = NULL; \
	return NULL; \
	} \
}
/////////////////////////////////////////////////////////////////
//懒人宏2
#define CREATE_FUNC_2(varType, var1, var2)\
public: static varType* create(var1 x, var2 y)\
{\
	varType *pRet = new varType(); \
	if (pRet && pRet->init(x, y)) \
	{ \
	pRet->autorelease(); \
	return pRet; \
	} \
	else \
	{ \
	delete pRet; \
	pRet = NULL; \
	return NULL; \
	} \
}
/////////////////////////////////////////////////////////////////
//懒人宏3
#define CREATE_FUNC_3(varType, var1, var2, var3)\
public: static varType* create(var1 x, var2 y, var3 width)\
{\
	varType *pRet = new varType(); \
	if (pRet && pRet->init(x, y, width)) \
	{ \
	pRet->autorelease(); \
	return pRet; \
	} \
	else \
	{ \
	delete pRet; \
	pRet = NULL; \
	return NULL; \
	} \
}
/////////////////////////////////////////////////////////////////
//懒人宏4
#define CREATE_FUNC_4(varType, var1, var2, var3, var4)\
public: static varType* create(var1 x, var2 y, var3 width, var4 height)\
{\
	varType *pRet = new varType(); \
	if (pRet && pRet->init(x, y, width, height)) \
	{ \
	pRet->autorelease(); \
	return pRet; \
	} \
	else \
	{ \
	delete pRet; \
	pRet = NULL; \
	return NULL; \
	} \
}
/////////////////////////////////////////////////////////////////
//懒人宏5
#define CREATE_FUNC_5(varType, var1, var2, var3, var4, var5)\
public: static varType* create(var1 x, var2 y, var3 width, var4 height, var5 five)\
{\
	varType *pRet = new varType(); \
	if (pRet && pRet->init(x, y, width, height, five)) \
	{ \
	pRet->autorelease(); \
	return pRet; \
	} \
	else \
	{ \
	delete pRet; \
	pRet = NULL; \
	return NULL; \
	} \
}
/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////

class PhysicsSprite : public cocos2d::Sprite
{
protected:
	b2Body* body;
	b2Fixture* fixture;
	float width;
	float height;
public:
	virtual bool init(float x, float y, float width, float height);
	CREATE_FUNC_4(PhysicsSprite, float, float, float, float);

	virtual bool init(float x, float y, b2Vec2* points, int count);
	/*points内的数字应该全部除以PTM_RATIO*/
	CREATE_FUNC_4(PhysicsSprite, float, float, b2Vec2*, int);

	void initBody(float x, float y, float width, float height);
	void initBody(float x, float y, b2Vec2* points, int count);

	/*设置物体类型 如:敌人、地板、友军等  用来做碰撞检测  type规则见头文件中声明*/
	virtual void setType(uint16 type);
	/*获取物体类型 如:敌人、地板、友军等  用来做碰撞检测  type规则见头文件中声明*/
	virtual uint16 getType() const;
	/*设置该精灵会与哪些类型物体发生碰撞*/
	virtual void setMask(uint16 types);
	
	/*获取包围盒宽
	 *注意 返回值为真实的像素单位
	 */
	virtual float getBodyBoundingBoxWidth();
	/*获取包围盒高
	 *注意 返回值为真实的像素单位
	 */
	virtual float getBodyBoundingBoxHeight();

	/*获取b2body对象*/
	virtual b2Body* getBody() const;
	/*获取当前精灵的夹具*/
	virtual b2Fixture* getFixture() const;

	/* 设置物理body与精灵坐标 屏幕像素为单位
	 */
	virtual void setPhysicsSpritePosition(float x, float y);
	/* 设置物理body与精灵坐标 屏幕像素为单位
	 */
	virtual void setPhysicsSpritePosition(cocos2d::Vec2 vec2);
	/* 设置物理body坐标 
	 * 如果你想设置全局精灵坐标 不推荐使用此方法 请见setPhysicsSpritePosition
	 */
	virtual void setPhysicsPosition(float x, float y);
	/* 设置物理body坐标
	* 如果你想设置全局精灵坐标 不推荐使用此方法 请见setPhysicsSpritePosition
	*/
	virtual void setPhysicsPosition(cocos2d::Vec2 vec2);

	/* 直接删除物理对象与精灵
	 * 注意 删除时涉及到碰撞迭代的同步问题，不要直接使用此方法，要删除某个精灵是应该调用autoRemovePhysicsSprite()
	 */
	virtual void removePhysicsSprite();
	/* 直接删除物理body 注意事项同上
	 * 不推荐使用，应为body保存着该精灵的引用，一旦销毁body，autoRemovePhy...将出现异常！
	 * 想要一个物理特征实现，应该设置其碰撞条件, 也就是Mask
	 */
	virtual void removeBody();

	/* 删除对象与精灵 推荐*/
	virtual void autoRemovePhysicsSprite();
};

#endif