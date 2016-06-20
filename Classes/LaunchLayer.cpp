//
//  LaunchLayer.cpp
//  MaLi2
//
//  Created by 宋扬 on 16/4/8.
//
//

#include "LaunchLayer.hpp"
#include "HLAdManagerWrapper.hpp"
#include "AdUnlockScene.hpp"
#include "WXRegisterLayer.hpp"
#include "WXRateLayer.hpp"

void LaunchLayer::scrollLayerPageNumberDidChanged(int num){
    item->setVisible(num == 2);
    WXUtil::showUnsafeInterstitial();
}

bool LaunchLayer::init(){
    if (!KTLayer::init()){
        return false;
    }
    
    auto la = LayerColor::create(Color4B::WHITE);
    addChild(la, -1);
    
    auto array = __Array::createWithCapacity(3);
    
    for (int i = 0; i < 3; i++) {
        char string[64];
        sprintf(string, "loading-%d.png", i+1);
        array->addObject(Sprite::create(string));
    }
    
    KTScrollLayer *scrollLayer = KTScrollLayer::create(array);
    scrollLayer->setDelegate(this);
    scrollLayer->setIndicator("GrayDot.png", "RedDot.png");
    
    auto label = Label::createWithSystemFont("启动", "arial", 28);
    label->setColor(Color3B::BLACK);
    auto item = MenuItemLabel::create(label, [=](Ref *sender){
        auto flag = UserDefault::getInstance()->getBoolForKey("wx_registered", false);
        Director::getInstance()->runWithScene(flag ? WXRateLayer::scene() : WXRegisterLayer::scene());
        HLAdManagerWrapper::showBanner();
    });
    item->setPosition(VisibleRect::bottom() + Vec2(0, 100));
    item->setVisible(false);
    setItem(item);
    auto menu = Menu::create(item, NULL);
    menu->setAnchorPoint(cocos2d::Point::ZERO);
    menu->setPosition(cocos2d::Point::ZERO);
    addChild(menu, 10);
    
    addChild(scrollLayer);
    return true;
}