#ifndef _CONFIG_DATA_H_
#define _CONFIG_DATA_H_

#include "cocos2d.h"

#define STATIC_DATA_PATH "config.xml"

#define CD_STRING(key)	ConfigData::getInstance()->stringFromKey(key)
#define CD_CHARS(key)	ConfigData::getInstance()->stringFromKey(key).c_str()
#define CD_INT(key)		ConfigData::getInstance()->intFromKey(key)
#define CD_FLOAT(key)	ConfigData::getInstance()->floatFromKey(key)
#define CD_BOOLEAN(key)	ConfigData::getInstance()->booleanFromKey(key)
#define CD_VEC2(key)	ConfigData::getInstance()->vec2FromKey(key)
#define CD_RECT(key)	ConfigData::getInstance()->rectFromKey(key)
#define CD_SIZE(key)	ConfigData::getInstance()->sizeFromKey(key)

#define SCALE_W_FLOAT(key)	Director::getInstance()->getVisibleSize().width * ConfigData::getInstance()->floatFromKey(key)/960
#define SCALE_H_FLOAT(key)	Director::getInstance()->getVisibleSize().height * ConfigData::getInstance()->floatFromKey(key)/640

class ConfigData : public cocos2d::Ref
{
private:
	ConfigData();
	~ConfigData();
protected:
	static ConfigData* staticData;
	cocos2d::ValueMap vm;
public:
	static ConfigData* getInstance();

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