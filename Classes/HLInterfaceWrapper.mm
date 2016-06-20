//
//  HLInterfaceWrapper.cpp
//  MaLi2
//
//  Created by 宋扬 on 16/4/7.
//
//

#include "HLInterfaceWrapper.hpp"
#import "HLInterface.h"

int HLInterfaceWrapper::market_reviwed_status(){
    return [HLInterface sharedInstance].market_reviwed_status;
}

int HLInterfaceWrapper::girl_start(){
    return [HLInterface sharedInstance].girl_start;
}

int HLInterfaceWrapper::ctrl_internal_01(){
    return [HLInterface sharedInstance].ctrl_internal_01;
}
