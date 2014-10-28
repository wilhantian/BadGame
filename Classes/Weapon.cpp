#include "Weapon.h"
#include "Aware.h"
#include "GameManager.h"
#include "StaticData.h"
USING_NS_CC;

bool Weapon::init(Aware* object)
{
	//子弹发射时的位置、碰撞大小
	if(!LifeObject::init(object->getPositionX(), object->getPositionY(), SD_FLOAT("weapon_float_width"), SD_FLOAT("weapon_float_height")))
	{
		return false;
	}
	startTag = true;
	//基本纹理
	this->setTexture(SD_STRING("weapon_path_texture"));
	//设置方向
	dir = object->getDir();
	//保存object
	this->object = object;

	this->getBody()->SetBullet(true);
	this->getBody()->SetType(b2_dynamicBody);

	this->setHp(SD_INT("weapon_int_hp"));		//设置血量
	this->setAtk(SD_INT("weapon_int_atk"));		//设置攻击力

	this->setType(TYPE_WEAPON);
	//会和谁发生碰撞
	if(object->getType() == TYPE_HERO)
	{ //如果子弹属于英雄
		this->setMask(
			TYPE_ANIMAL |
			TYPE_COIN |
			TYPE_BRICK |
			TYPE_ARTICLE |
			TYPE_MONSTER
		);
	}
	else{
	  //如果子弹不属于英雄
		this->setMask(
			TYPE_ANIMAL |
			TYPE_COIN |
			TYPE_BRICK |
			TYPE_ARTICLE |
			TYPE_HERO
			);
	}

	//设置速度并发射
	this->setSpeed(SD_FLOAT("weapon_float_speed"));

	return true;
}

void Weapon::setSpeed(float speed)
{
	this->speed = abs(speed);
	if(dir == DIR_LEFT)
		this->speed = -speed;
	this->getBody()->SetLinearVelocity(b2Vec2(getSpeed(), 0));
}

int Weapon::getSpeed()
{
	return speed;
}

void Weapon::update(float ft)
{
	LifeObject::update(ft);
	//初始标识初始化
	if (startTag)
	{
		startTag = false;
		startY = this->getPositionY();
	}
	//固定Y数值
	this->setPhysicsSpritePosition(this->getPositionX(), startY);

	Size size = Director::getInstance()->getVisibleSize();
	//如果超出屏幕 那么销毁子弹
	if(this->getPositionX() > size.width+100
		|| this->getPositionX() < -100)
	{
		this->autoRemovePhysicsSprite();
	}
	else if(this->getPositionY() > size.height+100
		|| this->getPositionY() < -100)
	{
		this->autoRemovePhysicsSprite();
	}
}

void Weapon::dead()
{
	LifeObject::dead();
	//重新设置碰撞
	setMask(0);
	this->getBody()->SetLinearVelocity(b2Vec2(0,0));
	Animate* animate = GameManager::getInstance()->getAnimate(SD_CHARS("weapon_animate_dead"), SD_FLOAT("weapon_float_dead_speed"));
	Action* action = Sequence::createWithTwoActions(animate, CallFunc::create(CC_CALLBACK_0(Weapon::ended, this)));
	this->runAction(action);
}

void Weapon::ended()
{
	LifeObject::ended();
	this->autoRemovePhysicsSprite();
}

void Weapon::PreSolve(GameObject* othera, b2Contact* contact, const b2Manifold* oldManifold)
{
	dead();

	if(othera->getType() == TYPE_ANIMAL
		||othera->getType() == TYPE_HERO
		||othera->getType() == TYPE_MONSTER
		||othera->getType() == TYPE_ARTICLE)
	{
		LifeObject* liftObject = (LifeObject*)othera;
		liftObject->setHp(liftObject->getHp() - atk);
		contact->SetEnabled(false);
	}
}
