#include "FinishScene.h"
#include "DynamicData.h"
#include "ConfigData.h"
#include "GameManager.h"
#include "LevelScene.h"
#include "GameScene.h"
#include "Hero.h"
#include "HelloWorldScene.h"
#include "TextData.h"
#include "JINTools.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
//友盟统计头
#include "MobClickCpp.h"
#endif

USING_NS_CC;

cocos2d::Scene* FinishScene::createScene(int coin)
{
	Scene* scene = Scene::create();
	Layer* layer = FinishScene::create(coin);
	scene->addChild(layer);
	return scene;
}

bool FinishScene::init(int coin)
{
	if (!LayerColor::initWithColor(Color4B(111, 240, 255, 255)))
	{
		return false;
	}
	//显示广告
	JINTools::showAdScreen();

	setCoin(coin);
	//setLevel(level);

	Sprite* down_bk = Sprite::create("UI/FINISH/redBk.png");
	down_bk->setAnchorPoint(Vec2(0, 0));
	down_bk->setPosition(0, 0-80);
	this->addChild(down_bk);

	//数字
	Sprite* coin_sprite = Sprite::create("HUD/hud_coins.png");
	coin_sprite->setPosition(CD_FLOAT("finish_scence_coin_x"), CD_FLOAT("finish_scence_coin_y"));
	this->addChild(coin_sprite);

	LabelAtlas* plabelAtlas = LabelAtlas::create("0123456789", "HUD/hud_num.png", 32, 40, '0');
	plabelAtlas->setAnchorPoint(Vec2(0.5, 0.5));
	plabelAtlas->setPosition(CD_FLOAT("finish_scence_num_x") + 30, CD_FLOAT("finish_scence_num_y"));
	this->addChild(plabelAtlas);

	char c_coin[6];
	sprintf(c_coin, "%d", coin);
	plabelAtlas->setString(c_coin);

	//next
	//开始按钮
	Menu* menu = Menu::create();
	menu->setAnchorPoint(Vec2(0, 0));
	menu->setPosition(0, 0);
	this->addChild(menu);
		
	Size size(960, 640);
	if (!GameManager::getInstance()->hero->isDie())	//如果完成任务  执行以下操作
	{
		//结束文字
		int random = CCRANDOM_0_1() * 2 + 1;	//1-3随机数.
		char tagName[24];
		sprintf(tagName, "h%d", random);
		TTFConfig ttfConfig("fonts/font.ttf", 40);
		auto bad_game_en = Label::createWithTTF(ttfConfig, TD_STRING(tagName));
		bad_game_en->setTextColor(Color4B(251, 96, 104, 255));
		bad_game_en->setPosition(960 / 2, TD_FLOAT("finish_text_y"));
		this->addChild(bad_game_en);
		//按钮
		MenuItemImage* buttonStart = MenuItemImage::create("UI/GAME/next1.png", "UI/GAME/next2.png", "UI/GAME/next2.png", CC_CALLBACK_1(FinishScene::nextCallBack, this));
		buttonStart->setPosition(CD_FLOAT("finish_scence_next_x"), CD_FLOAT("finish_scence_next_y"));
		menu->addChild(buttonStart);
		log("--------------------NEXT LEVEL----------------------");
	} 
	else
	{
		//结束文字
		int random = CCRANDOM_0_1() * 2 + 1;	//1-3随机数
		char tagName[24];
		sprintf(tagName, "s%d", random);
		TTFConfig ttfConfig("fonts/font.ttf", 40);
		auto bad_game_en = Label::createWithTTF(ttfConfig, TD_STRING(tagName));
		bad_game_en->setTextColor(Color4B(251, 96, 104, 255));
		bad_game_en->setPosition(960 / 2, TD_FLOAT("finish_text_y"));
		this->addChild(bad_game_en);
		//按钮
		MenuItemImage* buttonStart = MenuItemImage::create("UI/GAME/up_break.png", "UI/GAME/down_break.png", "UI/START_UI_UP_0003__.png", CC_CALLBACK_1(FinishScene::againCallBack, this));
		buttonStart->setPosition(CD_FLOAT("finish_scence_next_x"), CD_FLOAT("finish_scence_next_y"));
		menu->addChild(buttonStart);
		log("--------------------BACK LEVEL---------------------");
	}

	return true;
}

void FinishScene::setCoin(int coin)
{
	FinishScene::coin = coin;
}

// void FinishScene::setLevel(int Level)
// {
// 	FinishScene::level = Level;
// }

void FinishScene::nextCallBack(cocos2d::Ref* ref)
{
	//储存金币
	DynamicData::getInstance()->addCoin(coin);
	//log("Data Coin ========= %d", DynamicData::getInstance()->getCoin());
	//level
	int lastLevel = DynamicData::getInstance()->getLevel();
	//log("lastLevel ========= %d", lastLevel);
	if (lastLevel <= GameScene::level)	//开启关卡
	{
		DynamicData::getInstance()->setLevel(GameScene::level+1);
	}
	GameManager::destroyInstance();

	//友盟统计-完成任务
	char levelStr[5];
	sprintf(levelStr, "level_%d_", GameScene::level);
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	umeng::MobClickCpp::finishLevel(levelStr);
#endif

	if (GameScene::level >= 8)
	{
		Scene* scene = TransitionFade::create(1.0f, HelloWorld::createScene(), Color3B(0, 0, 0));
		Director::getInstance()->replaceScene(scene);
	}
	else
	{
		Scene* scene = TransitionFade::create(1.0f, GameScene::createScene(GameScene::level + 1), Color3B(0, 0, 0));
		Director::getInstance()->replaceScene(scene);
	}
}

void FinishScene::againCallBack(cocos2d::Ref* ref)
{
	//储存金币
	DynamicData::getInstance()->addCoin(coin);
	GameManager::destroyInstance();
	//友盟统计-失败
	char levelStr[5];
	sprintf(levelStr, "level_%d_", GameScene::level);
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	umeng::MobClickCpp::failLevel(levelStr);
#endif
	//跳转场景
	Scene* scene = TransitionFade::create(1.0f, GameScene::createScene(GameScene::level), Color3B(0, 0, 0));
	Director::getInstance()->replaceScene(scene);
}
