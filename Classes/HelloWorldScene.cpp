#include "HelloWorldScene.h"
#include "GameScene.h"
#include "ConfigData.h"
#include "AboutScene.h"
#include "LevelScene.h"
#include "JINTools.h"

// 引入相关的头文件
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
//友盟统计头
#include "MobClickCpp.h"
#include "Cocos2dx/Common/CCUMSocialSDK.h"
#include "Cocos2dx/ShareButton/UMShareButton.h"
// 使用友盟命令空间
USING_NS_UM_SOCIAL;
#endif

USING_NS_CC;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
/*
 * 分享回调, 该回调不是某个类的成员函数， 而是一个普通的函数, 具体使用参考HelloWorldScene的例子
* @param platform 要分享到的目标平台
 * @param stCode 返回码, 200代表分享成功, 100代表开始分享
 * @param errorMsg 分享失败时的错误信息,android平台没有错误信息
 */
void shareCallback(int platform, int stCode, string& errorMsg)
{
    if ( stCode == 100 ) 
    {
        CCLog("#### HelloWorld startshare");
    }
    else if ( stCode == 200 ) 
    {
        CCLog("#### HelloWorld finishshare");
    }
    else 
    {
        CCLog("#### HelloWorld erroshare");
    }

    CCLog("platform num is : %d.", platform);
}
#endif

Scene* HelloWorld::createScene()
{
    auto scene = Scene::create();
    auto layer = HelloWorld::create();
    scene->addChild(layer);

	return scene;
}

bool HelloWorld::init()
{
    if ( !LayerColor::initWithColor(Color4B(0,255,255,255)) )
    {
        return false;
    }
	Size size = Size(960, 640);
	//背景
	Sprite* background = Sprite::create("UI/START/background.png");
	background->setPosition(size.width/2, size.height/2);
	this->addChild(background);
	//左侧边栏
	Sprite* left = Sprite::create("UI/START/START_UI_DOWN_0004_LeftFoot.png");
	left->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	left->setPosition(0, 0);
	this->addChild(left);

	float leftFootWeight = left->getContentSize().width;
	float leftFootHeight = left->getContentSize().height;
	//LOGO
	Sprite* logo = Sprite::create("UI/START/START_UI_UP_0005_BAD-GAME.png");
	logo->setPosition((size.width - leftFootWeight) / 2 + leftFootWeight, CD_FLOAT("start_scene_logo_y"));
	this->addChild(logo);
	//版本号
	TTFConfig ttfConfig("fonts/font.ttf", 16);
	auto number = Label::createWithTTF(ttfConfig, CD_STRING("number"));
	number->setTextColor(Color4B(0, 0, 0, 150));
	number->setPosition(size.width - 460, 20);
	this->addChild(number);

	Menu* menu = Menu::create();
	menu->setPosition(0, 0);
	this->addChild(menu);
	//设置按钮
	MenuItemImage* buttonSetting = MenuItemImage::create("UI/START/START_UI_UP_0000_setting.png", "UI/START/START_UI_DOWN_0000_setting.png", "UI/START_UI_DOWN_0000_setting.png", CC_CALLBACK_1(HelloWorld::settingCallBack, this));
	buttonSetting->setPosition(leftFootWeight / 2, CD_FLOAT("start_scene_setting_button_y"));
	menu->addChild(buttonSetting);
	//关于按钮
	MenuItemImage* buttonAbout = MenuItemImage::create("UI/START/START_UI_UP_0003__.png", "UI/START/START_UI_DOWN_0003__.png", "UI/START_UI_UP_0003__.png", CC_CALLBACK_1(HelloWorld::aboutCallBack, this));
	buttonAbout->setPosition(leftFootWeight / 2, CD_FLOAT("start_scene_about_button_y"));
	menu->addChild(buttonAbout);
	//更多按钮
//	MenuItemImage* buttonMore = MenuItemImage::create("UI/START/START_UI_UP_0002_....png", "UI/START/START_UI_DOWN_0002_....png", "UI/START_UI_UP_0003__.png", CC_CALLBACK_1(HelloWorld::settingCallBack, this));
//	buttonMore->setPosition(leftFootWeight / 2, CD_FLOAT("start_scene_more_button_y"));
//	menu->addChild(buttonMore);
	//开始按钮
	MenuItemImage* buttonStart = MenuItemImage::create("UI/START/START_UI_UP_0006_StartButton.png", "UI/START/START_UI_DOWN_0006_StartButton.png", "UI/START_UI_UP_0003__.png", CC_CALLBACK_1(HelloWorld::startCallBack, this));
	buttonStart->setPosition((size.width - leftFootWeight) / 2 + leftFootWeight, CD_FLOAT("start_scene_start_button_y"));
	menu->addChild(buttonStart);
	//退出按钮
	MenuItemImage* exitStart = MenuItemImage::create("UI/START/exit1.png", "UI/START/exit2.png", "UI/exit2.png", CC_CALLBACK_1(HelloWorld::exitCallBack, this));
	exitStart->setPosition(CD_FLOAT("start_scene_exit_button_x"), CD_FLOAT("start_scene_exit_button_y"));
	menu->addChild(exitStart);
	//反馈按钮
	MenuItemImage* buttonMsg = MenuItemImage::create("UI/START/msg1.png", "UI/START/msg2.png", "UI/msg2.png", CC_CALLBACK_1(HelloWorld::msgCallBack, this));
	buttonMsg->setPosition(CD_FLOAT("start_scene_msg_button_x"), CD_FLOAT("start_scene_msg_button_y"));
	menu->addChild(buttonMsg);
	//todo logo动态动画
	this->schedule(schedule_selector(HelloWorld::dyncLogo), 3.5f);
    
	//测试功能 显示FPS
	/*
	EventListenerTouchOneByOne* event = EventListenerTouchOneByOne::create();
	event->onTouchBegan = [=](Touch* touch, Event* event){
		if (logo->getBoundingBox().containsPoint(touch->getLocation()))
		{
			// 如果在LOGO处发生触摸时间，那么显示FPS
			Director::getInstance()->setDisplayStats(!Director::getInstance()->isDisplayStats());
		}
		return true;
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(event, this);
	*/

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	// 创建分享按钮, 参数1为按钮正常情况下的图片, 参数2为按钮选中时的图片,参数3为友盟appkey, 参数4为分享回调
    UMShareButton *shareButton = UMShareButton::create("UI/START/share.png", "UI/START/share.png", "542752bcfd98c578990126ac", share_selector(shareCallback)) ;
	// 显示在友盟分享面板上的平台
    vector<int>* platforms = new vector<int>();
    platforms->push_back(SINA);
//    platforms->push_back(RENREN) ;
    platforms->push_back(DOUBAN) ;
    platforms->push_back(WEIXIN_CIRCLE) ;
    platforms->push_back(WEIXIN);
    platforms->push_back(QZONE) ;
    platforms->push_back(QQ) ;
    // 设置友盟分享面板上显示的平台
    shareButton->setPlatforms(platforms);
    // 设置文本分享内容
    shareButton->setShareContent(CD_CHARS("share_content")) ;
    // 设置要分享的图片, 图片支持本地图片和url图片, 但是url图片必须以http://或者https://开头
    shareButton->setShareImage(CD_CHARS("share_picture")) ;
    // 设置按钮的位置
    shareButton->setPosition(leftFootWeight / 2, CD_FLOAT("start_scene_more_button_y"));
    // 然后开发者需要将该按钮添加到游戏场景中
	menu->addChild(shareButton);
    // ********************** 设置平台信息 ***************************
    CCUMSocialSDK *sdk = shareButton->getSocialSDK();
    sdk->setWeiXinAppId("wx608e3343f4047772");
    // sdk->setQQAppIdAndAppKey("设置QQ的app id", "appkey");
    sdk->setQQAppIdAndAppKey("1103269146", "hLU6S75uuvXx4gyD");
    // 设置用户点击一条图文分享时用户跳转到的目标页面, 一般为app主页或者下载页面
    sdk->setTargetUrl(CD_CHARS("share_websize"));
    //     // 打开或者关闭log
    sdk->setLogEnable(false) ;
    // **********************   END ***************************
#endif

    return true;
}

