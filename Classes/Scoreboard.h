#ifndef _SCOREBOARD_H_
#define _SCOREBOARD_H_

#include "cocos2d.h"

class Scoreboard : cocos2d::Ref
{
private:
	static Scoreboard* _board;
	int money;
	int killMonster;
	int exp;
	int level;
	Scoreboard();
public:
	static Scoreboard* getInstance();
	static void destroyInstance();
	//≥ı ºªØ
	void init();
	//save
	void save();

	//+money
	void addMoney(int count);
	//-money
	void deleteMoney(int count);
	//get money
	int getMoney();

	//+killMonster
	void addKillMonster(int count);
	//get killMonster
	int getKillMonster();

	//+Exp
	void addExp(int count);
	//get Exp
	int getExp();

	void setLevel(int level);
	int getLevel();

	~Scoreboard();
};

#endif