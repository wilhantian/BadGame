#ifndef _BIRD_H_
#define _BIRD_H_

#include "Aware.h"

class Bird : public Aware
{
protected:
	bool fly;
	bool startTag;	//第一次标识
	int sight;	//视野
public:
	virtual bool init(float x, float y, float width, float height) override;
	CREATE_FUNC_4(Bird, float, float, float, float);

	/*停止飞行-降落*/
	virtual void flyStop();
	/*飞到*/
	virtual void flyTo(cocos2d::Vec2 vec);
	/*是否在飞*/
	virtual bool isFly();

	virtual void dead();
	virtual void ended();

	virtual void update(float ft);
};

#endif