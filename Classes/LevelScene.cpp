#include "LevelScene.h"
#include "ConfigData.h"
#include "HelloWorldScene.h"
#include "GameScene.h"
#include "DynamicData.h"
#include "JINTools.h"

USING_NS_CC;

cocos2d::Scene* LevelScene::createScene()
{
	Scene* scene = Scene::create();
	Layer* layer = LevelScene::create();
	scene->addChild(layer);

	//todo 销毁GameManager
	GameManager::destroyInstance();

	return scene;
}

bool LevelScene::init()
{
	if (!LayerColor::initWithColor(Color4B::WHITE))
	{
		return false;
	}

	Size size(960, 640);
	
	//背景
	Sprite* bk = Sprite::create("UI/LEVEL/LEVEL_UI_UP_0000s_0002_BK.png");
	bk->setPosition(size.width / 2, size.height / 2);
	this->addChild(bk);
	//LOGO
	Sprite* logo = Sprite::create("UI/LEVEL/LEVEL_UI_UP_0000s_0001_LOGO.png");
	logo->setPosition(size.width / 2, CD_FLOAT("level_scene_logo_y"));
	this->addChild(logo);
	
	//菜单
	Menu* menu = Menu::create();
	menu->setPosition(0, 0);
	this->addChild(menu);

	//返回按钮
	MenuItemImage* buttonBack = MenuItemImage::create("UI/LEVEL/LEVEL_UI_UP_0000s_0000_BACK_BUTTON.png", "UI/LEVEL/LEVEL_UI_DOWN_0000s_0000_BACK_BUTTON.png", "UI/LEVEL/LEVEL_UI_UP_0000s_0000_BACK_BUTTON.png", CC_CALLBACK_1(LevelScene::backCallBack, this));
	buttonBack->setPosition(CD_FLOAT("level_scene_back_button_x"), CD_FLOAT("level_scene_back_button_y"));
	menu->addChild(buttonBack);
	//读取关卡
	int canLevel = DynamicData::getInstance()->getLevel();
	log("canLevel -- %d", canLevel);
	//关卡按钮
	for (int i = 1; i <= 8; i++)
	{
		char c_buf_x[128];
		sprintf(c_buf_x, "level_scene_button_%d_x", i);
		char c_buf_y[128];
		sprintf(c_buf_y, "level_scene_button_%d_y", i);
		char but_name_up[32];
		sprintf(but_name_up, "UI/LEVEL/button_%d_up.png", i);
		char but_name_down[32];
		sprintf(but_name_down, "UI/LEVEL/button_%d_down.png", i);

		MenuItemImage* bm = MenuItemImage::create(but_name_up, but_name_down, "UI/LEVEL/button_not_level.png", CC_CALLBACK_1(LevelScene::levelsCallBack, this));
		bm->setPosition(CD_FLOAT(c_buf_x), CD_FLOAT(c_buf_y));
		bm->setTag(i);
		if (i > canLevel)
			bm->setEnabled(false);
		menu->addChild(bm);
	}
	//检测更新
	JINTools::umengUpdate();
	return true;
}

void LevelScene::backCallBack(cocos2d::Ref* ref)
{
	auto reScene = TransitionCrossFade::create(0.3f, HelloWorld::createScene());
	Director::getInstance()->replaceScene(reScene);
}

void LevelScene::levelsCallBack(cocos2d::Ref* ref)
{
	int level = ((MenuItemImage*)ref)->getTag();
	//log("level = %d", level);

	auto reScene = TransitionFade::create(1.0f, GameScene::createScene(level), Color3B(0, 0, 0));
	Director::getInstance()->replaceScene(reScene);
}
