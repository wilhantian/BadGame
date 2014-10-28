#ifndef _ARTICLE_H_
#define _ARTICLE_H_
/*
	物品
	可以交互的、无用途的
*/
#include "LifeObject.h"

class Article : public LifeObject
{
protected:

public:
	void initParam();

	virtual bool init(float x, float y, float width, float height) override;
	CREATE_FUNC_4(Article, float, float, float, float);

	virtual bool init(float x, float y, b2Vec2* points, int count) override;
	CREATE_FUNC_4(Article, float, float, b2Vec2*, int);

	virtual void dead();

	virtual void ended();
};
#endif