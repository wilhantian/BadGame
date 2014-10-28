#ifndef _DYNAMIC_DATA_H_
#define _DYNAMIC_DATA_H_

#include "cocos2d.h"

class DynamicData : public cocos2d::Ref
{
private:
	static DynamicData* dynamicData;
	cocos2d::UserDefault* userData;

	DynamicData();
public:
	static DynamicData* getInstance();
	static void destroyInstance();
	~DynamicData();

	void init();

	void setLevel(int level);
	int getLevel();

	void setCoin(int coin);
	void addCoin(int coin);
	int getCoin();
};

#endif