void HelloWorld::aboutCallBack(cocos2d::Ref* ref)
{
	auto reScene = TransitionCrossFade::create(0.3f, AboutScene::createScene());
	Director::getInstance()->pushScene(reScene);
}

void HelloWorld::settingCallBack(cocos2d::Ref* ref)
{
	log("settingCallBack");
	MessageBox("The function to be realized.\nWill be updated in the next version.", "Sorry");
}

void HelloWorld::startCallBack(cocos2d::Ref* ref)
{	
	auto reScene = TransitionCrossFade::create(0.3f, LevelScene::createScene());
	Director::getInstance()->replaceScene(reScene);
}

void HelloWorld::exitCallBack(cocos2d::Ref* ref)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	//友盟统计释放资源
	umeng::MobClickCpp::end();
#endif

	Director::getInstance()->end();
}

void HelloWorld::msgCallBack(cocos2d::Ref* ref)
{
	JINTools::openFeedback();
}

void HelloWorld::dyncLogo(float time)
{
	Size size(960, 640);
	float leftFootWeight = 194;
	Sprite* logo = Sprite::create("UI/START/START_UI_DOWN_0005_BAD-GAME.png");
	logo->setPosition((size.width - leftFootWeight) / 2 + leftFootWeight, CD_FLOAT("start_scene_logo_y"));
	this->addChild(logo);

	Sequence* action = Sequence::createWithTwoActions(cocos2d::DelayTime::create(0.3), CallFuncN::create(CC_CALLBACK_1(HelloWorld::deleteNode, this)));
	logo->runAction(action);
}

void HelloWorld::deleteNode(cocos2d::Node* sender)
{
	sender->removeFromParent();
}



