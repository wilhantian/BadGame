#ifndef _ABOUT_SCENE_H
#define _ABOUT_SCENE_H

#include "cocos2d.h"

class AboutScene : cocos2d::LayerColor
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	CREATE_FUNC(AboutScene);
};

#endif