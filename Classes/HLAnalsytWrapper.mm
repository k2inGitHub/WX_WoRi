//
//  HLAnalsytWrapper.cpp
//  MaLi2
//
//  Created by 宋扬 on 16/4/8.
//
//

#include "HLAnalsytWrapper.hpp"
#import "HLService.h"

std::string HLAnalsytWrapper::stringValue(const std::string& key, const std::string& defaultValue){

    return [HLAnalyst stringValue:[NSString stringWithUTF8String:key.c_str()] defaultValue:[NSString stringWithUTF8String:defaultValue.c_str()]].UTF8String;
}


bool HLAnalsytWrapper::boolValue(const std::string& key, const bool& defaultValue){

    return [HLAnalyst boolValue:[NSString stringWithUTF8String:key.c_str()] defaultValue:defaultValue];
}

float HLAnalsytWrapper::floatValue(const std::string& key, const float& defaultValue){
    return [HLAnalyst floatValue:[NSString stringWithUTF8String:key.c_str()] defaultValue:defaultValue];
}
int HLAnalsytWrapper::intValue(const std::string& key, const int& defaultValue){
    return [HLAnalyst intValue:[NSString stringWithUTF8String:key.c_str()] defaultValue:defaultValue];
}
void HLAnalsytWrapper::event(const std::string& event){
    [HLAnalyst event:[NSString stringWithUTF8String:event.c_str()]];
}