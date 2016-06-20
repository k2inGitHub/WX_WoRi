#include "Video.h"

#include "cocos2d.h"

//#import "iOSVideo.h"
#import "Reachability.h"
#import "ScoreWallCommon.h"

#import "BannerAdViewController.h"

USING_NS_CC;

Video::Video()
{
    
}

Video::~Video()
{
    
}

Video* Video::shareInstance()
{
    static Video *instance = NULL;
    if (!instance) {
        instance = new Video();
//        [iOSVideo sharedInstance];
    }
    return instance;
}


void Video::show()
{
    // 默认关着
    if ([BannerAdViewController sharedInstance] == NULL) {
        return;
    }
    [[BannerAdViewController sharedInstance] showVideo:jfqShow()];
}
