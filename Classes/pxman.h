#ifndef _PXMAN_H_
#define _PXMAN_H_

#include "cocos2d.h"
#include "Box2D/Box2D.h"

#include "GameManager.h"
#include "PhysicsSprite.h"
#include "GameObject.h"

//#define GRAVITY 10

#endif //_PXMAN_H_


/*  ===============================================================
							    学习备注
	===============================================================
	如果const位于*的左侧，则const就是用来修饰指针所指向的变量，即指针指向为常量；
	如果const位于*的右侧，const就是修饰指针本身，即指针本身是常量。

	Box2D碰撞回调函数中:
	b2Contact.GetManifold()->localNormal 可以获得两个body碰撞后产生的合力向量
	localNormal.y 如果为0-1则表示从上方发生的碰撞，如果为0 – -1则表示从下方发生的碰撞
*/