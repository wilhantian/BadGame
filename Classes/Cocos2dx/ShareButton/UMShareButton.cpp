//
//  UMShareButton.cpp
//  Umeng Social SDK ShareButton
//
//  Created by mrsimple on 3/18/14.
//
//

#include "UMShareButton.h"
#include "cocos2d.h"
#include <iostream>

USING_NS_CC;
using namespace std;
// 使用友盟命令空间
USING_NS_UM_SOCIAL;

/*
 * 构造函数
 */
UMShareButton::UMShareButton() {
	new (this) UMShareButton("", "", "");
}

/*
 * 构造函数, 没有使用cocos2d-x的内存管理, 需要开发者自行管理内存
 * @param  normalImage  按钮正常情况下显示的图片
 * @param  selectedImage 按钮选中情况下显示的图片
 * @param  umAppKey 友盟AppKey
 */
UMShareButton::UMShareButton(const char *normalImage, const char *selectedImage,
		const char* umAppKey) :
		mShareText(""), mImageName(""), mSocialSDK(NULL), mCallback(
		NULL) {
	CCLog("UMShareButton图片: normalImage = %s, selectedImage = %s.", normalImage,
			selectedImage);
#ifdef CC_CALLBACK_1
	// 初始化图片按钮
	 initWithNormalImage(normalImage, selectedImage, "", CC_CALLBACK_1(UMShareButton::shareCallback, this)) ;
//	initWithNormalImage(normalImage, selectedImage, "", [&](Ref* pSender) ->
//			{
//				CCLog("Cocos2d-x V3.X ShareButton.    in lambda.");
//				this->openShareBoard();
//			}, this));
#else
	// 初始化图片按钮
	initWithNormalImage(normalImage, selectedImage, "", this,
			menu_selector(UMShareButton::shareCallback));
#endif
	// 构造CCUMSocialSDK对象
	mSocialSDK = CCUMSocialSDK::create(umAppKey);
}

/*
 * 创建一个UMShareButton对象
 * @param  normalImage  按钮正常情况下显示的图片
 * @param  selectedImage 按钮选中情况下显示的图片
 * @param  umAppKey 友盟AppKey
 * @param callback 分享回调函数
 */
UMShareButton* UMShareButton::create(const char *normalImage,
		const char *selectedImage, const char* umAppKey,
		ShareEventHandler callback) {

	UMShareButton* shareButton = new UMShareButton(normalImage, selectedImage,
			umAppKey);
	shareButton->setShareCallback(callback);
	return shareButton;
}

/*
 * 析构函数,释放内存
 */
UMShareButton::~UMShareButton() {
	delete mSocialSDK;
}

/*
 * 获取CCUMSocialSDK对象
 */
CCUMSocialSDK* UMShareButton::getSocialSDK() {
	return mSocialSDK;
}

/*
 * 设置文本内容
 * @param text
 */
void UMShareButton::setShareContent(const char* text) {
	if (text != NULL) {
		this->mShareText = text;
	}

}

/*
 * 设置本地图片和url图片, url图片必须以http://或者https://开头
 * @param imgName 图片的本地路径或者url地址.
 */
void UMShareButton::setShareImage(const char* imgName) {
	if (imgName != NULL) {
		this->mImageName = imgName;
	}
}

/*
 * 设置分享回调回调
 * @param callback 分享回调
 */
void UMShareButton::setShareCallback(ShareEventHandler callback) {
	mCallback = callback;
}

/*
 * 设置友盟SDK支持的平台， 平台的申明参考CCUMTypeDef.h中的Platform枚举
 * @param platforms 友盟SDK支持的平台
 */
void UMShareButton::setPlatforms(vector<int>* platforms) {
	if (mSocialSDK != NULL) {
		mSocialSDK->setPlatforms(platforms);
	}
}

/*
 * 打开分享面板
 */
void UMShareButton::openShareBoard() {
	if (mSocialSDK != NULL) {
		mSocialSDK->openShare(mShareText.c_str(), mImageName.c_str(),
				mCallback);
	}
}

#ifdef CC_CALLBACK_1
/*
 * 点击该按钮时的回调, 这里实现为调用打开分享面板
 * @param pSender
 */
void UMShareButton::shareCallback(Ref* pSender)
{
	CCLog("Cocos2d-x V3.X ShareButton.");
	this->openShareBoard();
}
#else 
/*
 * 点击该按钮时的回调, 这里实现为调用打开分享面板
 * @param pSender
 */
void UMShareButton::shareCallback(CCNode* pSender) {
	CCLog("Cocos2d-x V2.X ShareButton.");
	this->openShareBoard();
}
#endif
