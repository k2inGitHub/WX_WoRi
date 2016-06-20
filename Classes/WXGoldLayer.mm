//
//  WXGoldLayer.cpp
//  MaLi2
//
//  Created by 宋扬 on 16/5/6.
//
//

#include "WXGoldLayer.hpp"
#include "HLAnalsytWrapper.hpp"
#import "KTAlertView.h"
#include "WXPopLayer.hpp"

void WXGoldLayer::closeCard(Ref *ref){
    auto card = (Button *)ref;
    card->loadTextures("抽奖-2.png", "抽奖-2.png", "抽奖-2.png");
    card->getChildByTag(15)->setVisible(false);
    card->getChildByTag(11)->setVisible(false);
    card->getChildByTag(13)->setVisible(false);
    
    
}

void WXGoldLayer::showResult(Button *card, int gold){

    if (gold == -1) {
    
        card->loadTextures("抽奖.png", "抽奖.png", "抽奖.png");
        auto text = (Text *)card->getChildByTag(15);
        text->setString(rewardString);
        text->setVisible(true);
    } else {
        card->loadTextures("抽奖-1.png", "抽奖-1.png", "抽奖-1.png");
        char str[64];
        sprintf(str, "x%d", gold);
        auto text = (Text *)card->getChildByTag(13);
        text->setString(str);
        text->setVisible(true);
        card->getChildByTag(11)->setVisible(true);
        
    }
}

std::vector<int> WXGoldLayer::getRandomSequence(std::vector<int> origin){

    std::vector<int> result;
    while(origin.size() > 0) {
        
        int idx = random(0, (int)origin.size()-1);
        int num = origin.at(idx);
        result.push_back(num);
        auto it = origin.begin() + idx;
        origin.erase(it);
    }
    return result;
}

std::vector<int> WXGoldLayer::getRandomSequence(int length){

    std::vector<int> origin;
    std::vector<int> result;
    for (int i = 0; i < length; i++) {
        origin.push_back(i);
    }
    while(origin.size() > 0) {
        
        int idx = random(0, (int)origin.size()-1);
        int num = origin.at(idx);
        result.push_back(num);
        auto it = origin.begin() + idx;
        origin.erase(it);
    }
    return result;
}

void WXGoldLayer::showAll(){

    
    std::vector<int> origin;
    for (int i = 0; i < 8; i++) {
        bool opened = false;
        for (auto num : _openedIdx) {
            if (num == i) {
                opened = true;
                break;
            }
        }
        if (!opened) {
            origin.push_back(i);
        }
    }
    
    auto seq = getRandomSequence(origin);
    for (auto num : seq) {
        CCLOG("num = %d", num);
    }
    int num = 0;
    for (int i = 0; i < _backCards.size(); i++) {
        
        if (_openedCards.contains(_backCards.at(i))) {
            continue;
        }
        auto btn = _backCards.at(i);
        int gold = golds[seq.at(num)];
        btn->runAction(Sequence::createWithTwoActions(DelayTime::create(num * 0.2), CallFuncN::create([=](Ref *sender){
        
            this->showResult((Button *)sender, gold);
        })));
        num++;
    }
    
    this->runAction(Sequence::createWithTwoActions(DelayTime::create(1.5), CallFuncN::create([=](Ref *sender){
        
        auto la = WXPopLayer::create();
        la->setDelegate(this);
        la->setContent("恭喜抽中该功能，\n你已成功开通此功能");
        this->addChild(la, 255, 110);
        if (HLAdManagerWrapper::isEncourageInterstitialLoaded()) {
            HLAdManagerWrapper::showEncourageInterstitial();
        } else {
            HLAdManagerWrapper::showUnsafeInterstitial();
        }
    })));
}

void WXGoldLayer::touchEvent(Ref *pSender, Widget::TouchEventType type){

    if (type == Widget::TouchEventType::ENDED) {
        Button *btn = (Button *)pSender;
        
        _openCounter++;
//        int idx = _backCards.getIndex(btn);
        
        _openedCards.pushBack(btn);
        
        if (_openCounter>= _openNum) {
            _opened = true;
            showResult(btn, -1);
            for (auto button : _backCards) {
                button->setEnabled(false);
            }
            showAll();
            
            getChildByTag(1234)->setVisible(true);
            
        } else {
            std::vector<int> seq;
            for (int i = 0; i < 8; i++) {
                bool opened = false;
                for (auto num : _openedIdx) {
                    if (num == i) {
                        opened = true;
                        break;
                    }
                }
                if (!opened) {
                    seq.push_back(i);
                }
            }
            
            int openidx = random(0, (int)seq.size() - 1);
            openidx = seq.at(openidx);
            _openedIdx.push_back(openidx);
            showResult(btn, golds[openidx]);
            btn->setEnabled(false);
            
            char str[64];
            sprintf(str, "恭喜你获得%d金币", golds[openidx]);
            
            auto la = WXPopLayer::create();
            la->setDelegate(this);
            la->setContent(str);
            addChild(la, 255);
            
            if (HLAdManagerWrapper::isEncourageInterstitialLoaded()) {
                HLAdManagerWrapper::showEncourageInterstitial();
            } else {
                HLAdManagerWrapper::showUnsafeInterstitial();
            }
        }
    }
}

void WXGoldLayer::onAlertViewClick(Ref *ref){
    
//    __Array *arry = (__Array *)ref;
//    int tag = ((__Integer *)arry->getObjectAtIndex(0))->getValue();
//    
//    if (tag == 110) {
//        doMakeSure();
//        removeFromParent();
//    }
}

