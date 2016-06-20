//
//  WXRateLayer.cpp
//  MaLi2
//
//  Created by 宋扬 on 16/5/5.
//
//

#include "WXRateLayer.hpp"
#include "WXOpenStartLayer.hpp"
#import "HLPopupManager.h"


void WXRateLayer::onNext(){
    Director::getInstance()->runWithScene(WXOpenStartLayer::scene());
}

void WXRateLayer::touchEvent(Ref *pSender, Widget::TouchEventType type){
    
    if (type == Widget::TouchEventType::ENDED) {
        CCLOG("touch end");
        _rateBtn->setVisible(false);
        _rateText->setVisible(true);
        setNextButtonEnabled(true);
        MessageBox("", "您已成功获得授权认证");
        
        if (flag) {
            [[HLPopupManager sharedManager] openRateUrl];
        } else {
            [[HLPopupManager sharedManager] showRate:^{
             
             } andCancel:^{
             
             }];
        }
    }
}


bool WXRateLayer::init(){
    if (!WXBaseLayer::init()) {
        return false;
    }
    
    flag = HLAnalsytWrapper::boolValue("wx_show_rate");
    
    auto sp = Sprite::create(flag ? "1.png" : "1-normal.png");
    sp->setPosition(VisibleRect::center());
    addChild(sp);
    
    _rateBtn = Button::create("bt_1.png");
    _rateBtn->setTitleText(flag?"立即好评>>":"立即开通>>");
    _rateBtn->setTitleFontSize(36);
    _rateBtn->setTitleColor(Color3B::WHITE);
    _rateBtn->setPosition(VisibleRect::center() + Vec2(0, -360));
    addChild(_rateBtn);
    _rateBtn->addTouchEventListener(CC_CALLBACK_2(WXRateLayer::touchEvent, this));
    
    _rateText = Text::create("已完成", "Arial", 30);
    _rateText->setPosition(VisibleRect::center() + Vec2(0, -360));
    addChild(_rateText);
    _rateText->setTextColor(Color4B::BLACK);
    
    if (getLayerEnabled()) {
        
        _rateBtn->setVisible(false);
        _rateText->setVisible(true);
    } else {
        _rateBtn->setVisible(true);
        _rateText->setVisible(false);
    }
    
    WXUtil::showUnsafeInterstitial();
    
    return true;
}