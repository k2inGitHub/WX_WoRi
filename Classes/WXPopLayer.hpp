//
//  WXPopLayer.hpp
//  MaLi2
//
//  Created by 宋扬 on 16/5/10.
//
//

#ifndef WXPopLayer_hpp
#define WXPopLayer_hpp

#include "KTPauseLayer.h"

class WXPopLayer : public KTPauseLayer{
    
    void touchEvent(Ref *pSender, Widget::TouchEventType type);
    
    virtual void onEnter() override;

    CC_SYNTHESIZE(std::string, _content, Content);
    
//    std::string _content;

    virtual bool init() override;
    
    CREATE_FUNC(WXPopLayer);
};

#endif /* WXPopLayer_hpp */
