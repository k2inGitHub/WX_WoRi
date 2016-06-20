//
//  WXRegisterSuccessLayer.hpp
//  MaLi2
//
//  Created by 宋扬 on 16/5/5.
//
//

#ifndef WXRegisterSuccessLayer_hpp
#define WXRegisterSuccessLayer_hpp

#include "KTLayer.h"

class WXRegisterSuccessLayer : public KTLayer {
    
public:
    void touchEvent(Ref *pSender, Widget::TouchEventType type);
    
    virtual bool init();
    
    CREATE_FUNC(WXRegisterSuccessLayer);
    
    static Scene* scene(){
        Scene *sc = Scene::create();
        sc->addChild(WXRegisterSuccessLayer::create());
        return TransitionMoveInR::create(0.2, sc);;
    };
};

#endif /* WXRegisterSuccessLayer_hpp */
