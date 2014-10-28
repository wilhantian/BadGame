#ifndef _MAP_ANALYSIS_H_
#define _MAP_ANALYSIS_H_

#include "cocos2d.h"

class MapAnalysis : public cocos2d::Ref
{
private:
	MapAnalysis();
protected:
	static MapAnalysis* _mapAnalysis;
public:
	static MapAnalysis* getInstance();
	~MapAnalysis();
	void initMap(char* leveName);
	void initMap(int level);
};

#endif