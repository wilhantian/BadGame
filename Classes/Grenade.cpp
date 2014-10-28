#include "Grenade.h"
#include "GameManager.h"
#include "Fragment.h"
#include "StaticData.h"

USING_NS_CC;

bool Grenade::init(Aware* aware)
{
	//位置和碰撞大小
	if (!Aware::init(aware->getPositionX(), aware->getPositionY(), SD_FLOAT("grenade_float_width"), SD_FLOAT("grenade_float_height")))
		return false;

	countTime = 0;
	bombTime = SD_FLOAT("grenade_float_bombtime");	//几秒后引燃爆炸

	this->setTexture(SD_STRING("grenade_path_texture"));
	this->getBody()->SetFixedRotation(false);
	this->getBody()->SetBullet(true);
	this->getFixture()->SetRestitution(SD_FLOAT("grenade_float_restitution"));	//弹力
	this->getFixture()->SetFriction(SD_FLOAT("grenade_float_friction"));	//摩擦力
	
	b2MassData mass;
	mass.mass = SD_FLOAT("grenade_float_mass");
	mass.I = SD_FLOAT("grenade_float_i");
	mass.center = this->getBody()->GetLocalCenter();
	this->getBody()->SetMassData(&mass);

	this->setType(TYPE_WEAPON);
	if(aware->getType() == TYPE_HERO)
		this->setMask(
		TYPE_WEAPON|
		TYPE_BRICK|
		TYPE_MONSTER|
		TYPE_ARTICLE);
	else
		this->setMask(
		TYPE_BRICK|
		TYPE_HERO|
		TYPE_ARTICLE);

	DIR dirr = aware->getDir();
	this->setDir(dirr);

	//扔出手雷
	if(this->getDir() == DIR_LEFT)
	{
		this->getBody()->SetAngularVelocity(-SD_FLOAT("grenade_float_velocity_a"));
		this->getBody()->SetLinearVelocity(b2Vec2(-SD_FLOAT("grenade_float_velocity_x"), SD_FLOAT("grenade_float_velocity_y")));
	}
	else
	{
		this->getBody()->SetAngularVelocity(SD_FLOAT("grenade_float_velocity_a"));
		this->getBody()->SetLinearVelocity(b2Vec2(SD_FLOAT("grenade_float_velocity_x"), SD_FLOAT("grenade_float_velocity_y")));
	}

	return true;
}

void Grenade::dead()
{
	Aware::dead();
	this->getBody()->SetType(b2_kinematicBody);
	//播放爆炸动画
	Animate* animate = GameManager::getInstance()->getAnimate(SD_CHARS("grenade_animate_dead"), SD_FLOAT("grenade_float_dead_speed"));
	Sequence* action = Sequence::createWithTwoActions(
		animate,
		CallFunc::create(CC_CALLBACK_0(Grenade::ended, this)));
	this->stopAllActions();
	this->runAction(action);

	//释放碎片
	float l = 15;
	//todo
	for (int i = 0; i < 18; i++)
	{
		float y = l * cos(i * 9);
		float x = sqrt((l*l) - (y*y));
		Fragment* fra = Fragment::create(this->getPositionX(), this->getPositionY(), b2Vec2(x, y), SD_FLOAT("grenade_float_fragment_size"), false);
		GameManager::getInstance()->heroLayer->addChild(fra);
		Fragment* fra2 = Fragment::create(this->getPositionX(), this->getPositionY(), b2Vec2(-x, y), SD_FLOAT("grenade_float_fragment_size"), false);
		GameManager::getInstance()->heroLayer->addChild(fra2);
	}
}

void Grenade::ended()
{
	Aware::ended();
	this->autoRemovePhysicsSprite();
}

void Grenade::update(float ft)
{
	Aware::update(ft);
	countTime = countTime + ft;
	if (!isDie() && countTime >= bombTime)	//N秒后开始引燃手榴弹
	{
		dead();
	}
}
