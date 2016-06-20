//
//  WXVipLayer.cpp
//  MaLi2
//
//  Created by 宋扬 on 16/5/6.
//
//

#include "WXVipLayer.hpp"
#import "KTAlertView.h"
#include "WXOpenStartLayer.hpp"

#pragma mark - WXInstallLayer

bool WXInstallLayer::init(){

    if (!KTPauseLayer::init()) {
        return false;
    }
    
    auto bg = Sprite::create("install_bg.jpg");
    bg->setPosition(VisibleRect::center());
    addChild(bg);
    
    auto rect = Sprite::create("install_rect.png");
    rect->setPosition(VisibleRect::center());
    rect->setScale(8.5);
    addChild(rect);

    auto title = Sprite::create("install_title.png");
    title->setPosition(VisibleRect::top() + Vec2(0, -120));
    addChild(title);
    
    auto icon = Sprite::create("安装功能包-1.png");
    icon->setPosition(VisibleRect::center() + Vec2(-160, 160));
    addChild(icon);
    
    auto animation = KTUtils::createAnimation("安装功能包-", 6, 1.6);
    icon->runAction(Sequence::createWithTwoActions(Animate::create(animation), CallFunc::create([](void){
    
        [[KTAlertView sharedInstance] showAlertView:nil tag:250 message:@"功能包安装失败" okTitle:@"重新激活" noTitle:nil];
    })));
    
    auto label = Text::create("正在安装...", "Arial", 30);
    label->setPosition(VisibleRect::left() + Vec2(160, 40));
    addChild(label);
    
    return true;
}

#pragma mark - WXVipLayer

WXVipLayer::~WXVipLayer(){

    __NotificationCenter::getInstance()->removeObserver(this, "onAlertViewClick");

}

void WXVipLayer::onAlertViewClick(Ref *ref){

    __Array *arry = (__Array *)ref;
    int tag = ((__Integer *)arry->getObjectAtIndex(0))->getValue();
    int buttonIdx = ((__Integer *)arry->getObjectAtIndex(1))->getValue();
    if (tag == 120) {
        if (buttonIdx == 1) {
            setNextButtonEnabled(true);
            _rateBtn->setVisible(false);
            _rateText->setVisible(true);
            _nextButton->setVisible(true);
            _jumpBtn->setVisible(false);
        } else {
            getNow();
        }
    } else if (tag == 130) {
    
        auto la = WXInstallLayer::create();
        addChild(la);
    } else if (tag == 250) {
        
        std::string layerNames[] = {"WXOpenStartLayer", "WXOpenLayer0", "WXOpenLayer1", "WXOpenLayer2", "WXOpenLayer3", "WXOpenLayer4", "WXOpenLayer5", "WXVipLayer"};
        
        for(auto name : layerNames) {
            std::string key = name += "_enable";
            UserDefault::getInstance()->setBoolForKey(key.c_str(), false);
        }
        UserDefault::getInstance()->flush();
        
        Director::getInstance()->runWithScene(WXOpenStartLayer::scene());
    }
}

void WXVipLayer::getNow(){
    
    Application::getInstance()->openURL(HLAnalsytWrapper::stringValue("wx_url"));
    
    MessageBox("您已成功领取会员", nullptr);
    setNextButtonEnabled(true);
    _rateBtn->setVisible(false);
    _rateText->setVisible(true);
    _nextButton->setVisible(true);
    _jumpBtn->setVisible(false);
}

void WXVipLayer::onNext(){
    [[KTAlertView sharedInstance] showAlertView:nil tag:130 message:@"已完成激活 开始安装功能包" okTitle:@"立即安装" noTitle:nil];

}

void WXVipLayer::touchEvent(Ref *pSender, Widget::TouchEventType type){
    
    if (type == Widget::TouchEventType::ENDED) {
        CCLOG("touch end");
        int tag = ((Node *)pSender)->getTag();
        if (tag == 55) {
            //jump
            
            [[KTAlertView sharedInstance] showAlertView:nil tag:120 message:@"跳过价值68元的VIP会员？（跳过后将无法再领取）" okTitle:@"确定跳过" noTitle:@"立即领取"];
            
        } else if (tag == 66){
            getNow();
        }
    }
}


bool WXVipLayer::init(){
    if (!WXBaseLayer::init()) {
        return false;
    }
    
    auto sp = Sprite::create("3.png");
    sp->setPosition(VisibleRect::center());
    addChild(sp);
    
    _rateBtn = Button::create("bt_1.png");
    _rateBtn->setTitleText("立即领取>>");
    _rateBtn->setTitleFontSize(36);
    _rateBtn->setTitleColor(Color3B::WHITE);
    _rateBtn->setPosition(VisibleRect::center() + Vec2(0, -360));
    addChild(_rateBtn);
    _rateBtn->addTouchEventListener(CC_CALLBACK_2(WXVipLayer::touchEvent, this));
    _rateBtn->setTag(66);
    
    _rateText = Text::create("已完成", "Arial", 30);
    _rateText->setPosition(VisibleRect::center() + Vec2(0, -360));
    addChild(_rateText);
    _rateText->setTextColor(Color4B::BLACK);
    
    _jumpBtn = Button::create();
    _jumpBtn->setTitleText("跳过");
    _jumpBtn->setTitleFontSize(30);
    _jumpBtn->setTitleColor(Color3B::GRAY);
    _jumpBtn->setPosition(_nextButton->getPosition());
    _jumpBtn->setTag(55);
    _jumpBtn->addTouchEventListener(CC_CALLBACK_2(WXVipLayer::touchEvent, this));

    addChild(_jumpBtn);
    
    if (getLayerEnabled()) {
        
        _rateBtn->setVisible(false);
        _rateText->setVisible(true);
        _jumpBtn->setVisible(false);
        _nextButton->setVisible(true);
    } else {
        _rateBtn->setVisible(true);
        _rateText->setVisible(false);
        _jumpBtn->setVisible(true);
        _nextButton->setVisible(false);
    }
    
    __NotificationCenter::getInstance()->addObserver(this, CC_CALLFUNCO_SELECTOR(WXVipLayer::onAlertViewClick), "onAlertViewClick", nullptr);
    
    WXUtil::showUnsafeInterstitial();

    return true;
}