//
//  LoadingLayer.cpp
//  MaLi2
//
//  Created by 宋扬 on 16/5/10.
//
//

#include "LoadingLayer.hpp"

bool LoadingLayer::init(){

    if (!KTLayer::init()) {
        return false;
    }
    
    onLoadingFinish = nullptr;
    
    auto bg = Sprite::create("WX_loading.jpg");
    bg->setPosition(VisibleRect::center());
    addChild(bg);
    
    runAction(Sequence::create(DelayTime::create(10), CallFunc::create([=](){
        if (this->onLoadingFinish) {
            onLoadingFinish(this);
        }
    }), NULL));
    
    return true;
}