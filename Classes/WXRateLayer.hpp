//
//  WXRateLayer.hpp
//  MaLi2
//
//  Created by 宋扬 on 16/5/5.
//
//

#ifndef WXRateLayer_hpp
#define WXRateLayer_hpp

#include "WXBaseLayer.hpp"

class WXRateLayer : public WXBaseLayer {
    
public:
    
    bool flag;
    
    virtual const std::string getLayerName() override{
        return "WXRateLayer";
    };
    
    Button *_rateBtn;
    
    Text *_rateText;
    
    void touchEvent(Ref *pSender, Widget::TouchEventType type);
    
    virtual bool init() override;
    
    virtual void onNext() override;
    
    CREATE_FUNC(WXRateLayer);
    
    static Scene* scene(){
        Scene *sc = Scene::create();
        sc->addChild(WXRateLayer::create());
        return TransitionMoveInR::create(0.2, sc);
    };
};

#endif /* WXRateLayer_hpp */
