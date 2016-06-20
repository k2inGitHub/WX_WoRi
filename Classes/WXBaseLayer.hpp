//
//  WXBaseLayer.hpp
//  MaLi2
//
//  Created by 宋扬 on 16/5/5.
//
//

#ifndef WXBaseLayer_hpp
#define WXBaseLayer_hpp

#include "KTLayer.h"

class WXBaseLayer : public KTLayer {
    
public:
    
    std::vector<int> v;
    
    bool getLayerEnabled();
    
    void setLayerEnabled(bool enable);
    
    virtual const std::string getLayerName() {
        assert("fuck");
        return "";
    };
    
    void respawnText();
    
    Text *_scrollText;
    
    virtual void setNextButtonEnabled(bool enable);
    
    Button *_nextButton;
    
    virtual void onNext();
    
    void touchNext(Ref *pSender, Widget::TouchEventType type);
    
    virtual bool init();
    
    CREATE_FUNC(WXBaseLayer);
};

#endif /* WXBaseLayer_hpp */
