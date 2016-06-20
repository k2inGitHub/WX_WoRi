//
//  WXRegisterLayer.hpp
//  MaLi2
//
//  Created by 宋扬 on 16/5/5.
//
//

#ifndef WXRegisterLayer_hpp
#define WXRegisterLayer_hpp

#include "KTLayer.h"


class WXRegisterLayer : public KTLayer{

public:
    
//    VBox *_verticalNode;
    
//    std::string _cities[4] = {"北京", "天津", "上海", "重庆"};
    
    void touchEvent(Ref *pSender, Widget::TouchEventType type);
    
    TextField *_tf1;
    
//    TextField *_tf2;
    
    virtual bool init();
    
    WXRegisterLayer();
    
    ~WXRegisterLayer();
    
    CREATE_FUNC(WXRegisterLayer);
    
    static Scene* scene(){
        Scene *sc = Scene::create();
        sc->addChild(WXRegisterLayer::create());
        return TransitionMoveInR::create(0.2, sc);
    };
    
    
};

#endif /* WXRegisterLayer_hpp */
