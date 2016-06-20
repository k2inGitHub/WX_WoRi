//
//  AdUnlockListener.cpp
//  MaLi2
//
//  Created by 宋扬 on 16/4/8.
//
//

#include "AdUnlockListener.h"
#import "HLService.h"

@interface AdUnlockListeneriOS : NSObject

@property (nonatomic, assign) int unlockCount;

- (void)showUnlock;

@end

@interface AdUnlockListeneriOS (){

    AdUnlockListener *_listener;
}

@property (nonatomic, assign) int vipCurrentCount;

@property (nonatomic, assign) BOOL adShow;

@property (nonatomic, retain) NSDate *lastDate;

@end

@implementation AdUnlockListeneriOS

- (void)showUnlock{
    //kt
#if 0
    [self addVipCount];
#else
    [[HLAdManager sharedInstance] showEncourageInterstitial];
#endif
}

- (void)didBecomeActive:(NSNotification*)notification {
    NSDate *now = [NSDate date];
    NSDate *compere = [NSDate dateWithTimeInterval:30 sinceDate:_lastDate];
    if (_adShow && [now compare:compere] > 0) {
        [self addVipCount];
    } else {
        _adShow = NO;
    }
}

- (void)addVipCount{
    
    _vipCurrentCount++;
    if (_vipCurrentCount >= self.unlockCount) {
        _listener->onUnlockEvent(1);
//        [KTUIFactory showAlertViewWithTitle:nil message:@"恭喜你，解锁成功！" delegate:nil tag:0 cancelButtonTitle:@"确定" otherButtonTitles:nil, nil];
    } else {
        _listener->onUnlockEvent(0);
//        [KTUIFactory showAlertViewWithTitle:nil message:@"恭喜你已经成功激活了1个，继续加油哦~" delegate:nil tag:0 cancelButtonTitle:@"确定" otherButtonTitles:nil, nil];
    }
    
}

- (void)willResignActive:(NSNotification*)notification {
    //    if (_adShow) {
    self.lastDate = [NSDate date];
    //    }
}

- (void)onInterstitialPresent:(HLAdType *)adType{
    _adShow = NO;
}

- (void)onInterstitialFinish:(HLAdType *)adType {
    _adShow = YES;
    
}

- (instancetype)init:(void *)listener{
    self = [super init];
    if (!self) {
        return nil;
    }
    _listener = (AdUnlockListener *)listener;
    self.vipCurrentCount = 0;
    self.unlockCount = 1;
    _lastDate = [[NSDate distantFuture] retain];
    _adShow = NO;
    
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(onInterstitialFinish:) name:HLInterstitialFinishNotification object:nil];
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(onInterstitialPresent:) name:HLInterstitialPresentNotification object:nil];
    
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(didBecomeActive:) name:UIApplicationDidBecomeActiveNotification object:[UIApplication sharedApplication]];
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(willResignActive:) name:UIApplicationWillResignActiveNotification object:[UIApplication sharedApplication]];
    
    return self;
}

- (void)dealloc{
    _listener = nullptr;
    [[NSNotificationCenter defaultCenter] removeObserver:self];
    self.lastDate = nil;
    [super dealloc];
}

@end

void AdUnlockListener::onUnlockEvent(int type){
    if(type == 0) {
        if (_unlockCallback) {
            _unlockCallback(this);
        }
    } else if (type == 1) {
        if (_unlockFinishCallback) {
            _unlockFinishCallback(this);
        }
    }
}

void AdUnlockListener::addEventListener(const AdUnlockListener::AdUnlockCallback& callback, const AdUnlockListener::AdUnlockFinishCallback& finishCallback){
    _unlockCallback = callback;
    _unlockFinishCallback = finishCallback;
}

int AdUnlockListener::getCurrentUnlockNum(){
    return [((AdUnlockListeneriOS *)adUnlockiOS) vipCurrentCount];
}

int AdUnlockListener::getTotalUnlockNum(){
    return [((AdUnlockListeneriOS *)adUnlockiOS) unlockCount];
}

void AdUnlockListener::setTotalUnlockNum(int count){
    ((AdUnlockListeneriOS *)adUnlockiOS).unlockCount = count;
}

AdUnlockListener::AdUnlockListener(){
    adUnlockiOS = [[AdUnlockListeneriOS alloc] init:this];
}

AdUnlockListener::~AdUnlockListener(){
    if (adUnlockiOS) {
        [(AdUnlockListeneriOS *)adUnlockiOS dealloc];
    }
}

void AdUnlockListener::showUnlock(){
    [(AdUnlockListeneriOS *)adUnlockiOS showUnlock];
}


