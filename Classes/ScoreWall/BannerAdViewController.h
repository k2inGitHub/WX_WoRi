//  File: BannerAdViewController.h
//  Project: AdsMOGO iPhone Sample
//  Version: 1.1.9
//
//  Copyright 2011 AdsMogo.com. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "AdMoGoDelegateProtocol.h"
#import "AdMoGoView.h"
#import "AdMoGoWebBrowserControllerUserDelegate.h"
#import "RootViewController.h"
//#import "IndependentVideoManager.h"

@interface BannerAdViewController : RootViewController <AdMoGoDelegate,AdMoGoWebBrowserControllerUserDelegate>{//IndependentVideoManagerDelegate
    AdMoGoView *adView;
    bool received;
    
//    IndependentVideoManager*_videoManager;
    int totalPoint;
    int consumedPoint;
    int currentPoint;
}
@property (nonatomic, retain) AdMoGoView *adView;

+ (BannerAdViewController*)sharedInstance;
- (void)startAd;
- (void)show;
- (void)hide;
- (bool)received;
- (void)showVideo:(int)flag;

@end
