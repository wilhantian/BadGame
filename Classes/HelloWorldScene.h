#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "GameManager.h"
#include "GameObject.h"
#include "LifeObject.h"
#include "Hero.h"
#include "Brick.h"

class HelloWorld : public cocos2d::LayerColor
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld); 

	void aboutCallBack(cocos2d::Ref* ref);
	void settingCallBack(cocos2d::Ref* ref);
	void startCallBack(cocos2d::Ref* ref);
	void exitCallBack(cocos2d::Ref* ref);
	void msgCallBack(cocos2d::Ref* ref);


	void dyncLogo(float time);
	void deleteNode(cocos2d::Node* sender);
};


#endif // __HELLOWORLD_SCENE_H__
