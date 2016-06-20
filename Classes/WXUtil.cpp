//
//  WXUtil.cpp
//  MaLi2
//
//  Created by 宋扬 on 16/5/10.
//
//

#include "WXUtil.hpp"
#include "HLAdManagerWrapper.hpp"
#include "HLAnalsytWrapper.hpp"
#include "cocos2d.h"
using namespace cocos2d;

void WXUtil::showUnsafeInterstitial(){
    auto param = HLAnalsytWrapper::floatValue("wx_int_probability");
    auto roll = rand_0_1();
    if (param > roll){
        HLAdManagerWrapper::showUnsafeInterstitial();
    }
}