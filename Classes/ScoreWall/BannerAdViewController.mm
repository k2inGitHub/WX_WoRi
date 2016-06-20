//  File: BannerAdViewController.m
//  Project: AdsMOGO iPhone Sample
//  Version: 1.1.9
//
//  Copyright 2011 AdsMogo.com. All rights reserved.
//

#import "BannerAdViewController.h"
#import "AdsMOGOContent.h"
//#import "CocoBVideo.h"

@implementation BannerAdViewController
@synthesize adView;
static BannerAdViewController *sharedInstance = nil;

+ (id)sharedInstance
{
    return sharedInstance;
}


- (void)dealloc
{
    adView.delegate = nil;
    adView.adWebBrowswerDelegate = nil;
    [super dealloc];
}

- (void)didReceiveMemoryWarning
{
    // Releases the view if it doesn't have a superview.
    [super didReceiveMemoryWarning];
    
    // Release any cached data, images, etc that aren't in use.
}


- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil {
    if ((self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil])) {
        // Custom initialization
        sharedInstance = self;
        adView = nil;
        received = false;
    }
    return self;
}

#pragma mark - View lifecycle

- (void)startAd {
    
    
    if (adView) {
        return;
    }
    NSString * strModel  = [UIDevice currentDevice].model;
    NSLog(@"%@",strModel);

    
    if([strModel isEqualToString:@"iPad"])
    {
        NSLog(@"11111");

        adView = [[AdMoGoView alloc] initWithAppKey:@"2bf808f0361745508fc98b3f62a109a3"
                                             adType:AdViewTypeLargeBanner
                                 adMoGoViewDelegate:self
                                          autoScale:YES];
    }
    else{
        
        NSLog(@"22222");

        adView = [[AdMoGoView alloc] initWithAppKey:@"d298479898b44308a463a02cc8046c38"
                                             adType:AdViewTypeNormalBanner
                                 adMoGoViewDelegate:self
                                          autoScale:YES];
    }
    
  
    
    adView.adWebBrowswerDelegate = self;
    
    
    
//    typedef enum {
//        AdViewTypeUnknown = 0,          //error
//        AdViewTypeNormalBanner = 1,     //e.g. 320 * 50 ; 320 * 48  iphone banner  
//        AdViewTypeLargeBanner = 2,      //e.g. 728 * 90 ; 768 * 110 ipad only
//        AdViewTypeMediumBanner = 3,     //e.g. 468 * 60 ; 508 * 80  ipad only
//        AdViewTypeRectangle = 4,        //e.g. 300 * 250; 320 * 270 ipad only 
//        AdViewTypeSky = 5,              //Don't support
//        AdViewTypeFullScreen = 6,       //iphone full screen ad
//        AdViewTypeVideo = 7,            //Don't support
//        AdViewTypeiPadNormalBanner = 8, //ipad use iphone banner
//    } AdViewType;
//    self.view.backgroundColor = [UIColor blackColor];
    
    if([strModel isEqualToString:@"iPad"])
    {
        adView.frame = CGRectMake(0.0, 0.0, 728.0, 90.0);
    }
    else{
        adView.frame = CGRectMake(0.0, 0.0, 320.0, 50.0);

    }
    
    [self.view addSubview:adView];
    [adView release];
    
    if ([[UIDevice currentDevice].systemVersion floatValue] >=7.0) {
        self.automaticallyAdjustsScrollViewInsets = NO;
    }
    
//    // 创建视频积分墙管理器,这⾥里使⽤用的是测试 ID,请按照 User Guide ⽂文档中获取新的 Publisher ID。
//    _videoManager = [[IndependentVideoManager alloc] initWithPublisherID:@"96ZJ0O/wzehW7wTNrC"];
//    
//    // 设置实现了 IndependentVideoManagerDelegate 协议的对象,⼀一般为 self。
//    _videoManager.delegate = self;
//    
//    
//    [CocoBVideo cBVideoInitWithAppID:@"78bbe2d16fcf2986" cBVideoAppIDSecret:@"6ebc7ecdcc23ea8b"];
//    [CocoBVideo cBCloseAlertViewWhenWantExit:false];
    
}
- (void)show
{
    adView.hidden = false;
}

