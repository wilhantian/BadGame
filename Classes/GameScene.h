#ifndef _GAME_SCENE_H_
#define _GAME_SCENE_H_

#include "cocos2d.h"
class Hero;
class HudLayer;

class GameScene : public cocos2d::LayerColor
{
private:
	bool pause;			//暂停标识
	cocos2d::Layer* staticLayer;	//静态层 - 基层
	cocos2d::Layer* gameLayer;		//游戏主层--地图层：staticLayer
	cocos2d::Layer* bkLayer;		//背景层-视差层
	cocos2d::Layer* settingLayer;	//设置层
	cocos2d::Layer* weaponLayer;	//特效层
	HudLayer* hudLayer;				//hud层--todo
	cocos2d::Layer* heroLayer;		//英雄层
	cocos2d::Layer* monsterLayer;	//怪物层
	cocos2d::Layer* thingLayer;		//事物层

	Hero* hero;			//英雄
	bool _left;
	bool _right;
public:
	static int level;

	static cocos2d::Scene* createScene(int level);

	virtual bool init();  

	CREATE_FUNC(GameScene);

	void update(float time);
	
	void setLeft(bool left);
	bool isLeft();
	void setRight(bool right);
	bool isRight();

	//暂停层的按钮回调
	void pauseButton(Ref* ref);
	void backButton(Ref* ref);
	void homeButton(Ref* ref);
	void breakButton(Ref* ref);
};

#endif