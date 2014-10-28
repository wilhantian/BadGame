#ifndef _WALL_H_
#define _WALL_H_

#include "GameObject.h"

class Wall : public GameObject
{
public:
	void initParam();
	virtual bool init(float x, float y, float width, float height) override;
	CREATE_FUNC_4(Wall, float, float, float, float);

	virtual bool init(float x, float y, b2Vec2* points, int count) override;
	CREATE_FUNC_4(Wall, float, float, b2Vec2*, int);
};

#endif