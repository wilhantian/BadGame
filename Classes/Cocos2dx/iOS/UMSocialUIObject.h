//
//  UMSocialUIObject.h
//  UmengGame
//
//  Created by yeahugo on 14-3-28.
//
//

#import <Foundation/Foundation.h>
#import "UMSocial.h"
#include "CCUMTypeDef.h"

using namespace umeng::social;

@interface UMSocialUIObject : NSObject<UMSocialUIDelegate>
{
    ShareEventHandler handler;
}

-(id)initWithCallback:(ShareEventHandler)callBack;

@end
