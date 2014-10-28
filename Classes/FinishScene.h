#ifndef _FINISH_SCENE_H_
#define _FINISH_SCENE_H_

#include "cocos2d.h"
#include "PhysicsSprite.h"

class FinishScene : public cocos2d::LayerColor
{
private:
	bool win;
	int coin;
	//int level;
public:
	static cocos2d::Scene* createScene(int coin);

	virtual bool init(int coin);

	//CREATE_FUNC(FinishScene);
	CREATE_FUNC_1(FinishScene, int);

	void setCoin(int coin);

	//void setLevel(int Level);

	void nextCallBack(cocos2d::Ref* ref);
	void againCallBack(cocos2d::Ref* ref);
};

#endif