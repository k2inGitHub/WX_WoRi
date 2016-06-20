//
//  HLAdManagerWrapper.hpp
//  MaLi2
//
//  Created by 宋扬 on 16/4/7.
//
//

#ifndef HLAdManagerWrapper_hpp
#define HLAdManagerWrapper_hpp

#include <stdio.h>

class HLAdManagerWrapper {
    
public:
    static void showBanner();
    
    static void showUnsafeInterstitial();
    
    static void showEncourageInterstitial();
    
    static bool isEncourageInterstitialLoaded();
};

#endif /* HLAdManagerWrapper_hpp */
