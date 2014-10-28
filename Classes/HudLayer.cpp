#include "HudLayer.h"
#include "GameManager.h"
#include "Hero.h"
#include "StaticData.h"
#include "ConfigData.h"

USING_NS_CC;

bool HudLayer::init()
{
	if (!Layer::init())
		return false;
	//血量HUD	
	int hp = SD_INT("hero_int_hp");
	for (int i = 0; i < hp; i++)
	{
		Sprite* s_hp = Sprite::create("HUD/hud_heartFull.png");
		char name[20];
		sprintf(name, "HP_%d", i);
		s_hp->setName(name);
		s_hp->setPosition(CD_FLOAT("hud_hp_x") + i * 75, 640 - CD_FLOAT("hud_hp_y"));
		this->addChild(s_hp);
	}
	//////////////////金币HUD///////////////////
	//金币图标
	Sprite* c_hp = Sprite::create("HUD/hud_coins.png");
	c_hp->setPosition(CD_FLOAT("hud_coin_x"), 640 - CD_FLOAT("hud_coin_y"));
	this->addChild(c_hp);
	//数字
	plabelAtlas = LabelAtlas::create("0123456789", "HUD/hud_num.png", 32, 40, '0');
	plabelAtlas->setAnchorPoint(Vec2(0, 0.5));
	plabelAtlas->setPosition(CD_FLOAT("hud_coin_x")+30, 640 - CD_FLOAT("hud_coin_y"));
	this->addChild(plabelAtlas);

	return true;
}

void HudLayer::replaceHpHud()
{
	Hero* hero = GameManager::getInstance()->hero;
	if (hero == nullptr)
	{
		return;
	}
	int hp = hero->getHp();
	//更新HUD
	for (int i = 0; i < SD_INT("hero_int_hp"); i++)
	{
		char name[10];
		sprintf(name, "HP_%d", i);
		Sprite* s_hp = (Sprite*)GameManager::getInstance()->hudLayer->getChildByName(name);
		if (s_hp != nullptr)
		{
			s_hp->setTexture("HUD/hud_heartFull.png");
		}
	}
	for (int i = SD_INT("hero_int_hp"); i >= hp; i--)
	{
		char name[10];
		sprintf(name, "HP_%d", i);
		Sprite* s_hp = (Sprite*)GameManager::getInstance()->hudLayer->getChildByName(name);
		if (s_hp != nullptr)
		{
			s_hp->setTexture("HUD/hud_heartEmpty.png");
		}
	}
}

void HudLayer::replaceCoinHud()
{
	Hero* hero = GameManager::getInstance()->hero;
	if (hero == nullptr)
	{
		plabelAtlas->setString("0");
		return;
	}
	int coin = hero->getCoin();
	char c_coin[6] = "0";
	sprintf(c_coin, "%d", coin);
	//设置显示文字
	plabelAtlas->setString(c_coin);
}

