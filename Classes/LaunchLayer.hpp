//
//  LaunchLayer.hpp
//  MaLi2
//
//  Created by 宋扬 on 16/4/8.
//
//

#ifndef LaunchLayer_hpp
#define LaunchLayer_hpp

#include "KTLayer.h"
#include "cocos-ext.h"
#include "KTScrollLayer.h"

class LaunchLayer : public KTLayer, KTScrollLayerDelegate{

public:
    
    CC_SYNTHESIZE(MenuItem *, item, Item);
    
    void scrollLayerPageNumberDidChanged(int number) override;
    
    CREATE_FUNC(LaunchLayer);
    
    bool init()override;
    
    static Scene* scene(){
        Scene *sc = Scene::create();
        sc->addChild(LaunchLayer::create());
        return sc;
    };
};

#endif /* LaunchLayer_hpp */
