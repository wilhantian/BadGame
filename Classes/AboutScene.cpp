#include "AboutScene.h"
#include "TextData.h"

USING_NS_CC;

Scene* AboutScene::createScene()
{
	Scene* scene = Scene::create();
	Layer* layer = AboutScene::create();
	scene->addChild(layer);
	return scene;
}

bool AboutScene::init()
{
	if (!LayerColor::initWithColor(Color4B(137, 201, 151, 255)))
	{
		return false;
	}
	Size size(960, 640);
	Sprite* bk = Sprite::create("UI/ABOUT/about.png");
	bk->setPosition(size.width / 2, size.height / 2);
	this->addChild(bk);
// 	//Bad Game
// 	TTFConfig ttfConfig("fonts/font.ttf", 40);
// 	auto bad_game_en = Label::createWithTTF(ttfConfig, TD_STRING("bad_game_en"));
// 	bad_game_en->setTextColor(Color4B::WHITE);
// 	bad_game_en->setPosition(size.width / 2, TD_FLOAT("bad_game_en_y"));
// 	this->addChild(bad_game_en);
// 	//ÀÃÓÎÏ·
// 	ttfConfig.fontSize = 27;
// 	auto bad_game_ch = Label::createWithTTF(ttfConfig, TD_STRING("bad_game_ch"));
// 	bad_game_ch->setPosition(size.width / 2, TD_FLOAT("bad_game_ch_y"));
// 	this->addChild(bad_game_ch);
// 	//by
// 	ttfConfig.fontSize = 25;
// 	auto make_by_en = Label::createWithTTF(ttfConfig, TD_STRING("make_by_en"));
// 	make_by_en->setPosition(size.width / 2, TD_FLOAT("make_by_en_y"));
// 	this->addChild(make_by_en);
// 	//twitter
// 	ttfConfig.fontSize = 20;
// 	auto twitter = Label::createWithTTF(ttfConfig, TD_STRING("twitter"));
// 	twitter->setPosition(size.width / 2, TD_FLOAT("twitter_y"));
// 	this->addChild(twitter);
// 	//weibo
// 	ttfConfig.fontSize = 20;
// 	auto weibo = Label::createWithTTF(ttfConfig, TD_STRING("weibo"));
// 	weibo->setPosition(size.width / 2, TD_FLOAT("weibo_y"));
// 	this->addChild(weibo);
// 	//email
// 	ttfConfig.fontSize = 20;
// 	auto email = Label::createWithTTF(ttfConfig, TD_STRING("email"));
// 	email->setPosition(size.width / 2, TD_FLOAT("email_y"));
// 	this->addChild(email);
// 	//web_size
// 	ttfConfig.fontSize = 20;
// 	auto web_size = Label::createWithTTF(ttfConfig, TD_STRING("web_size"));
// 	web_size->setPosition(size.width / 2, TD_FLOAT("web_size_y"));
// 	this->addChild(web_size);
// 	//some_word_ch
// 	ttfConfig.fontSize = 20;
// 	auto some_word_ch = Label::createWithTTF(ttfConfig, TD_STRING("some_word_ch"));
// 	some_word_ch->setPosition(size.width / 2, TD_FLOAT("some_word_ch_y"));
// 	this->addChild(some_word_ch);

	auto event = EventListenerTouchOneByOne::create();
	event->onTouchBegan = [](Touch* t, Event* e){
		Director::getInstance()->popScene();
		return true;
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(event, this);

	return true;
}
