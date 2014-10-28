#include "cocos2d.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include <jni.h>
#include "platform/android/jni/JniHelper.h"
#endif

using namespace cocos2d;

class JINTools
{
public:
	JINTools();
	virtual ~JINTools();
	static void showAdScreen();
	static void closeAdScreen();

	static void umengUpdate();
	static void openFeedback();
 };
