//
//  WXOpenLayer.hpp
//  MaLi2
//
//  Created by 宋扬 on 16/5/6.
//
//

#ifndef WXOpenLayer_hpp
#define WXOpenLayer_hpp

#include "WXBaseLayer.hpp"
#include "KTPauseLayer.h"


class WXOpenLayer : public WXBaseLayer, KTPauseLayerDelegate {
    
public:
    
    virtual void pauseLayerDidMakeSure(KTPauseLayer *layer)override;

    virtual void onNext() override;
    
    virtual const std::string getLayerName() override{
        char name[64];
        sprintf(name, "WXOpenLayer%d", _openIdx);
        return name;
    };
    
    Button *_rateBtn;
    
    Text *_rateText;
    
    CC_SYNTHESIZE(int, _openIdx, OpendIdx);
    
    void touchEvent(Ref *pSender, Widget::TouchEventType type);
    
    virtual void onEnter() override;
    virtual void onExit() override;
    
    virtual bool init(int idx);
    
    CREATE_FUNC_PARAM(WXOpenLayer, int, idx);
    
    static Scene* scene(int idx){
        Scene *sc = Scene::create();
        sc->addChild(WXOpenLayer::create(idx));
        return TransitionMoveInR::create(0.2, sc);
    };
};

#endif /* WXOpenLayer_hpp */
