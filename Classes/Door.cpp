#include "Door.h"
#include "StaticData.h"
#include "FinishScene.h"
#include "GameManager.h"
#include "Hero.h"

USING_NS_CC;

bool Door::init(float x, float y, float width, float height)
{
	if (!GameObject::init(x, y, width, height))
	{
		return false;
	}
	this->setTexture(SD_CHARS("door_path_texture"));
	this->getBody()->SetType(b2_staticBody);
	this->setType(TYPE_PRIZE);	//相当于战利品
	this->setMask(TYPE_HERO);

	return true;
}

void Door::BeginContact(GameObject* other, b2Contact* contact)
{
	contact->SetEnabled(false);
	//只要与英雄碰撞就会胜利
	if (other->getType() == TYPE_HERO)
	{
		if (GameManager::getInstance()->hero->isDie())
			return;
		auto finish = FinishScene::createScene(GameManager::getInstance()->hero->getCoin());
		Director::getInstance()->replaceScene(finish);
	}
}

