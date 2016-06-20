//
//  AdUnlockScene.cpp
//  MaLi2
//
//  Created by 宋扬 on 16/4/7.
//
//

#include "AdUnlockScene.hpp"
#include "FX_App.h"
#include "KTAlertView.h"
#include "VisibleRect.h"
#include "HLAdManagerWrapper.hpp"
#include "HLAnalsytWrapper.hpp"
#import "HLPopupManager.h"

AdUnlockScene::~AdUnlockScene(){
__NotificationCenter::getInstance()->removeObserver(this, "onAlertViewClick");
}

Scene* AdUnlockScene::scene(){
    auto scene = new Scene();
    scene->addChild(AdUnlockScene::create());
    return scene;
}

void AdUnlockScene::onAlertViewClick(Ref *ref){

    __Array *arry = (__Array *)ref;
    int tag = ((__Integer *)arry->getObjectAtIndex(0))->getValue();
//    int buttonIdx = ((__Integer *)arry->getObjectAtIndex(1))->getValue();
    if (tag == 25) {
        
        HLAdManagerWrapper::showUnsafeInterstitial();
    }
}

bool AdUnlockScene::init() {
    if(!Layer::init()){
        return false;
    }
    
    auto size = (Director::getInstance())->getVisibleSize();
    
    auto bg = Sprite::create("unlockBg.jpg");
    bg->setAnchorPoint(Vec2(0.5, 0));
    bg->setPosition(Vec2(size.width * 0.5, 0));
    addChild(bg);
    
    if (MyApp->is_pad) {
        bg->setScale(0.85);
    }
    
    this->setColor(Color3B::WHITE);
    
//    [[KTAlertView sharedInstance] showAlertView:nil tag:11 message:@"下载2个app即可马上免费试用微信分身版" okTitle:@"马上激活" noTitle:nil];
    __NotificationCenter::getInstance()->addObserver(this, CC_CALLFUNCO_SELECTOR(AdUnlockScene::onAlertViewClick), "onAlertViewClick", nullptr);
    
    auto flag = UserDefault::getInstance()->getBoolForKey("ML_AdUnlock", false);
    if (!flag) {
        auto flag2 = UserDefault::getInstance()->getBoolForKey("ML_Rated", false);
        if (!flag2) {
            [[HLPopupManager sharedManager] showRate:^{
                UserDefault::getInstance()->setBoolForKey("ML_Rated", true);
            } andCancel:^{
            }];
        }
        
        auto layer = AdUnlockPop::create(this);
        addChild(layer, 20);
    }
    
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = CC_CALLBACK_2(AdUnlockScene::onTouchBegan, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
    
    return true;
}



bool AdUnlockScene::onTouchBegan(Touch *touch, Event *unused_event){
    
    [[KTAlertView sharedInstance] showAlertView:nil tag:25 message:@"服务器连接错误，请重新登入" okTitle:@"确定" noTitle:nil];
    
    return true;
}