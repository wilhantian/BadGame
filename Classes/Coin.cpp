#include "Coin.h"
#include "GameManager.h"
#include "Hero.h"
#include "StaticData.h"

USING_NS_CC;

bool Coin::init(float x, float y, float width, float height)
{
	if(!LifeObject::init(x, y, width, height))
	{
		return false;
	}
	coin = SD_INT("coin_int_coin");
	//ÉèÖÃÅö×²
	this->setType(TYPE_COIN);
	this->setMask(
		TYPE_BRICK |
		TYPE_HERO  |
		TYPE_COIN
		);
	//ÉèÖÃÎÆÀí
	this->setTexture(SD_CHARS("coin_path_texture"));
	return true;
}

void Coin::dead()
{
	LifeObject::dead();
	//²»ÈÃÆäÅö×²
	this->setMask(TYPE_BRICK);
	ended();
}

void Coin::ended()
{
	LifeObject::ended();
	this->autoRemovePhysicsSprite();
}

void Coin::PreSolve(GameObject* other, b2Contact* contact, const b2Manifold* oldManifold)
{
	if(other->getType() == TYPE_HERO && !isDie())
	{
		dead();//setHp(0);
		Hero* hero = (Hero*)other;
		hero->setCoin(hero->getCoin() + coin);
		contact->SetEnabled(false);
	}
}
