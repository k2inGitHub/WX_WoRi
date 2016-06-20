//
//  HLAnalsytWrapper.hpp
//  MaLi2
//
//  Created by 宋扬 on 16/4/8.
//
//

#ifndef HLAnalsytWrapper_hpp
#define HLAnalsytWrapper_hpp

#include <stdio.h>

class HLAnalsytWrapper{

public:
    static std::string stringValue(const std::string& key, const std::string& defaultValue = "");
    static bool boolValue(const std::string& key, const bool& defaultValue = false);
    static float floatValue(const std::string& key, const float& defaultValue = 0);
    static int intValue(const std::string& key, const int& defaultValue = 0);
    static void event(const std::string& event);
};

#endif /* HLAnalsytWrapper_hpp */
