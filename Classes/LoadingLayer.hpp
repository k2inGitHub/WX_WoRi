//
//  LoadingLayer.hpp
//  MaLi2
//
//  Created by 宋扬 on 16/5/10.
//
//

#ifndef LoadingLayer_hpp
#define LoadingLayer_hpp

#include "KTLayer.h"

class LoadingLayer : public KTLayer{
public:
    typedef std::function<void(Ref*)> OnLoadingFinish;
    
    OnLoadingFinish onLoadingFinish;
    
    virtual bool init() override;
    
    CREATE_FUNC(LoadingLayer);
    
    static Scene* scene(OnLoadingFinish onLoadingFinish = nullptr){
        Scene *sc = Scene::create();
        auto la = LoadingLayer::create();
        la->onLoadingFinish = onLoadingFinish;
        sc->addChild(la);
        return sc;
    };
};

#endif /* LoadingLayer_hpp */
