/**
 * FileName : CCUMScoialSDK.cpp
 * Author   : hehonghui
 * Company  : umeng.com
 * 该类为友盟社会化组件的Cocos2d-x版本，在友盟社会化组件Android、iOS原生SDK上进行适配，支持打开分享面板分享、直接分享、授权某平台、删除某平台授权、判断某平台是否授权这几个核心功能。
 *
 * Android 平台实现的代码参考UmengSocial/Android目录下的实现, IOS平台的参考UmengSocial/IOS目录下的实现。
 *
 */

#include "CCUMSocialSDK.h"
#include <vector>

#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS

#include "UmSocialControllerIOS.h"

#elif CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID

#include "Cocos2dx/Android/CCUMSocialController.h"

#endif

USING_NS_CC;
using namespace std;
// 使用友盟命令空间 
USING_NS_UM_SOCIAL;

CCUMSocialSDK* CCUMSocialSDK::_instance = NULL;

/*
 * 构造函数, 必须传递友盟appKey
 * @param appKey 友盟appKey
 */
CCUMSocialSDK::CCUMSocialSDK(const char* appKey) :
		mPlatforms(new vector<int>()), _wrapperType("Cocos2d-x"), _wrapperVersion(
				"1.0") {
	initSDK();
	setAppKey(appKey);
}

/*
 * 初始化sdk
 */
void CCUMSocialSDK::initSDK() {
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
	// 初始化cocos2d-x平台
	initCocos2dxSDKFromJni(_wrapperType, _wrapperVersion);

#elif CC_TARGET_PLATFORM == CC_PLATFORM_IOS

	UmSocialControllerIOS::initCocos2dxSDK(_wrapperType, _wrapperVersion);

#endif
}

/*
 * 创建CCUMSocialSDK对象, 单例模式
 * @param appKey 友盟app key
 */

CCUMSocialSDK* CCUMSocialSDK::create(const char* appKey) {

	if (_instance == NULL) {
		_instance = new CCUMSocialSDK(appKey);
	} else if (appKey != NULL) {
		_instance->setAppKey(appKey);
	}
	return _instance;
}

/*
 * 设置友盟app key
 * @param appKey 友盟app key
 */
void CCUMSocialSDK::setAppKey(const char* appkey) {
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
	if (appkey == NULL) {
		CCLog("CCUMSocialSDK::setAppKey, key == null");
	}
	// 授权某平台
	setUmengAppkey(appkey);

#elif CC_TARGET_PLATFORM == CC_PLATFORM_IOS

	UmSocialControllerIOS::setAppKey(appkey);

#endif
}

/*
 * 设置SDK中的所有平台
 *@param    platforms SDK中包含的所有平台
 */
void CCUMSocialSDK::setPlatforms(vector<int>* platforms) {
	if (platforms != NULL && platforms->size() > 0) {
		mPlatforms = platforms;
	}
	else
	{
		mPlatforms->push_back(SINA) ;
		mPlatforms->push_back(TENCENT_WEIBO) ;
		mPlatforms->push_back(RENREN) ;
		mPlatforms->push_back(DOUBAN) ;
		mPlatforms->push_back(SMS) ;
		mPlatforms->push_back(EMAIL) ;
	}

#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
	// 设置平台
	setSocialPlatforms(mPlatforms);
#elif CC_TARGET_PLATFORM == CC_PLATFORM_IOS
	// TODO

#endif

}

/*
 * 返回SDK中设置的所有平台
 */
vector<int>* CCUMSocialSDK::getPlatforms()
{
	return mPlatforms;
}

/*
 * 对某平台进行授权
 * @param platfrom 要授权的平台, 参考CCUMTypeDef.h中的Platform枚举定义
 * @param  callback 授权回调, 具体参考CCUMTypeDef.h中的定义
 */
void CCUMSocialSDK::authorize(int platform, AuthEventHandler callback) {
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
	// 授权某平台
	doAuthorize(platform, callback);

#elif CC_TARGET_PLATFORM == CC_PLATFORM_IOS

	UmSocialControllerIOS::authorize(platform, callback);

#endif
}

/*
 * 删除某平台的授权信息
 * @param platform 要删除授权的平台
 * @param   callback 删除授权的回调, 具体参考CCUMTypeDef.h中的定义
 */
void CCUMSocialSDK::deleteAuthorization(int platform,
		AuthEventHandler callback) {
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID

	deletePlatformAuthorization(platform, callback);

#elif CC_TARGET_PLATFORM == CC_PLATFORM_IOS

	UmSocialControllerIOS::deleteAuthorization(platform, callback);

#endif
}

/*
 * 判断某平台是否已经授权
 * @param platform 要判定的平台, 参考CCUMTypeDef.h中的Platform枚举定义
 */
bool CCUMSocialSDK::isAuthorized(int platform) {
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID

	return isPlatformAuthorized(platform);

#elif CC_TARGET_PLATFORM == CC_PLATFORM_IOS
	return UmSocialControllerIOS::isAuthorized(platform);

#endif
}

