//
//  WXRegisterSuccessLayer.cpp
//  MaLi2
//
//  Created by 宋扬 on 16/5/5.
//
//

#include "WXRegisterSuccessLayer.hpp"
#include "WXRateLayer.hpp"

void WXRegisterSuccessLayer::touchEvent(Ref *pSender, Widget::TouchEventType type){
    
    if (type == Widget::TouchEventType::ENDED) {
        CCLOG("touch end");
        Director::getInstance()->runWithScene(WXRateLayer::scene());
    }
}


bool WXRegisterSuccessLayer::init(){
    if (!KTLayer::init()) {
        return false;
    }
    auto bg = LayerColor::create(Color4B(229, 235, 235, 255));
    addChild(bg);
    
    
    auto sp = Sprite::create("bt_成功.png");
    sp->setPosition(VisibleRect::center() + Vec2(0, 180));
    addChild(sp);
    
//    auto spLabel = Text::create("bt_成功.png", "Arial", 30);
//    spLabel->setPosition(VisibleRect::center() + Vec2(0, 180));
//    addChild(spLabel);

    
    auto *btn = Button::create();
    btn->setContentSize(Size(320, 80));
    btn->setTitleText("立即登录>>");
    btn->setTitleColor(Color3B(22,165,64));
    btn->setTitleFontSize(36);
    btn->setPosition(VisibleRect::center()+ Vec2(0, 60));
    btn->addTouchEventListener(CC_CALLBACK_2(WXRegisterSuccessLayer::touchEvent, this));
    this->addChild(btn);
    
    auto label = Text::create("致敬爱的用户：\n    该应用尚处在内测阶段，可能会出现网络不稳定、闪退或者其他未知BUG，敬请谅解！遇到此类问题可彻底关闭应用后重新进入。我们正在努力完善，谢谢您的参与！", "Arial", 30);
    label->setPosition(VisibleRect::center() + Vec2(0, -300));
    label->ignoreContentAdaptWithSize(false);
    label->setContentSize(Size(600, 300));
    label->setTextHorizontalAlignment(TextHAlignment::LEFT);
    label->setTextColor(Color4B::GRAY);
    addChild(label);
    
    UserDefault::getInstance()->setBoolForKey("wx_registered", true);
    UserDefault::getInstance()->flush();
    
    WXUtil::showUnsafeInterstitial();
    
    return true;
}