#include "GameManager.h"
#include "Hero.h"
#include "StaticData.h"
USING_NS_CC;

GameManager* GameManager::gameManager = nullptr;

GameManager* GameManager::getInstance()
{
	if(!gameManager)
	{
		gameManager = new GameManager();
		gameManager->retain();	//计数+1
	}
	return gameManager;
}

void GameManager::initPhysicsWorld(float gravity)
{
	world = new b2World(b2Vec2(0, -gravity));
	world->SetContactListener(this);
	//屏幕位置
	sceneX = Director::getInstance()->getVisibleSize().width / 2;
	sceneY = Director::getInstance()->getVisibleSize().height / 2;
}

GameManager::GameManager()
{
	hero = nullptr;
	//初始化资源
	initRes();
	//初始化物理世界
	initPhysicsWorld(GRAVITY);
	//level = 0;
}

GameManager::~GameManager()
{
	//CC_SAFE_RELEASE(gameManager);
	CC_SAFE_DELETE(world);
}

b2World* GameManager::getWorld()
{
	return world;
}

void GameManager::step(float time)
{
	//--英雄上次位置
	Vec2 heroLastPostion = hero->getPosition();

	world->Step(time, 8, 3);
	//更新精灵位置、角度
	for(b2Body* body=world->GetBodyList(); body; body=body->GetNext())
	{
		Sprite* sprite = (Sprite*)body->GetUserData();
		if(sprite == NULL)
			continue;
		sprite->setPosition(body->GetPosition().x*PTM_RATIO, body->GetPosition().y*PTM_RATIO);
		sprite->setRotation(-1*CC_RADIANS_TO_DEGREES(body->GetAngle()));	//设置角度
	}

	//释放销毁缓冲栈中的物理精灵
	for(auto it  = _deleteSprites.begin(); it != _deleteSprites.end(); )  
	{  
		(*it)->removePhysicsSprite();
		it = _deleteSprites.erase(it);  
	}

	//--英雄当前位置
	Vec2 heroNowPostion = hero->getPosition();
	sceneX = sceneX + heroLastPostion.x - heroNowPostion.x;
	sceneY = sceneY + heroLastPostion.y - heroNowPostion.y;
	GameManager::getInstance()->gameLayer->setPosition(sceneX, sceneY);
}

void GameManager::pushDeleteSprite(PhysicsSprite* sprite)
{
	_deleteSprites.pushBack(sprite);
}

void GameManager::BeginContact(b2Contact* contact)
{
	GameObject* a = (GameObject*)contact->GetFixtureA()->GetBody()->GetUserData();
	GameObject* b = (GameObject*)contact->GetFixtureB()->GetBody()->GetUserData();

	a->BeginContact(b, contact);
	b->BeginContact(a, contact);
}

void GameManager::EndContact(b2Contact* contact)
{
	GameObject* a = (GameObject*)contact->GetFixtureA()->GetBody()->GetUserData();
	GameObject* b = (GameObject*)contact->GetFixtureB()->GetBody()->GetUserData();

	a->EndContact(b, contact);
	b->EndContact(a, contact);
}

void GameManager::PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
{
	GameObject* a = (GameObject*)contact->GetFixtureA()->GetBody()->GetUserData();
	GameObject* b = (GameObject*)contact->GetFixtureB()->GetBody()->GetUserData();

	a->PreSolve(b, contact, oldManifold);
	b->PreSolve(a, contact, oldManifold);
}

void GameManager::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse)
{
	GameObject* a = (GameObject*)contact->GetFixtureA()->GetBody()->GetUserData();
	GameObject* b = (GameObject*)contact->GetFixtureB()->GetBody()->GetUserData();

	a->PostSolve(b, contact, impulse);
	b->PostSolve(a, contact, impulse);
}

/*初始化资源*/
void GameManager::initRes()
{
	std::string path = FileUtils::getInstance()->fullPathForFilename("load.xml");
	ValueMap vm = FileUtils::getInstance()->getValueMapFromFile(path);
	for (int i = 0; i < vm.size(); i++)
	{
		char buf[12];
		sprintf(buf, "%d", i+1);
		std::string s = vm.at(buf).asString();
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile(s);
	}
	vm.clear();
}

Animation* GameManager::getAnimation(const char* src, float delay, unsigned int loops)
{
	Vector<SpriteFrame*> frames;

	char _src[30];
	for(int i=0; i<10000; i++)
	{
		sprintf(_src, "%s%04d", src, i);
		SpriteFrame* sf = SpriteFrameCache::getInstance()->getSpriteFrameByName(_src);
		if(sf == nullptr)
		{
			break;
		}
		frames.pushBack(sf);
	}
	return Animation::createWithSpriteFrames(frames, delay, loops);
}

cocos2d::Animate* GameManager::getAnimate(const char* src, float delay /*= 0.0f*/, unsigned int loops /*= 1U*/)
{
	Animation* animation = getAnimation(src, delay, loops);
	return Animate::create(animation);
}

void GameManager::destroyInstance()
{
	CC_SAFE_DELETE(gameManager);
}

// void GameManager::setLevel(int level)
// {
// 	GameManager::level = level;
// }
// 
// int GameManager::getLevel()
// {
// 	return level;
// }
