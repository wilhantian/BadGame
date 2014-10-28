#include "StaticData.h"

USING_NS_CC;

StaticData* StaticData::staticData = nullptr;

StaticData* StaticData::getInstance()
{
	if (staticData == nullptr)
	{
		staticData = new StaticData();
		staticData->init();
	}
	return staticData;
}

void StaticData::init()
{
	std::string path = FileUtils::getInstance()->fullPathForFilename(STATIC_STATIC_DATA_PATH);
	vm = FileUtils::getInstance()->getValueMapFromFile(path);
}

StaticData::StaticData()
{
}

StaticData::~StaticData()
{
}

void StaticData::purge()
{
}
//////////////////////////////////////////////////////
const std::string StaticData::stringFromKey(std::string key)
{
	return vm.at(key).asString();
}

int StaticData::intFromKey(std::string key)
{
	return vm.at(key).asInt();
}

float StaticData::floatFromKey(std::string key)
{
	return vm.at(key).asFloat();
}

bool StaticData::booleanFromKey(std::string key)
{
	return vm.at(key).asBool();
}

cocos2d::Vec2 StaticData::vec2FromKey(std::string key)
{
	return PointFromString(vm.at(key).asString().c_str());
}

cocos2d::Rect StaticData::rectFromKey(std::string key)
{
	return RectFromString(vm.at(key).asString().c_str());
}

cocos2d::Size StaticData::sizeFromKey(std::string key)
{
	return SizeFromString(vm.at(key).asString().c_str());
}