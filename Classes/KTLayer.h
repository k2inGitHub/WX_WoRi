//
//  KTScene.h
//  HelloCpp
//
//  Created by Men on 13-9-27.
//
//



#ifndef HelloCpp_KTSceneBase_h
#define HelloCpp_KTSceneBase_h

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "VisibleRect.h"
#include "KTUtils.h"
//#include "KTFactory.h"
//#include "MIRDynamicData.h"
//#include "MIRConfig.h"
#include "extensions/cocos-ext.h"
#include "ui/CocosGUI.h"
#include "HLAnalsytWrapper.hpp"
#include "HLAdManagerWrapper.hpp"
#include "WXUtil.hpp"

USING_NS_CC;
using namespace CocosDenshion;
using namespace cocos2d::ui;

/**
 Layer基类
 */
class KTLayer : public Layer{
    
public:

    float _scale;
    
//    MIRDynamicData *data;
    
    cocos2d::Size winSize ;
    
    virtual bool init();
    
    CREATE_FUNC(KTLayer);
//    virtual void keyBackClicked();
//    virtual void keyMenuClicked();
    
    
    //MIR custom
    void showTipLayer(std::string file, std::string content);
    
    void playEffect(const char*file);
    
    void playBackgroundMusic(const char* file);
};


#endif
