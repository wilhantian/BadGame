/*
 * FileName : CCUMScoialSDK.h
 * Author   : hehonghui
 * Company  : umeng.com
 *
 */

#ifndef __CCUMSOCIALSDK__
#define __CCUMSOCIALSDK__

#include "cocos2d.h"
#include "CCUMTypeDef.h"
#include <vector>

USING_NS_CC;
using namespace std;

namespace umeng {
/**
 * Umeng Social命名空间, 使用该SDK必须加上USING_NS_UM_SOCIAL
 */
namespace social {
/**
 * 该类为友盟社会化组件的Cocos2d-x版本，在友盟社会化组件Android、iOS原生SDK上进行适配，支持打开分享面板分享、直接分享、授权某平台、删除某平台授权、判断某平台是否授权这几个核心功能，
 * 	如果有进一步的需求请参考本SDK进行实现。
 *
 * Android 平台实现的代码参考UmengSocial/Android目录下的实现, IOS平台的参考UmengSocial/IOS目录下的实现。
 *
 */
class CCUMSocialSDK {
private:
	CCUMSocialSDK(const char* umAppKey);
	void initSDK();
public:

	/**
	 * 构建CCUMSocialSDK对象
	 * @param appKey 友盟app key
	 */
	static CCUMSocialSDK* create(const char* appKey);

	/*
	 * 设置友盟app key
	 * @param appKey 友盟app key
	 */
	void setAppKey(const char* appkey);

	/**
	 * 对某平台进行授权
	 * @param platfrom 要授权的平台, 参考CCUMTypeDef.h中的Platform枚举定义
	 * @param  callback 授权回调, 具体参考CCUMTypeDef.h中的定义
	 */
	void authorize(int platform, AuthEventHandler callback);

	/**
	 * 删除某平台的授权信息
	 * @param platform 要删除授权的平台
	 * @param   callback 删除授权的回调, 具体参考CCUMTypeDef.h中的定义
	 */
	void deleteAuthorization(int platform, AuthEventHandler callback);

	/**
	 * 判断某平台是否已经授权
	 *@param    platform 判断某平台是否已经授权
	 */
	bool isAuthorized(int platform);

	/**
	 * 设置SDK中的所有平台
	 *@param    platforms SDK中包含的所有平台
	 */
	void setPlatforms(vector<int>* platforms);

	/**
	 * 返回SDK中设置的所有平台
	 * @return SDK中设置的所有平台
	 */
	vector<int>* getPlatforms();

	/**
	 * 打开友盟分享面板, 在调用该方法前请先调用setPlatforms函数来设置分享SDK支持的所有平台.
	 * @param text 要分享的文字内容
	 * @param imgName 要分享的图片的本地路径或者url, 如果是url必须则必须以http://或者https://开头
	 * @param callback 分享回调,具体参考CCUMTypeDef.h中的定义
	 */
	void openShare(const char* text,
			const char* imgName, ShareEventHandler callback);

	/**
	 * 直接分享到某个平台，不打开分享面板和内容编辑页面
	 * @param platform 要分享到的目标平台，参考CCUMTypeDef.h中的Platform枚举定义
	 * @param text 要分享的文字内容
	 * @param imgName 要分享的图片的本地路径或者url, 如果是url必须则必须以http://开头
	 * @param callback 分享回调，具体参考CCUMTypeDef.h中的定义
	 */
	void directShare(int platform, const char* text, const char* imgName,
			ShareEventHandler callback);

	/**
	 * 设置SDK的target url, 即用户点击某条分享时跳转到的目标页面
	 * @param url 用户点击某条分享时跳转到的目标页面通常为app的主页或者下载链接等
	 */
	void setTargetUrl(const char* targetUrl);

	/**
	 * 设置QQ和QQ空间的app id, 两个平台共用套app id, appKey
	 *
	 * @param appid	QQ空间或者QQ的app id
	 * @param appKey QQ空间或者QQ的app key
	 */
	void setQQAppIdAndAppKey(const char* appid, const char* appkey);

	/**
	 * 设置微信和微信朋友圈的app id
	 *
	 * @param appid 微信或者微信朋友圈的appid
	 */
	void setWeiXinAppId(const char* appid);

	/**
	 * 设置易信和易信朋友圈的app id
	 *
	 * @param appid 易信或者易信朋友圈的app id
	 */
	void setYiXinAppKey(const char* appid);

	/**
	 * 设置来往和来往动态的app id
	 *
	 * @param appid	来往的app id
	 * @param appKey  来往的app key
	 * @param appid	应用名, 一般为你的应用名
	 */
	void setLaiwangAppInfo(const char* appid, const char* appkey,
			const char* appName);

	/**
	 * 设置Facebook的appid
	 *
	 * @param appid   Facebook应用的app id
	 */
	void setFacebookAppId(const char *appid);

	/**
	 * 打开Twitter开关，只对iOS平台生效
	 *
	 */
	void openTwitterForiOS();

	/**
	 * 打开Instagram开关，只对iOS平台生效
	 *
	 */
	void openInstagramForiOS();

	/**
	 *  是否开启log
	 * @param flag 如果为true则开启log, 否则关闭.
	 */
	void setLogEnable(bool flag);

private:
	static CCUMSocialSDK *_instance;
	vector<int>* mPlatforms;
	char* _wrapperType;
	char* _wrapperVersion;

};
}
}

#endif
