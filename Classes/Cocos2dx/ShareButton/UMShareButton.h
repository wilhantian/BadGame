//
//  UMShareButton.h
//  UMShareButton, 封装了CCUMSocialSDK的分享功能 ( 通过分享面板分享 ). 没有使用Cocos2d-x的内存管理策略，开发者自行管理该Button的内存释放.
//
//  Created by mrsimple on 3/18/14.
//
//

#ifndef __crossdemo__UMShareButton__
#define __crossdemo__UMShareButton__

#include <iostream>
#include "cocos2d.h"
#include "Cocos2dx/Common/CCUMSocialSDK.h"
#include <vector>

USING_NS_CC;
using namespace std;

namespace umeng {
	namespace social {

		/**
		* 该类集成自Cocos2d-x的图片按钮类，但是没有使用Cocos2d-x的内存管理，开发者许自行进行内存释放。该类封装了CCUMSocialSDK的openShare功能，
		* 	当用户点击按钮时打开友盟分享面板, 具体实现请参考源码。
		*
		*/
#ifdef CC_CALLBACK_1
		class UMShareButton : public cocos2d::MenuItemImage
		{
#else
		class UMShareButton : public cocos2d::CCMenuItemImage {
#endif
		public:
			/**
			* 析构函数,释放内存
			*/
			virtual ~UMShareButton();
			/**
			* 创建一个UMShareButton对象
			* @param  normalImage  按钮正常情况下显示的图片
			* @param  selectedImage 按钮选中情况下显示的图片
			* @param  umAppKey 友盟AppKey
			* @param callback 分享回调函数
			*/
			static UMShareButton* create(const char* normalImage, const char *selectedImage, const char* umAppKey, ShareEventHandler callback);

			/**
			* 设置要分享的文本内容
			* @param text 要分享的文本内容
			*/
			void setShareContent(const char* text);
			/**
			* 设置要分享的图片路径或者url
			* @param imgName 本地图片和url图片, url图片则必须以http://或者https://开头
			*/
			void setShareImage(const char* imgName);
			/**
			* 设置分享回调回调
			* @param callback 分享回调
			*/
			void setShareCallback(ShareEventHandler callback);
			/**
			* 设置友盟SDK支持的平台，分享面板上也会显示这些平板，如果这些平台没有添加相应的依赖则不会显示。平台的申明参考CCUMTypeDef.h中的Platform枚举
			* @param platforms 友盟SDK支持的平台
			*/
			void setPlatforms(vector<int>* platforms);
			/**
			* 获取CCUMSocialSDK对象
			* @return 返回CCUMSocialSDK单例对象
			*/
			CCUMSocialSDK* getSocialSDK();
		private:
			UMShareButton();
			// 构造函数
			UMShareButton(const char *normalImage, const char *selectedImage,
				const char* umAppKey);
			// 打开分享面板
			void openShareBoard();
#ifdef CC_CALLBACK_1
			// 分享按钮回调, 打开友盟分享面板
			void shareCallback(cocos2d::Ref* pSender);
#else
			// 分享按钮回调, 打开友盟分享面板
			void shareCallback(CCNode* pSender);
#endif

		private:
			// 友盟分享组件SDK
			CCUMSocialSDK* mSocialSDK;
			// 要添加支持的平台
			//	vector<int>* mPlatforms;
			// 要分享的文本内容
			string mShareText;
			// 要分享的图片本地路径或者url
			string mImageName;
			// 分享回调
			ShareEventHandler mCallback;
		};
		}
	}

#endif /* defined(__crossdemo__UMShareButton__) */
