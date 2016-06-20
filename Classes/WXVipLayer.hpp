//
//  WXVipLayer.hpp
//  MaLi2
//
//  Created by 宋扬 on 16/5/6.
//
//

#ifndef WXVipLayer_hpp
#define WXVipLayer_hpp

#include "WXBaseLayer.hpp"
#include "KTPauseLayer.h"

class WXInstallLayer : public KTPauseLayer{
    
public:
    
    virtual bool init() override;
    
    CREATE_FUNC(WXInstallLayer);
};

class WXVipLayer : public WXBaseLayer {
    
public:
    
    void getNow();
    
    ~WXVipLayer();
    
    void onAlertViewClick(Ref *ref);
    
    virtual void onNext() override;
    
    virtual const std::string getLayerName() override{
        return "WXVipLayer";
    };
    
    Button *_jumpBtn;
    
    Button *_rateBtn;
    
    Text *_rateText;
    
    void touchEvent(Ref *pSender, Widget::TouchEventType type);
    
    virtual bool init() override;
    
    CREATE_FUNC(WXVipLayer);
    
    static Scene* scene(){
        Scene *sc = Scene::create();
        sc->addChild(WXVipLayer::create());
        return TransitionMoveInR::create(0.2, sc);
    };
};

#endif /* WXVipLayer_hpp */
