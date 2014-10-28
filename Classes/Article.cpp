#include "Article.h"
#include "GameManager.h"
#include "StaticData.h"
#include "Coin.h"

USING_NS_CC;

void Article::initParam()
{
	int randInt = CCRANDOM_0_1() * 4;
	//随机纹理
	if (randInt == 0)
		this->setTexture(SD_STRING("article_path_texture"));
	else
		this->setTexture(SD_STRING("article_path_texture_1")); 

	this->getBody()->SetSleepingAllowed(true);	//允许物理休眠

	this->getFixture()->SetRestitution(SD_FLOAT("article_float_restitution"));	//弹力
	this->getFixture()->SetFriction(SD_FLOAT("article_float_friction"));	//摩擦力

	int boxWidth = this->getBodyBoundingBoxWidth();
	int boxHeight = this->getBodyBoundingBoxHeight();

	b2MassData mass;
	mass.mass = SD_FLOAT("article_float_mass");
	mass.I = SD_FLOAT("article_float_i");
	//todo
	mass.center = this->getBody()->GetLocalCenter();

	this->getBody()->SetMassData(&mass);

	this->setType(TYPE_ARTICLE);
	this->setMask(	//碰撞类型
		TYPE_ARTICLE |
		TYPE_BRICK |
		TYPE_HERO |
		TYPE_MONSTER |
		TYPE_WEAPON
		);
	this->setHp(SD_INT("article_int_hp"));

}

bool Article::init(float x, float y, float width, float height)
{
	if (!LifeObject::init(x, y, width, height))
	{
		return false;
	}
	initParam();
	return true;
}

bool Article::init(float x, float y, b2Vec2* points, int count)
{
	if (!LifeObject::init(x, y, points, count))
	{
		return false;
	}
	initParam();
	return true;

}

void Article::dead()
{
	LifeObject::dead();
	this->getBody()->SetLinearVelocity(b2Vec2(0,0));
	this->setMask(TYPE_BRICK);
	Animate* animate = GameManager::getInstance()->getAnimate(SD_CHARS("article_animate_dead"), SD_FLOAT("article_float_dead_speed"));
	Sequence* action = Sequence::createWithTwoActions(
		animate,
		CallFunc::create(CC_CALLBACK_0(Article::ended, this)));
	this->runAction(action);
	//有一定几率给金币
	float random = CCRANDOM_0_1() * 100;
	if (random < SD_FLOAT("article_float_bomb_coin_odds"))	//几率
	{
		Coin* coin = Coin::create(this->getPosition().x, this->getPosition().y, SD_FLOAT("coin_float_width"), SD_FLOAT("coin_float_height"));
		GameManager::getInstance()->thingLayer->addChild(coin);
		coin->getBody()->SetLinearVelocity(b2Vec2(0, 4));
	}
}

void Article::ended()
{
	LifeObject::ended();
	this->autoRemovePhysicsSprite();
}
