#ifndef _TEXT_DATA_H_
#define _TEXT_DATA_H_

#include "cocos2d.h"

#define TEXT_DATA_PATH "text.xml"

#define TD_STRING(key)	TextData::getInstance()->stringFromKey(key)
#define TD_CHARS(key)	TextData::getInstance()->stringFromKey(key).c_str()
#define TD_FLOAT(key)	TextData::getInstance()->floatFromKey(key)

class TextData : public cocos2d::Ref
{
private:
	TextData();
	~TextData();
protected:
	static TextData* staticData;
	cocos2d::ValueMap vm;
public:
	static TextData* getInstance();

	virtual void init();
	//สอทลืสิด
	virtual void purge();

	const std::string stringFromKey(std::string key);
	float floatFromKey(std::string key);
};

#endif