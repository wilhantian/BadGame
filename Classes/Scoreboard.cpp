#include "Scoreboard.h"

USING_NS_CC;

Scoreboard* Scoreboard::_board = nullptr;

Scoreboard* Scoreboard::getInstance()
{
	if (_board == nullptr)
	{
		_board = new Scoreboard();
		_board->init();
	}
	return _board;
}

void Scoreboard::init()
{
	UserDefault* userData = UserDefault::getInstance();
	money = userData->getIntegerForKey("money", 0);
	killMonster = userData->getIntegerForKey("killMonster", 0);
	exp = userData->getIntegerForKey("exp", 0);
	level = userData->getIntegerForKey("level", 1);
}

void Scoreboard::save()
{
	UserDefault* userData = UserDefault::getInstance();
	userData->setIntegerForKey("money", money);
	userData->setIntegerForKey("killMonster", killMonster);
	userData->setIntegerForKey("exp", exp);
	userData->setIntegerForKey("level", level);
	userData->flush();
}

Scoreboard::~Scoreboard()
{
}

void Scoreboard::addMoney(int count)
{
	if (count < 0)
	{
		log("addMoney worng");
		return;
	}
	money += count;
}

void Scoreboard::deleteMoney(int count)
{
	if (count < 0)
	{
		log("deleteMoney worng");
		return;
	}
	money -= count;
}

int Scoreboard::getMoney()
{
	return money;
}

void Scoreboard::addKillMonster(int count)
{
	if (count < 0)
	{
		log("addKillMonster worng");
		return;
	}
	killMonster += count;
}

int Scoreboard::getKillMonster()
{
	return killMonster;
}

void Scoreboard::addExp(int count)
{
	if (count < 0)
	{
		log("addExp worng");
		return;
	}
	exp += count;
}

int Scoreboard::getExp()
{
	return exp;
}


void Scoreboard::setLevel(int level)
{
	Scoreboard::level = level;
}

int Scoreboard::getLevel()
{
	return level;
}


Scoreboard::Scoreboard()
{

}

void Scoreboard::destroyInstance()
{
	CC_SAFE_DELETE(_board);
}

