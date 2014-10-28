#include "TextData.h"

USING_NS_CC;

TextData* TextData::staticData = nullptr;

TextData* TextData::getInstance()
{
	if (staticData == nullptr)
	{
		staticData = new TextData();
		staticData->init();
	}
	return staticData;
}

void TextData::init()
{
	std::string path = FileUtils::getInstance()->fullPathForFilename(TEXT_DATA_PATH);
	vm = FileUtils::getInstance()->getValueMapFromFile(path);
}

TextData::TextData()
{
}

TextData::~TextData()
{
}

void TextData::purge()
{
}
//////////////////////////////////////////////////////
const std::string TextData::stringFromKey(std::string key)
{
	return vm.at(key).asString();
}

float TextData::floatFromKey(std::string key)
{
	return vm.at(key).asFloat();
}
