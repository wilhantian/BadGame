//
//  UmSocialControllerIOS.h
//  UmengGame
//
//  Created by 张梓琦 on 14-3-16.
//
//

#ifndef __UmengGame__UmSocialControllerIOS__
#define __UmengGame__UmSocialControllerIOS__

#include "CCUMTypeDef.h"
#include <string>
#include <vector>

#define CC_ShareToWechat       1
#define CC_ShareToQQOrQzone    1
#define CC_ShareToLaiWang      1
#define CC_ShareToYiXin        1
#define CC_ShareToFacebook     1
#define CC_ShareToTwitter      1
#define CC_ShareToInstagram    1

using namespace std;
using namespace umeng::social;

class UmSocialControllerIOS {
public:
    
    //设置SDK的appkey
    static void setAppKey(const char* appKey);
    
    //初始化sdk
    static void initCocos2dxSDK(const char *sdkType, const char *version);

    //设置分享的url
    static void setTargetUrl(const char * targetUrl);
    
    //授权某社交平台
    static void authorize(int platform, AuthEventHandler callback);
    
    //解除某平台授权
    static void deleteAuthorization(int platform,AuthEventHandler callback);
    
    //是否已经授权某平台
    static bool isAuthorized(int platform);
    
    //打开分享面板
    static void openShareWithImagePath(vector<int>* platform, const char* text, const char* imagePath,ShareEventHandler callback);
    
//    //设置分享的平台
//    static void setSharePlatforms(vector<int>* platform);
    
    //直接分享到各个社交平台
    static void directShare(const char* text, const char* imagePath, int platform, ShareEventHandler callback);
    
    //打开SDK的log输出
    static void openLog(bool flag);
    
    //设置QQ互联appid，appkey
    static void setQQAppIdAndAppKey(const char *appId,const char *appKey);

    //设置微信appid
    static void setWechatAppId(const char *appId);

    //设置来往appid，appkey
    static void setLaiwangAppInfo(const char *appId, const char *appKey, const char * appName);

    //设置易信appid
    static void setYiXinAppKey(const char *appKey);
    
    //设置Facebook的appid
    static void setFacebookAppId(const char *appId);

    //打开Twitter的开关
    static void openTwitter();

    //打开Instagram的开关
    static void openInstagram();
    
private:
    static string m_appKey;
};

#endif /* defined(__UmengGame__UmSocialControllerIOS__) */
