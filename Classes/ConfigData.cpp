#include "ConfigData.h"

USING_NS_CC;

ConfigData* ConfigData::staticData = nullptr;

ConfigData* ConfigData::getInstance()
{
	if (staticData == nullptr)
	{
		staticData = new ConfigData();
		staticData->init();
	}
	return staticData;
}

void ConfigData::init()
{
	std::string path = FileUtils::getInstance()->fullPathForFilename(STATIC_DATA_PATH);
	vm = FileUtils::getInstance()->getValueMapFromFile(path);
}

ConfigData::ConfigData()
{
}

ConfigData::~ConfigData()
{
}

void ConfigData::purge()
{
}
//////////////////////////////////////////////////////
const std::string ConfigData::stringFromKey(std::string key)
{
	return vm.at(key).asString();
}

int ConfigData::intFromKey(std::string key)
{
	return vm.at(key).asInt();
}

float ConfigData::floatFromKey(std::string key)
{
	return vm.at(key).asFloat();
}

bool ConfigData::booleanFromKey(std::string key)
{
	return vm.at(key).asBool();
}

cocos2d::Vec2 ConfigData::vec2FromKey(std::string key)
{
	return PointFromString(vm.at(key).asString().c_str());
}

cocos2d::Rect ConfigData::rectFromKey(std::string key)
{
	return RectFromString(vm.at(key).asString().c_str());
}

cocos2d::Size ConfigData::sizeFromKey(std::string key)
{
	return SizeFromString(vm.at(key).asString().c_str());
}