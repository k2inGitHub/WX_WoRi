//
//  HLAdManagerWrapper.cpp
//  MaLi2
//
//  Created by 宋扬 on 16/4/7.
//
//

#include "HLAdManagerWrapper.hpp"
#import "HLAdManager.h"

void HLAdManagerWrapper::showBanner(){
    [[HLAdManager sharedInstance] showBanner];
}

void HLAdManagerWrapper::showUnsafeInterstitial(){
    [[HLAdManager sharedInstance] showUnsafeInterstitial];
}

void HLAdManagerWrapper::showEncourageInterstitial(){

    [[HLAdManager sharedInstance] showEncourageInterstitial];
}

bool HLAdManagerWrapper::isEncourageInterstitialLoaded(){
    return [[HLAdManager sharedInstance] isEncourageInterstitialLoaded];
}