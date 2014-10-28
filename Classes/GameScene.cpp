#include "GameScene.h"
#include "GameManager.h"
#include "StaticData.h"
#include "ConfigData.h"
#include "MapAnalysis.h"
#include "Brick.h"
#include "Hero.h"
#include "MonsterEx.h"
#include "Coin.h"
#include "Fragment.h"
#include "Article.h"
#include "Bird.h"
#include "FlyingSlime.h"
#include "HudLayer.h"
#include "HelloWorldScene.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
//友盟统计头
#include "MobClickCpp.h"
#endif

USING_NS_CC;

Scene* GameScene::createScene(int level)
{
	GameScene::level = level;
	auto scene = Scene::create();
	auto layer = GameScene::create();
	scene->addChild(layer);

	return scene;
}

bool GameScene::init()
{
	if ( !LayerColor::initWithColor(Color4B(0,250,250,255)) )
	{
		return false;
	}
	pause = false;	//暂停标识为假
	/************************************************************************/
	/* 将图层存入游戏管理器中                                                   */
	/************************************************************************/
	//友盟统计-记录进入关卡
	char levelStr[5];
	sprintf(levelStr, "level_%d_", level);
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	umeng::MobClickCpp::startLevel(levelStr);
	#endif

	staticLayer = this;		//游戏静态层
	GameManager::getInstance()->staticLayer = staticLayer;
	
	gameLayer = Layer::create();		//游戏主层
	GameManager::getInstance()->gameLayer = gameLayer;
	staticLayer->addChild(gameLayer);

	ParallaxNode* praNode = ParallaxNode::create();
	bkLayer = Layer::create();		//背景层-视差层
	GameManager::getInstance()->bkLayer = bkLayer;
	gameLayer->addChild(praNode, -2); //应该小于加载地图层
	praNode->addChild(bkLayer, 1, Vec2(CD_FLOAT("bk_ratio_x"), CD_FLOAT("bk_ratio_y")), Vec2(0, 0));

	thingLayer = Layer::create();		//事物层
	GameManager::getInstance()->thingLayer = thingLayer;
	gameLayer->addChild(thingLayer);

	monsterLayer = Layer::create();	//怪物层
	GameManager::getInstance()->monsterLayer = monsterLayer;
	gameLayer->addChild(monsterLayer);

	heroLayer = Layer::create();		//英雄层
	GameManager::getInstance()->heroLayer = heroLayer;
	gameLayer->addChild(heroLayer, 100);

	weaponLayer = Layer::create();	//特效层
	GameManager::getInstance()->weaponLayer = weaponLayer;
	gameLayer->addChild(weaponLayer);

	hudLayer = HudLayer::create();	//HUD层----------todo
	GameManager::getInstance()->hudLayer = hudLayer;
	staticLayer->addChild(hudLayer);

	settingLayer = Layer::create();	//设置层
	GameManager::getInstance()->settingLayer = settingLayer;
	staticLayer->addChild(settingLayer);
	//////////////////设置层初始化////////////////////////////
	//默认不打开设置层
	settingLayer->setVisible(false);
	//背景
	Sprite* settingBk = Sprite::create("UI/GAME/bk.png");
	settingBk->setAnchorPoint(Vec2(0, 0));
	settingBk->setPosition(0, 0);
	settingLayer->addChild(settingBk);
	//Pause
	Sprite* pauseLogo = Sprite::create("UI/GAME/pause.png");
	pauseLogo->setPosition(CD_FLOAT("setting_pause_x"), CD_FLOAT("setting_pause_y"));
	settingLayer->addChild(pauseLogo);
	//菜单
	Menu* settingMenu = Menu::create();
	settingMenu->setAnchorPoint(Vec2(0, 0));
	settingMenu->setPosition(0, 0);
	settingLayer->addChild(settingMenu);
	//返回按钮
	MenuItemImage* backButton = MenuItemImage::create("UI/GAME/up_back.png", "UI/GAME/down_back.png", "UI/GAME/down_back.png", CC_CALLBACK_1(GameScene::backButton, this));
	backButton->setPosition(CD_FLOAT("setting_back_x"), CD_FLOAT("setting_back_y"));
	settingMenu->addChild(backButton);
	MenuItemImage* homeButton = MenuItemImage::create("UI/GAME/up_home.png", "UI/GAME/down_home.png", "UI/GAME/down_home.png", CC_CALLBACK_1(GameScene::homeButton, this));
	homeButton->setPosition(CD_FLOAT("setting_home_x"), CD_FLOAT("setting_home_y"));
	settingMenu->addChild(homeButton);
	MenuItemImage* breakButton = MenuItemImage::create("UI/GAME/up_break.png", "UI/GAME/down_break.png", "UI/GAME/down_break.png", CC_CALLBACK_1(GameScene::breakButton, this));
	breakButton->setPosition(CD_FLOAT("setting_break_x"), CD_FLOAT("setting_break_y"));
	settingMenu->addChild(breakButton);
	
	//////////////////初始化地图/////////////////////////////
	//
	MapAnalysis* mapAnalysis = MapAnalysis::getInstance();
	mapAnalysis->initMap(level);
	//此处糅合严重
	hero = GameManager::getInstance()->hero;
	///////////////////////////事件监听//////////////////////////////
	//申请键盘监听
	EventListenerKeyboard* event = EventListenerKeyboard::create();
	event->onKeyPressed = [=](EventKeyboard::KeyCode code, Event* event){
		if(code == EventKeyboard::KeyCode::KEY_K)
		{
			hero->jump();
		}
		else if(code == EventKeyboard::KeyCode::KEY_A)
		{
			hero->moveLeft();
		}
		else if(code == EventKeyboard::KeyCode::KEY_D)
		{
			hero->moveRight();
		}
		else if(code == EventKeyboard::KeyCode::KEY_J)
		{
			hero->fire();
		}
	};
	event->onKeyReleased = [=](EventKeyboard::KeyCode code, Event* event){
		if(code == EventKeyboard::KeyCode::KEY_A && hero->getMoveState() == MOVE_LEFT)
		{
			hero->moveStop();
		}
		else if(code == EventKeyboard::KeyCode::KEY_D && hero->getMoveState() == MOVE_RIGHT)
		{
			hero->moveStop();
		}
	};
	//按键精灵
	Sprite* but_left = Sprite::create("HUD/button_up_left.png");
	but_left->setAnchorPoint(Vec2(0, 0));
	but_left->setPosition(CD_FLOAT("hud_but_left_x"), CD_FLOAT("hud_but_left_y"));
	hudLayer->addChild(but_left);

	Sprite* but_right = Sprite::create("HUD/button_up_right.png");
	but_right->setAnchorPoint(Vec2(0, 0));
	but_right->setPosition(CD_FLOAT("hud_but_right_x"), CD_FLOAT("hud_but_right_y"));
	hudLayer->addChild(but_right);

	Sprite* but_A = Sprite::create("HUD/button_up_A.png");
	but_A->setAnchorPoint(Vec2(0, 0));
	but_A->setPosition(CD_FLOAT("hud_but_A_x"), CD_FLOAT("hud_but_A_y"));
	hudLayer->addChild(but_A);

	Sprite* but_B = Sprite::create("HUD/button_up_B.png");
	but_B->setAnchorPoint(Vec2(0, 0));
	but_B->setPosition(CD_FLOAT("hud_but_B_x"), CD_FLOAT("hud_but_B_y"));
	hudLayer->addChild(but_B);
	//hud菜单
	Menu* hudMenu = Menu::create();
	hudMenu->setAnchorPoint(Vec2(0, 0));
	hudMenu->setPosition(0, 0);
	hudLayer->addChild(hudMenu);
	//暂停按钮
	MenuItemImage* pauseButton = MenuItemImage::create("UI/GAME/pause_button.png", "UI/GAME/pause_button.png", "UI/GAME/pause_button.png", CC_CALLBACK_1(GameScene::pauseButton, this));
	pauseButton->setPosition(CD_FLOAT("hud_pause_bt_x"), 640-CD_FLOAT("hud_pause_bt_y"));
	hudMenu->addChild(pauseButton);
	//按键包围盒
	Rect rect_but_left = but_left->getBoundingBox();
	Rect rect_but_right = but_right->getBoundingBox();
	Rect rect_but_A = but_A->getBoundingBox();
	Rect rect_but_B = but_B->getBoundingBox();
	//申请触摸监听
	EventListenerTouchAllAtOnce* touchEvent = EventListenerTouchAllAtOnce::create();
	//触摸按下
	touchEvent->onTouchesBegan = [=](const std::vector<Touch*>& touches, Event* event){
		for (auto &item : touches)       //遍历容器中的各个成员
		{
			auto touch = item;
			auto location = touch->getLocation();
			//LEFT
			if (rect_but_left.containsPoint(location))
			{
				hero->moveLeft();
			}
			//RIGHT
			else if (rect_but_right.containsPoint(location))
			{
				hero->moveRight();
			} 
			//A
			else if (rect_but_A.containsPoint(location))
			{
				hero->fire();
			} 
			//B
			else if (rect_but_B.containsPoint(location))
			{
				hero->jump();
			}
		}
	};
	//触摸时
	touchEvent->onTouchesMoved = [=](const std::vector<Touch*>& touches, Event* event){
		bool left = false;
		bool right = false;
		for (auto &item : touches)       //遍历容器中的各个成员
		{
			auto touch = item;			auto location = touch->getLocation();
			
			if (rect_but_left.containsPoint(location))
			{
				left = true;
				hero->moveLeft();
			}
			else if (rect_but_right.containsPoint(location))
			{
				right = true;
				hero->moveRight();
			}
		}
		setLeft(left);
		setRight(right);
		if (!left && !right)
		{
			hero->moveStop();
		}
	};
	//触摸抬起
	touchEvent->onTouchesEnded = [=](const std::vector<Touch*>& touches, Event* event){
		bool left = isLeft();
		bool right = isRight();
		for (auto &item : touches)       //遍历容器中的各个成员
		{
			auto touch = item;			auto location = touch->getLocation();

			if (rect_but_left.containsPoint(location))
			{
				left = false;
			}
			else if (rect_but_right.containsPoint(location))
			{
				right = false;
			}
		}
		setLeft(left);
		setRight(right);
		if (!left && !right)
		{
			hero->moveStop();
		}
	};
	//绑定事件
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(event, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchEvent, this);
	
	scheduleUpdate();
	
	return true;
}

void GameScene::update(float time)
{
	if (!pause)
		GameManager::getInstance()->step(time);
}

void GameScene::setLeft(bool left)
{
	_left = left;
}

bool GameScene::isLeft()
{
	return _left;
}

void GameScene::setRight(bool right)
{
	_right = right;
}

bool GameScene::isRight()
{
	return _right;
}

void GameScene::backButton(Ref* ref)
{
	settingLayer->setVisible(false);
	pause = false;
}

void GameScene::homeButton(Ref* ref)
{
	//跳转主页
	Scene* scene = TransitionCrossFade::create(0.3f, HelloWorld::createScene());
	Director::getInstance()->replaceScene(scene);
}

void GameScene::breakButton(Ref* ref)
{
	//自杀
	hero->dead();
}

void GameScene::pauseButton(Ref* ref)
{
	pause = true;
	settingLayer->setVisible(true);
}

int GameScene::level = 0;
