#ifndef _STATIC_DATA_H_
#define _STATIC_DATA_H_

#include "cocos2d.h"

#define STATIC_STATIC_DATA_PATH "test.xml"

#define SD_STRING(key)	StaticData::getInstance()->stringFromKey(key)
#define SD_CHARS(key)	StaticData::getInstance()->stringFromKey(key).c_str()
#define SD_INT(key)		StaticData::getInstance()->intFromKey(key)
#define SD_FLOAT(key)	StaticData::getInstance()->floatFromKey(key)
#define SD_BOOLEAN(key)	StaticData::getInstance()->booleanFromKey(key)
#define SD_VEC2(key)	StaticData::getInstance()->vec2FromKey(key)
#define SD_RECT(key)	StaticData::getInstance()->rectFromKey(key)
#define SD_SIZE(key)	StaticData::getInstance()->sizeFromKey(key)

class StaticData : public cocos2d::Ref
{
private:
	StaticData();
	~StaticData();
protected:
	static StaticData* staticData;
	cocos2d::ValueMap vm;
public:
	static StaticData* getInstance();

	virtual void init();
	//ÊÍ·Å×ÊÔ´
	virtual void purge();

	const std::string stringFromKey(std::string key);
	int intFromKey(std::string key);
	float floatFromKey(std::string key);
	bool booleanFromKey(std::string key);

	cocos2d::Vec2 vec2FromKey(std::string key);
	cocos2d::Rect rectFromKey(std::string key);
	cocos2d::Size sizeFromKey(std::string key);
};

#endif