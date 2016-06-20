//
//  WXOpenStartLayer.hpp
//  MaLi2
//
//  Created by 宋扬 on 16/5/5.
//
//

#ifndef WXOpenStartLayer_hpp
#define WXOpenStartLayer_hpp

#include "WXBaseLayer.hpp"

class WXOpenStartLayer : public WXBaseLayer {
    
public:
    
    virtual void onNext() override;
    
    virtual const std::string getLayerName() override{
        return "WXOpenStartLayer";
    };
    
    Button *_rateBtn;
    
    Text *_rateText;
    
    void touchEvent(Ref *pSender, Widget::TouchEventType type);
    
    virtual bool init() override;
    
    CREATE_FUNC(WXOpenStartLayer);
    
    static Scene* scene(){
        Scene *sc = Scene::create();
        sc->addChild(WXOpenStartLayer::create());
        return TransitionMoveInR::create(0.2, sc);
    };
};

#endif /* WXOpenStartLayer_hpp */