- (void)hide
{
    adView.hidden = true;
}
- (void)showVideo:(int)flag
{
//    if (flag == 1) {
//        
//        [CocoBVideo cBIsHaveVideo:^(int isHaveVideoStatue){
//            if (isHaveVideoStatue == 1) {
//                NSLog(@"暂时没有可播放视频");
//                
//                [_videoManager presentIndependentVideo];
//                
//            } else if (isHaveVideoStatue == 0) {
//                NSLog(@"有可播放视频");
//                
//                [CocoBVideo cBVideoPlay:self cBVideoPlayFinishCallBackBlock:^(BOOL isFinishPlay){
//                    NSLog(@"视频播放结束");
//                } cBVideoPlayConfigCallBackBlock:^(BOOL isLegal){
//                    NSLog(@"此次播放是否有效：%d",isLegal);
//                    if (isLegal) {
//                        //[self.view makeToast:@"消费成功！"];
//                        cocos2d::__NotificationCenter::getInstance()->postNotification([@"VideoPlayed" cStringUsingEncoding:NSASCIIStringEncoding], NULL);
//                    }
//                }];
//            }
//        }];
//    }
//    else if (flag == 2) {
//        [_videoManager checkVideoAvailable];
//    }
}
- (bool)received
{
    return received;
}

- (void)viewDidUnload
{
    [super viewDidUnload];
    // Release any retained subviews of the main view.
    // e.g. self.myOutlet = nil;
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    // Return YES for supported orientations
    return (interfaceOrientation == UIInterfaceOrientationPortrait);
}



#pragma mark -
#pragma mark AdMoGoDelegate delegate 
/*
 返回广告rootViewController
 */
- (UIViewController *)viewControllerForPresentingModalView{
    return self;
}



/**
 * 广告开始请求回调
 */
- (void)adMoGoDidStartAd:(AdMoGoView *)adMoGoView{
    NSLog(@"广告开始请求回调");
}
/**
 * 广告接收成功回调
 */
- (void)adMoGoDidReceiveAd:(AdMoGoView *)adMoGoView{
    NSLog(@"广告接收成功回调");
    received = true;
}
/**
 * 广告接收失败回调
 */
- (void)adMoGoDidFailToReceiveAd:(AdMoGoView *)adMoGoView didFailWithError:(NSError *)error{
    NSLog(@"广告接收失败回调");
}
/**
 * 点击广告回调
 */
- (void)adMoGoClickAd:(AdMoGoView *)adMoGoView{
    NSLog(@"点击广告回调");
}
/**
 *You can get notified when the user delete the ad 
 广告关闭回调
 */
- (void)adMoGoDeleteAd:(AdMoGoView *)adMoGoView{
    NSLog(@"广告关闭回调");
}

#pragma mark -
#pragma mark AdMoGoWebBrowserControllerUserDelegate delegate 

/*
 浏览器将要展示
 */
- (void)webBrowserWillAppear{
    NSLog(@"浏览器将要展示");
}

/*
 浏览器已经展示
 */
- (void)webBrowserDidAppear{
    NSLog(@"浏览器已经展示");
}

/*
 浏览器将要关闭
 */
- (void)webBrowserWillClosed{
    NSLog(@"浏览器将要关闭");
}

/*
 浏览器已经关闭
 */
- (void)webBrowserDidClosed{
    NSLog(@"浏览器已经关闭");
}
/**
 *直接下载类广告 是否弹出Alert确认
 */
-(BOOL)shouldAlertQAView:(UIAlertView *)alertView{
    return NO;
}

