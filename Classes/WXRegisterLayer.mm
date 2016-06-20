//
//  WXRegisterLayer.cpp
//  MaLi2
//
//  Created by 宋扬 on 16/5/5.
//
//

#include "WXRegisterLayer.hpp"
#include "WXRegisterSuccessLayer.hpp"
#import <AVFoundation/AVFoundation.h>

void WXRegisterLayer::touchEvent(Ref *pSender, Widget::TouchEventType type){
    
    Node *btn = (Node *)pSender;
    
    if (type == Widget::TouchEventType::ENDED) {
        if (btn->getTag() == 10) {
            if(_tf1->getString().empty()) {
                MessageBox("", "请输入手机号");
                return;
            }
//            if (_tf2->getString().empty()) {
//                MessageBox("", "请输入地区");
//                return;
//            }
             Director::getInstance()->runWithScene(WXRegisterSuccessLayer::scene());
        }
//        else if (btn->getTag() == 20) {
//            _verticalNode->setVisible(!_verticalNode->isVisible());
//        } else {
//        
//           int idx = btn->getTag() % 10;
//            _tf2->setString(_cities[idx]);
//            
//            _verticalNode->setVisible(false);
//        }
        
       
    }
}

bool WXRegisterLayer::init(){
    if (!KTLayer::init()) {
        return false;
    }

    auto bg = LayerColor::create(Color4B(229, 235, 235, 255));
    addChild(bg);
    
    auto icon = Sprite::create("人.png");
    icon->setPosition(VisibleRect::center() + Vec2(0, 300));
    addChild(icon);
    
    auto pos = VisibleRect::center() + Vec2(0, 60);
    auto tfBg = Sprite::create("bt_number.png");
    tfBg->setPosition(pos);
    addChild(tfBg);
    
    
    auto head = Text::create("账户", "Arial", 40);
    head->setTextColor(Color4B::BLACK);
    head->setPosition(pos + Vec2(-240, 0));
    addChild(head);
    
    auto foot = Text::create("必填", "Arial", 40);
    foot->setTextColor(Color4B::RED);
    foot->setPosition(pos + Vec2(240, 0));
    addChild(foot);
    
    _tf1 = TextField::create("      请输入手机号      ","Arial",40);
    _tf1->setMaxLengthEnabled(true);
    _tf1->setMaxLength(11);
    _tf1->setPosition(pos);
    _tf1->setTextColor(Color4B::BLACK);
    
//    auto size = _tf1->getContentSize();
//    CCLOG("touch size = %d %d",size.width, size.height);
    
    this->addChild(_tf1);
    
   
    
//    pos = VisibleRect::center() + Vec2(0, -30);
//    auto textBtn = Button::create("bt_number.png", "bt_number.png");
////    textBtn->setBackGroundImage("bt_number.png");
////    Sprite::create("bt_number.png");
//    textBtn->setPosition(pos);
//    textBtn->setPressedActionEnabled(false);
//    textBtn->setTag(20);
//    textBtn->addTouchEventListener(CC_CALLBACK_2(WXRegisterLayer::touchEvent, this));
//    addChild(textBtn);
    
    
//    head = Text::create("地区", "Arial", 30);
//    head->setTextColor(Color4B::BLACK);
//    head->setPosition(pos + Vec2(-240, 0));
//    addChild(head);
//    
//    foot = Text::create("必填", "Arial", 30);
//    foot->setTextColor(Color4B::RED);
//    foot->setPosition(pos + Vec2(240, 0));
//    addChild(foot);
    
//    _tf2 = TextField::create("请选择地区","Arial",30);
//    _tf2->setPosition(pos);
//    _tf2->setTextColor(Color4B::BLACK);
//    this->addChild(_tf2);
    
//    auto triangle = Sprite::create("三角.png");
//    this->addChild(triangle);
//    triangle->setPosition(pos + Vec2(140, 0));
//    triangle->setContentSize(Size(42,42));
//    triangle->setTag(20);
    

    
    auto *btn = Button::create("bt_register.png");
    btn->setPosition(VisibleRect::center()+ Vec2(0, -200));
    btn->addTouchEventListener(CC_CALLBACK_2(WXRegisterLayer::touchEvent, this));
    btn->setTag(10);
    this->addChild(btn);
    
    
//    _verticalNode = VBox::create();
//    _verticalNode->setPosition(VisibleRect::center() + Vec2(60, -80));
//    _verticalNode->setScaleZ(0.5f);
//    addChild(_verticalNode);
//    for (int i = 0; i < 4; i++) {
//        auto *bt = Button::create("bt_1.png");
//        bt->setTitleText(_cities[i]);
//        bt->setTitleColor(Color3B::BLACK);
//        bt->setTitleFontSize(30);
//        bt->setTag(30 + i);
////        auto text = Text::create(cities[i], "Arial", 30);
//        bt->addTouchEventListener(CC_CALLBACK_2(WXRegisterLayer::touchEvent, this));
//        _verticalNode->addChild(bt);
//    }
        
#if TARGET_IPHONE_SIMULATOR
    _tf1->setString("haha");
//    _tf2->setString("hoho");
#endif
    
   
    
    return true;
}

WXRegisterLayer::WXRegisterLayer():
_tf1(nullptr)
//_tf2(nullptr)
{

}

WXRegisterLayer::~WXRegisterLayer(){

}