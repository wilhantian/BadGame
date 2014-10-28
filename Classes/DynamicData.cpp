#include "DynamicData.h"

USING_NS_CC;

DynamicData* DynamicData::dynamicData = nullptr;

DynamicData::DynamicData()
{
}

DynamicData* DynamicData::getInstance()
{
	if (dynamicData == nullptr)
	{
		dynamicData = new DynamicData();
		dynamicData->init();
	}
	return dynamicData;
}

void DynamicData::init()
{
	userData = UserDefault::getInstance();
}

DynamicData::~DynamicData()
{

}

void DynamicData::destroyInstance()
{
	CC_SAFE_DELETE(dynamicData);
}

void DynamicData::setLevel(int level)
{
	userData->setIntegerForKey("level", level);
	userData->flush();
}

int DynamicData::getLevel()
{
	return userData->getIntegerForKey("level", 1);
}

void DynamicData::setCoin(int coin)
{
	userData->setIntegerForKey("coin", coin);
	userData->flush();
}

void DynamicData::addCoin(int coin)
{
	userData->setIntegerForKey("coin", coin + getCoin());
	userData->flush();
}

int DynamicData::getCoin()
{
	return userData->getIntegerForKey("coin", 0);
}