/*
 * 打开分享面板
 * @param platforms 显示在分享面板上的所有平台,平台的定义参考CCUMTypeDef.h中的Platform枚举
 * @param text 要分享的文字内容
 * @param imgName 要分享的图片的本地路径或者url, 如果是url必须则必须以http://或者https://开头
 * @param callback 分享回调,具体参考CCUMTypeDef.h中的定义
 */
void CCUMSocialSDK::openShare(const char* text,
		const char* imgName, ShareEventHandler callback) {
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
	// 设置分享内容
	setShareTextContent(text);
	// 设置图片内容
	setShareImageName(imgName);
	// 打开分享面板
	doOpenShare(callback);

#elif CC_TARGET_PLATFORM == CC_PLATFORM_IOS
	UmSocialControllerIOS::openShareWithImagePath(mPlatforms, text, imgName, callback);
#endif
}

/*
 * 直接分享到某个平台，不打开分享面板和内容编辑页面
 * @param platform 要分享到的目标平台， 参考CCUMTypeDef.h中的Platform枚举定义
 * @param text 要分享的文字内容
 * @param imgName 要分享的图片的本地路径或者url, 如果是url必须则必须以http://开头
 * @param callback 分享回调，具体参考CCUMTypeDef.h中的定义
 */
void CCUMSocialSDK::directShare(int platform, const char* text,
		const char* imgName, ShareEventHandler callback) {
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID

	setShareTextContent(text);
	setShareImageName(imgName);
	doDirectShare(platform, callback);

#elif CC_TARGET_PLATFORM == CC_PLATFORM_IOS
	UmSocialControllerIOS::directShare(text, imgName, platform, callback);

#endif
}

/*
 * 设置QQ的app id
 *
 * @param appid
 */
void CCUMSocialSDK::setQQAppIdAndAppKey(const char* appid, const char* appKey) {
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID

	setQQAndQzoneAppIdWithAppKey(appid, appKey);

#elif CC_TARGET_PLATFORM == CC_PLATFORM_IOS

	UmSocialControllerIOS::setQQAppIdAndAppKey(appid, appKey);

#endif
}

/*
 * 设置微信和微信朋友圈的app id
 *
 * @param appid
 */
void CCUMSocialSDK::setWeiXinAppId(const char* appid) {
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID

	setWeiXinPlatformAppId(appid);

#elif CC_TARGET_PLATFORM == CC_PLATFORM_IOS

	UmSocialControllerIOS::setWechatAppId(appid);

#endif
}

/*
 * 设置易信和易信朋友圈的app id
 *
 * @param appid
 */
void CCUMSocialSDK::setYiXinAppKey(const char* appKey) {
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID

	setYiXinPlatformAppKey(appKey);

#elif CC_TARGET_PLATFORM == CC_PLATFORM_IOS

	UmSocialControllerIOS::setYiXinAppKey(appKey);

#endif
}

/*
 * 设置来往和来往动态的app id
 *
 * @param appid	来往的app id
 * @param appKey  来往的app key
 * @param appid	应用名, 一般为你的应用名
 */
void CCUMSocialSDK::setLaiwangAppInfo(const char* appid, const char* appKey,
		const char* appName) {
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID

	setLaiwangPlatformAppId(appid);
	setLaiwangPlatformAppKey(appKey);
	setLaiwangPlatformAppName(appName);

#elif CC_TARGET_PLATFORM == CC_PLATFORM_IOS

	UmSocialControllerIOS::setLaiwangAppInfo(appid, appKey, appName);

#endif
}

/*
 * 设置SDK的target url, 即用户点击某条分享时跳转到的目标页面
 * @param url 用户点击某条分享时跳转到的目标页面通常为app的主页或者下载链接等
 */
void CCUMSocialSDK::setTargetUrl(const char* targetUrl) {
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID

	setShareTargetUrl(targetUrl);

#elif CC_TARGET_PLATFORM == CC_PLATFORM_IOS

	UmSocialControllerIOS::setTargetUrl(targetUrl);

#endif
}

/*
 * 设置 facebook appId
 * @param appid facebook的app id
 */
void CCUMSocialSDK::setFacebookAppId(const char *appid) {

#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID

	setFacebookPlatformAppId(appid);
#elif CC_TARGET_PLATFORM == CC_PLATFORM_IOS

	UmSocialControllerIOS::setFacebookAppId(appid);

#endif

}

/*
 * 针对iOS平台打开分享到Twitter的开关
 *
 */
void CCUMSocialSDK::openTwitterForiOS() {
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
	UmSocialControllerIOS::openTwitter();
#endif
}

/*
 * 针对iOS平台打开分享到Instagram的开关
 *
 */
void CCUMSocialSDK::openInstagramForiOS() {
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
	UmSocialControllerIOS::openInstagram();
#endif
}

/*
 *  是否开启log
 * @param flag 如果为true则开启log, 否则关闭.
 */
void CCUMSocialSDK::setLogEnable(bool flag) {
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID

	setAndroidLogEnable(flag);

#elif CC_TARGET_PLATFORM == CC_PLATFORM_IOS

	UmSocialControllerIOS::openLog(flag);

#endif

}
