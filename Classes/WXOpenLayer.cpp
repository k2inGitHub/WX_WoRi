//
//  WXOpenLayer.cpp
//  MaLi2
//
//  Created by 宋扬 on 16/5/6.
//
//

#include "WXOpenLayer.hpp"
#include "WXGoldLayer.hpp"
#include "HLAnalsytWrapper.hpp"
#include "WXOpenStartLayer.hpp"

void WXOpenLayer::onNext(){

    int nextIdx = _openIdx + 1;
    if (nextIdx == 6) {
        Director::getInstance()->runWithScene(WXOpenStartLayer::scene());
    } else {
        Director::getInstance()->runWithScene(WXOpenLayer::scene(nextIdx));
    }
}

void WXOpenLayer::pauseLayerDidMakeSure(KTPauseLayer *layer){

    if (_openIdx == 5) {
        UserDefault::getInstance()->setBoolForKey("WXOpenStartLayer_enable", true);
        UserDefault::getInstance()->flush();
    }
    
    setNextButtonEnabled(true);
    
    _rateBtn->setVisible(false);
    _rateText->setVisible(true);
}

void WXOpenLayer::onEnter(){
    WXBaseLayer::onEnter();
    char str[64];
    sprintf(str, "open_%d.png", _openIdx + 1);
    auto sp = Sprite::create(str);
    sp->setPosition(VisibleRect::center());
    addChild(sp);
    
    _rateBtn = Button::create("bt_1.png");
    _rateBtn->setTitleText("免费开通>>");
    _rateBtn->setTitleFontSize(36);
    _rateBtn->setTitleColor(Color3B::WHITE);
    _rateBtn->setPosition(VisibleRect::center() + Vec2(0, -340));
    addChild(_rateBtn);
    _rateBtn->addTouchEventListener(CC_CALLBACK_2(WXOpenLayer::touchEvent, this));
    
    _rateText = Text::create("已完成", "Arial", 30);
    _rateText->setPosition(VisibleRect::center() + Vec2(0, -340));
    addChild(_rateText);
    _rateText->setTextColor(Color4B::BLACK);
    
    if (getLayerEnabled()) {
        
        _rateBtn->setVisible(false);
        _rateText->setVisible(true);
    } else {
        _rateBtn->setVisible(true);
        _rateText->setVisible(false);
    }
    
    auto title = Sprite::create("开通六大逆天功能.png");
    title->setPosition(VisibleRect::center() + Vec2(0, 330));
    addChild(title);
    
    auto des = Sprite::create("原价6.png");
    des->setPosition(VisibleRect::center() + Vec2(0, -400));
    addChild(des);
}
 void WXOpenLayer::onExit(){

WXBaseLayer::onExit();
}

void WXOpenLayer::touchEvent(Ref *pSender, Widget::TouchEventType type){
    
    if (type == Widget::TouchEventType::ENDED) {
        CCLOG("touch end");
        //        _rateBtn->setVisible(false);
        //        _rateText->setVisible(true);
        //        setNextButtonEnabled(true);
        //        MessageBox("", "您已成功获得授权认证");
        std::string strings[] = {"微信\n多开", "朋友圈\n转发", "一键评论\n和点赞", "一键清理\n僵尸粉", "伪装定位\n神器", "虚拟聊天\n生成器"};
        WXGoldLayer *goldLayer = WXGoldLayer::create();
        goldLayer->rewardString = strings[_openIdx];
        
        char str[64];
        sprintf(str, "wx_open_num_%d", _openIdx);
        int num = HLAnalsytWrapper::intValue(str, 2);
        goldLayer->setOpenNum(num);
        goldLayer->setDelegate(this);
        
        addChild(goldLayer);
    }
}


bool WXOpenLayer::init(int idx){
    setOpendIdx(idx);
    if (!WXBaseLayer::init()) {
        return false;
    }
    
    
    WXUtil::showUnsafeInterstitial();
    
    return true;
}