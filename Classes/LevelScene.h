#ifndef _LEVEL_H_
#define _LEVEL_H_

#include "cocos2d.h"

class LevelScene : cocos2d::LayerColor
{
private:

public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	CREATE_FUNC(LevelScene);

	void backCallBack(cocos2d::Ref* ref);
	void levelsCallBack(cocos2d::Ref* ref);
};

#endif