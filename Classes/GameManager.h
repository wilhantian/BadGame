#ifndef _GAME_MANAGER_H_
#define _GAME_MANAGER_H_

#include "cocos2d.h"
//#include "PhysicsSprite.h"
#include "GameObject.h"

class PhysicsSprite;
class Hero;
class HudLayer;

enum GAME_STATIC
{
	WIN,
	FAILED,
	PLAYING
};

class GameManager : public cocos2d::Ref, public b2ContactListener
{
private:
	static GameManager* gameManager;
	cocos2d::Vector<PhysicsSprite*> _deleteSprites;	//待删除的物理精灵
	b2World* world;
	float sceneX;	//屏幕当前位置X
	float sceneY;	//屏幕当前位置Y
	//int level;
	GameManager();
public:
	cocos2d::Layer* staticLayer;	//静态层 底层
	cocos2d::Layer* gameLayer;		//游戏主层--地图层
	cocos2d::Layer* bkLayer;		//视差背景层
	cocos2d::Layer* settingLayer;	//设置层
	cocos2d::Layer* weaponLayer;	//子弹层
	cocos2d::Layer* heroLayer;		//英雄层
	cocos2d::Layer* monsterLayer;	//怪物层
	cocos2d::Layer* thingLayer;		//事物层
	HudLayer* hudLayer;		//HUD层

	Hero* hero;			//英雄
public:
	static GameManager* getInstance();
	static void destroyInstance();
	~GameManager();

	/*初始化物理世界*/
	void initPhysicsWorld(float gravity);
	/*更新物理世界*/
	void step(float time);
	/*获取物理世界*/
	b2World* getWorld();

	/*初始化资源*/
	void initRes();
	
	/*获取Animation*/
	cocos2d::Animation* getAnimation(const char* src, float delay = 0.0f, unsigned int loops = 1U);
	/*获取Animate*/
	cocos2d::Animate* getAnimate(const char* src, float delay = 0.0f, unsigned int loops = 1U);
	
	/*物理精灵压入删除栈*/
	void pushDeleteSprite(PhysicsSprite* sprite);

	virtual void BeginContact(b2Contact* contact);
	virtual void EndContact(b2Contact* contact);
	virtual void PreSolve(b2Contact* contact, const b2Manifold* oldManifold);
	virtual void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse);

// 	/*当前关卡*/
// 	void setLevel(int level);
// 	int getLevel();
};

#endif	//_GAME_MANAGER_H_