void WXGoldLayer::pauseLayerDidMakeSure(KTPauseLayer *layer){

    int tag = layer->getTag();
    if (tag == 110) {
        doMakeSure();
        
        runAction(Sequence::createWithTwoActions(DelayTime::create(0.001), CallFunc::create([=](void){
            this->removeFromParent();
        })));
    }
}

bool WXGoldLayer::init(){

    if (!KTPauseLayer::init()) {
        return false;
    }
    
    _opened = false;
    _openCounter = 0;
        
    auto la = LayerColor::create(Color4B(0, 0, 0, 192));
    addChild(la);
    
    auto sp = Sprite::create("转盘-bg.png");
    sp->setPosition(VisibleRect::center());
    addChild(sp);
    
    auto close = Button::create("差.png");
    close->setPosition(VisibleRect::rightTop() + Vec2(-80, -80));
    close->addTouchEventListener([=](Ref *pSender, Widget::TouchEventType type){
        if (type == Widget::TouchEventType::ENDED) {
            this->doResume();
        }
    });
    close->setTag(1234);
    addChild(close);
    close->setVisible(false);
    
    for (int i = 0; i < 3; i++) {

        for (int j = 0; j < 3; j++) {
            auto back = Button::create("抽奖-2.png", "抽奖-2.png", "抽奖-2.png");
            back->addTouchEventListener(CC_CALLBACK_2(WXGoldLayer::touchEvent, this));
            back->setPosition(VisibleRect::center() + Vec2((j-1) * 200, -(i - 1) * 200));
            back->setTag(i*3 + j);
            addChild(back);
            _backCards.pushBack(back);
            back->setVisible(false);
            back->setEnabled(false);
            
            auto gold = Sprite::create("金币.png");
            gold->setPosition(Vec2(96, 120));
            back->addChild(gold);
            gold->setVisible(false);
            gold->setTag(11);
            
            
            auto text = Text::create("x100", "Arial", 40);
            text->setPosition(Vec2(96, 50));
            text->setTextColor(Color4B::BLACK);
            back->addChild(text);
            text->setVisible(false);
            text->setTag(13);
            
            auto text2 = Text::create("微信\n多开", "Arial-BoldMT", 46);
            text2->setPosition(Vec2(96, 96));
            text2->setTextColor(Color4B(115,53,29,255));
            text2->setTextHorizontalAlignment(TextHAlignment::CENTER);
//            text2->setContentSize(Size(190, 190));
            back->addChild(text2);
            text2->setTag(15);
            text2->setVisible(false);
            
            auto seq = Sequence::create(DelayTime::create((i*3+j)*0.1), Show::create(), DelayTime::create(1.2), CallFuncN::create(CC_CALLBACK_1(WXGoldLayer::closeCard, this)), nil);
            back->runAction(seq);
        }
    }
    
    runAction(Sequence::create(DelayTime::create(2.7), CallFunc::create(CC_CALLBACK_0(WXGoldLayer::randomSort, this)), nil));
    
    __NotificationCenter::getInstance()->addObserver(this, CC_CALLFUNCO_SELECTOR(WXGoldLayer::onAlertViewClick), "onAlertViewClick", nullptr);
    
    auto text = Text::create("抽中对应功能即可开通此功能\n观看完整广告后领取奖励", "Arial", 36);
    text->setTextHorizontalAlignment(TextHAlignment::CENTER);
    text->setPosition(VisibleRect::center() + Vec2(0, 420));
    addChild(text);
    
    return true;
}

void WXGoldLayer::randomSort(){

    float t = 0.3;
    for (int i = 0; i < 9; i++) {
        auto pair = changeIdxes[i];
        auto node1 = _backCards.at(pair[0]);
        auto node2 = _backCards.at(pair[1]);
        
        auto seq = Sequence::create(DelayTime::create(i*t), MoveTo::create(t, node2->getPosition()),MoveTo::create(0, node1->getPosition()), nil);
        node1->runAction(seq);
        
        auto seq1 = Sequence::create(DelayTime::create(i*t), MoveTo::create(t, node1->getPosition()),MoveTo::create(0, node2->getPosition()), nil);
        node2->runAction(seq1);
    }
    
    runAction(Sequence::createWithTwoActions(DelayTime::create(3), CallFunc::create(CC_CALLBACK_0(WXGoldLayer::finalSort, this))));
    
}

void WXGoldLayer::finalSort(){

    auto pos = _backCards.at(4)->getPosition();
    for (int i = 0; i < _backCards.size(); i++) {
        
        auto repeat = Repeat::create(Sequence::createWithTwoActions(ScaleTo::create(0.35, 0.75f), ScaleTo::create(0.35, 1)), 2);
        
        auto seq = Sequence::create(MoveTo::create(0.5, pos), MoveTo::create(0.5, _backCards.at(i)->getPosition()), DelayTime::create(0.35), repeat, nil);
        _backCards.at(i)->runAction(seq);
    }
    
    runAction(Sequence::createWithTwoActions(DelayTime::create(2.7), CallFunc::create([=](void){
        for(auto btn : this->_backCards){
            btn->setEnabled(true);
        }
    })));
}

void WXGoldLayer::onEnter(){

    KTPauseLayer::onEnter();
    
    auto seq = getRandomSequence(9);
//    for(auto num : seq){
//        CCLOG("enter num = %d", num);
//    }
    for (int i = 0; i < 9; i++) {
        int idx = seq[i];
        if (idx == 8) {
            showResult(_backCards.at(i), -1);
        } else {
            showResult(_backCards.at(i), golds[idx]);
        }
    }
}

WXGoldLayer::~WXGoldLayer(){
    __NotificationCenter::getInstance()->removeObserver(this, "onAlertViewClick");
}