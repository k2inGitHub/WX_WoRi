//
//  KTScene.cpp
//  HelloCpp
//
//  Created by Men on 13-9-27.
//
//

#include "KTLayer.h"
//#include "MIRTipLayer.h"


#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include <jni.h>
#include "platform/android/jni/JniHelper.h"
#include <android/log.h>
#endif

void KTLayer::playEffect(const char*file)
{
//    if (!data->getSoundOff()) {
//        SimpleAudioEngine::getInstance()->playEffect(file);
//    }
}

void KTLayer::playBackgroundMusic(const char* file)
{
//    if (!data->getSoundOff()) {
//        SimpleAudioEngine::getInstance()->playBackgroundMusic(file);
//    }
}

bool KTLayer::init()
{
    if (!Layer::init()) {
        return false;
    }
    
    _scale = IS_IPAD_HD ? 2.0 : 1.0;
    
    winSize = Director::getInstance()->getWinSize();
    
//    data = MIRDynamicData::getInstance();
    
    return true;
}

void KTLayer::showTipLayer(std::string file, std::string content)
{
//    auto la = MIRTipLayer::create();
//    la->setFile(file);
//    la->setContent(content);
//    addChild(la, 1024);
}