- (void)webBrowserShare:(NSString *)url{
    
}
//#pragma mark - Manager Delegate
//
//// 积分墙开始加载列表数据
//- (void)ivManagerDidStartLoad:(IndependentVideoManager *)manager {
//    
//}
//
//// 积分墙加载完成。
//- (void)ivManagerDidFinishLoad:(IndependentVideoManager *)manager {
//    
//}
//
//// 积分墙加载失败。可能的原因由error部分提供，例如网络连接失败、被禁用等。
//- (void)ivManager:(IndependentVideoManager *)manager
//failedLoadWithError:(NSError *)error {
//    
//}
//// 视频播放完成
//- (void)ivManagerCompletePlayVideo:(IndependentVideoManager *)manager{
//    
//    
//}
//// 当积分墙要被呈现出来时，回调该方法
//- (void)ivManagerWillPresent:(IndependentVideoManager *)manager {
//    
//}
//
////  积分墙页面关闭。
//- (void)ivManagerDidClosed:(IndependentVideoManager *)manager {
//    
//}
//
//// 成功获取视频积分
//- (void)ivCompleteIndependentVideo:(IndependentVideoManager *)manager
//                    withTotalPoint:(NSNumber *)totalPoint_
//                     consumedPoint:(NSNumber *)consumedPoint_
//                      currentPoint:(NSNumber *)currentPoint_ {
//    
//    currentPoint = [currentPoint_ intValue];
//    NSLog(@"CompleteVideoOfferWithTotalpoint:%@ consumedPoint:%@ currentPoint:%@",totalPoint_,consumedPoint_,currentPoint_);
//    
//    [self consume];
//}
//
//// 获取视频积分出错
//- (void)ivManagerUncompleteIndependentVideo:(IndependentVideoManager *)manager
//                                  withError:(NSError *)error {
//    
//    NSLog(@"UncompleteVideoOfferWithError:%@",error);
//}  // Dispose of any resources that can be recreated.
//
//// 检查是否有视频可用
//- (void)ivManager:(IndependentVideoManager *)manager
//isIndependentVideoAvailable:(BOOL)available {
//    
//    if (available) {
//        
//        NSLog(@"有可播放视频广告");
//        
//        [_videoManager presentIndependentVideo];
//    }
//    else {
//        
//        NSLog(@"无可播放视频广告");
//        
//        
//        [CocoBVideo cBVideoPlay:self cBVideoPlayFinishCallBackBlock:^(BOOL isFinishPlay){
//            NSLog(@"视频播放结束");
//        } cBVideoPlayConfigCallBackBlock:^(BOOL isLegal){
//            NSLog(@"此次播放是否有效：%d",isLegal);
//            if (isLegal) {
//                //[self.view makeToast:@"消费成功！"];
//                cocos2d::NotificationCenter::getInstance()->postNotification([@"VideoPlayed" cStringUsingEncoding:NSASCIIStringEncoding], NULL);
//            }
//        }];
//    }
//}
//
//- (void)consume {
//    
//    //int remainPoint = totalPoint - consumedPoint;
//    if (currentPoint > 0) {
//        [_videoManager consumeWithPointNumber:currentPoint];
//    }
//}
//
//- (void)checkSocre {
//    
//    [_videoManager checkOwnedPoint];
//}
//
//
//// 积分查询成功之后，回调该接口，获取总积分和总已消费积分。
//- (void)ivManager:(IndependentVideoManager *)manager
//receivedTotalPoint:(NSNumber *)totalPoint_
//totalConsumedPoint:(NSNumber *)consumedPoint_ {
//    
//    totalPoint = [totalPoint_ intValue];
//    consumedPoint = [consumedPoint_ intValue];
//}
//
//// 积分查询失败之后，回调该接口，返回查询失败的错误原因。
//- (void)ivManager:(IndependentVideoManager *)manager
//failedCheckWithError:(NSError *)error {
//    NSLog(@"<demo>azManager:failedCheckWithError:%@", error);
//}
//
//// 消费请求正常应答后，回调该接口，并返回消费状态（成功或余额不足），以及总积分和总已消费积分。
//- (void)ivManager:(IndependentVideoManager *)manager
//consumedWithStatusCode:(IndependentVideoConsumeStatus)statusCode
//       totalPoint:(NSNumber *)totalPoint_
//totalConsumedPoint:(NSNumber *)consumedPoint_ {
//    
//    switch (statusCode) {
//        case eIndependentVideoConsumeSuccess:
//            //[self.view makeToast:@"消费成功！"];
//            
//            cocos2d::NotificationCenter::getInstance()->postNotification([@"VideoPlayed" cStringUsingEncoding:NSASCIIStringEncoding], NULL);
//            
//            break;
//        case eIndependentVideoConsumeInsufficient:
//            [self.view makeToast:@"消费失败，余额不足！"];
//            break;
//        case eIndependentVideoConsumeDuplicateOrder:
//            [self.view makeToast:@"订单重复！"];
//            break;
//        default:
//            break;
//    }
//    
//    totalPoint = [totalPoint_ intValue];
//    consumedPoint = [consumedPoint_ intValue];
//    currentPoint = 0;
//    
//    
//}
//
////  消费请求异常应答后，回调该接口，并返回异常的错误原因。
//- (void)ivManager:(IndependentVideoManager *)manager
//failedConsumeWithError:(NSError *)error {
//    
//    NSLog(@"<demo>azManager:failedConsumeWithError:%@", error);
//}

@end
