//
//  WXBaseLayer.cpp
//  MaLi2
//
//  Created by 宋扬 on 16/5/5.
//
//

#include "WXBaseLayer.hpp"

//const std::string WXBaseLayer::getLayerName(){
//    return "";
//}

bool WXBaseLayer::getLayerEnabled(){
    auto name = getLayerName();
    name += "_enable";
    return UserDefault::getInstance()->getBoolForKey(name.c_str(), false);
}

void WXBaseLayer::setLayerEnabled(bool enable){
    auto name = getLayerName();
    name += "_enable";
    UserDefault::getInstance()->setBoolForKey(name.c_str(), enable);
    UserDefault::getInstance()->flush();
}

void WXBaseLayer::setNextButtonEnabled(bool enable){

    _nextButton->setEnabled(enable);
    if (enable) {
        _nextButton->setTitleColor(Color3B(22,165,64));
    } else {
        _nextButton->setTitleColor(Color3B::GRAY);
    }
    setLayerEnabled(enable);
}

void WXBaseLayer::onNext(){
    
}

void WXBaseLayer::touchNext(Ref *pSender, Widget::TouchEventType type){
    if (type == Widget::TouchEventType::ENDED) {
        onNext();
    }
}

void WXBaseLayer::respawnText(){
    
    char str[64];
    int pre = v.at(random(0, (int)v.size() - 1));
    sprintf(str, "用户%d****%0.4d成功激活应用", pre, (int)(rand_0_1() * 10000));
    _scrollText->setString(str);
    _scrollText->setPosition(VisibleRect::rightTop() + Vec2(200, -30));
    _scrollText->runAction(Sequence::createWithTwoActions(MoveBy::create(3, Vec2(-screenSize.width-400, 0)), CallFunc::create(CC_CALLBACK_0(WXBaseLayer::respawnText, this))));
}

bool WXBaseLayer::init(){

    if (!KTLayer::init()) {
        return false;
    }
    
    auto bg = LayerColor::create(Color4B(229, 235, 235, 255));
    addChild(bg);
    
    LayerColor *topBar = LayerColor::create(Color4B::GRAY, screenSize.width, 60);
    topBar->setPosition(Vec2(0, screenSize.height - 60));
    addChild(topBar);
    
    _nextButton = Button::create();
    _nextButton->setTitleText("下一步");
    _nextButton->setTitleFontSize(40);
    _nextButton->setPosition(VisibleRect::rightTop() + Vec2(-80, -100));
    _nextButton->addTouchEventListener(CC_CALLBACK_2(WXBaseLayer::touchNext, this));
    addChild(_nextButton);
    setNextButtonEnabled(getLayerEnabled());
    
    _scrollText = Text::create("", "Arial", 30);
    _scrollText->setTextColor(Color4B::RED);
    addChild(_scrollText);
    
    
    for (int i = 0; i < 9; i++) {
        v.push_back(130 + i);
    }
    v.push_back(186);
    
    respawnText();
    
    return true;
}