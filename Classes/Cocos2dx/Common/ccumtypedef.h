/**
 * CCUMTypeDef.h
 *	类型定义文件， 定义了平台枚举，分享回调、授权回调等类型.
 *
 */
#include <map>
#include <string>
using namespace std;

#ifndef _CCUMTypeDef_h
#define _CCUMTypeDef_h

/// 简化引入社会化组件SDK命名空间的宏
#ifdef __cplusplus

#define USING_NS_UM_SOCIAL      using namespace umeng::social
#else 
#define USING_NS_SOCIAL
#endif 

namespace umeng {
////////////////////////////////////////////////////////////////////////////////////
/// @namespace social
/// @brief 友盟社会化组件Cocos2d-x SDK命名空间

namespace social {

/// 各个分享平台的枚举
// enum Platform {
// 	SINA = 0,
// 	WEIXIN = 1,
// 	WEIXIN_CIRCLE = 2,
// 	QQ = 3,
// 	QZONE = 4,
// 	RENREN = 5,
// 	DOUBAN = 6,
// 	LAIWANG = 7,
// 	LAIWANG_CIRCLE = 8,
// 	YIXIN = 9,
// 	YIXIN_CIRCLE = 10,
// 	FACEBOOK = 11,
// 	TWITTER = 12,
// 	INSTAGRAM = 13,
// 	SMS = 14,
// 	EMAIL = 15,
// 	TENCENT_WEIBO = 16
// };
enum Platform
{
	SINA = 0,
	WEIXIN = 1,
	WEIXIN_CIRCLE = 2,
	QQ = 3,
	QZONE = 4,
	RENREN = 5,
	DOUBAN = 6,
	LAIWANG = 7,
	LAIWANG_CIRCLE = 8,
	YIXIN = 9,
	YIXIN_CIRCLE = 10,
	FACEBOOK = 11,
	TWITTER = 12,
	INSTAGRAM = 13,
	SMS = 14,
	EMAIL = 15,
	TENCENT_WEIBO = 16
};
/**
 * 授权回调函数指针类型
 * @param platform 平台
 * @param stCode 状态码, 200代表授权成功, 100代表开始授权, 0代表授权出错, -1代表取消授权
 * @param data 授权数据
 */
typedef void (*AuthEventHandler)(int platform, int stCode,
		const map<string, string>& data);
/**
 * 分享回调函数指针类型
 * @param platform 平台
 * @param stCode 状态码, 200代表分享成功, 100代表开始分享
 * @param errorMsg 错误信息, Android平台中没有错误信息返回
 */
typedef void (*ShareEventHandler)(int platform, int stCode,
		const string& errorMsg);

/// 授权回调selector
#define auth_selector(_SELECTOR) (AuthEventHandler)(&_SELECTOR)

/// 分享回调selector

#define share_selector(_SELECTOR) (ShareEventHandler)(&_SELECTOR)

}
}

#endif
