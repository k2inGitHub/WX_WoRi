//
//  WXPopLayer.cpp
//  MaLi2
//
//  Created by 宋扬 on 16/5/10.
//
//

#include "WXPopLayer.hpp"

void WXPopLayer::onEnter(){
    KTPauseLayer::onEnter();

    auto bg = Sprite::create("弹出框.png");
    bg->setPosition(VisibleRect::center());
    addChild(bg);
    
    auto label = Text::create(_content, "Arial", 36);
    label->setPosition(VisibleRect::center() + Vec2(0, 50));
    addChild(label);
    
    auto btn = Button::create("bt_1.png");
    btn->setTitleText("确定");
    btn->setTitleColor(Color3B::WHITE);
    btn->setTitleFontSize(36);
    btn->setPosition(VisibleRect::center() + Vec2(0, -90));
    btn->addTouchEventListener(CC_CALLBACK_2(WXPopLayer::touchEvent, this));
    addChild(btn);

}

void WXPopLayer::touchEvent(Ref *pSender, Widget::TouchEventType type){
    if(type == Widget::TouchEventType::ENDED) {
        
        doMakeSure();
        removeFromParent();
    }
}

bool WXPopLayer::init(){
    if (!KTPauseLayer::init()) {
        return false;
    }

    

    
    return true;
}