#include "JINTools.h"
JINTools::JINTools(){}
JINTools::~JINTools(){}

void JINTools::showAdScreen()
{
	#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	JniMethodInfo adScreenInfo;
	bool isHave = JniHelper::getStaticMethodInfo(adScreenInfo,"org/cocos2dx/cpp/AppActivity","showAdScreen","()V");
	if (!isHave) {
		  CCLog("jni:showAdScreen false");
	}else{
		adScreenInfo.env->CallStaticVoidMethod(adScreenInfo.classID, adScreenInfo.methodID);
	}
	#endif
}

void JINTools::closeAdScreen()
{

}

void JINTools::umengUpdate()
{
	#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	JniMethodInfo updateInfo;
	bool isHave = JniHelper::getStaticMethodInfo(updateInfo,"org/cocos2dx/cpp/AppActivity","umengUpdate","()V");
	if (!isHave) {
		  CCLog("jni:updateInfo false");
	}else{
		updateInfo.env->CallStaticVoidMethod(updateInfo.classID, updateInfo.methodID);
	}
	#endif
}

void JINTools::openFeedback()
{
	#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	JniMethodInfo openFeedbackInfo;
	bool isHave = JniHelper::getStaticMethodInfo(openFeedbackInfo,"org/cocos2dx/cpp/AppActivity","openFeedback","()V");
	if (!isHave) {
		  CCLog("jni:openFeedbackInfo false");
	}else{
		openFeedbackInfo.env->CallStaticVoidMethod(openFeedbackInfo.classID, openFeedbackInfo.methodID);
	}
	#endif
}
