//
//  AdUnlockPop.cpp
//  MaLi2
//
//  Created by 宋扬 on 16/4/8.
//
//

#include "AdUnlockPop.hpp"
#include "VisibleRect.h"
#import "HLService.h"

AdUnlockPop::~AdUnlockPop(){
}

bool AdUnlockPop::init(KTPauseLayerDelegate *delegate){
    if (!KTPauseLayer::init(delegate)) {
        return false;
    }
    
    auto la = LayerColor::create(Color4B(0, 0, 0, 127));
    addChild(la, -1);
    
    auto la2 = LayerColor::create(Color4B::WHITE, 400, 280);
    la2->setPosition(VisibleRect::center() - Vec2(200, 140));
    addChild(la2, 0);
    
    
    auto label = Label::createWithSystemFont("确定(已解锁0/2)", "arial", 30,cocos2d::Size::ZERO, TextHAlignment::CENTER);
    label->setColor(Color3B::BLACK);
    setButtonLabel(label);
    auto cancel = MenuItemLabel::create(label, [=](Ref* sender){
        this->unlockListenr->showUnlock();
    });
    cancel->setAnchorPoint(cocos2d::Point::ANCHOR_MIDDLE);
    cancel->setPosition(VisibleRect::center() + Vec2(0, -60));
    
    auto menu = Menu::create(cancel, NULL);
    menu->setAnchorPoint(cocos2d::Point::ZERO);
    menu->setPosition(cocos2d::Point::ZERO);
    addChild(menu, 2);
    
    auto message = Label::createWithSystemFont("下载2个app即可马上免费试用微信分身版", "arial", 24, cocos2d::Size(300, 100), TextHAlignment::CENTER);
    message->setColor(Color3B::BLACK);
    message->setPosition(VisibleRect::center());
    addChild(message, 3);

    AdUnlockListener *listener = new AdUnlockListener();
    listener->setTotalUnlockNum(2);
    listener->addEventListener([=](Ref *sender){
        char string[256] = {0};
        sprintf(string,"确定(已解锁%d/%d)",this->unlockListenr->getCurrentUnlockNum(), this->unlockListenr->getTotalUnlockNum());
        this->buttonLabel->setString(string);
    }, [=](Ref *sender){
        
        UserDefault::getInstance()->setBoolForKey("ML_AdUnlock", true);
        UserDefault::getInstance()->flush();
        this->removeFromParent();
    });
    listener->autorelease();
    setUnlockListenr(listener);
    


    return true;
}
