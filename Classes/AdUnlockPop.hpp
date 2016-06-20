//
//  AdUnlockPop.hpp
//  MaLi2
//
//  Created by 宋扬 on 16/4/8.
//
//

#ifndef AdUnlockPop_hpp
#define AdUnlockPop_hpp

#include "KTPauseLayer.h"
#include "AdUnlockListener.h"

class AdUnlockPop : public KTPauseLayer{

public:
    ~AdUnlockPop();
    CC_SYNTHESIZE_RETAIN(AdUnlockListener *, unlockListenr, UnlockListenr);
    CC_SYNTHESIZE(Label *, buttonLabel, ButtonLabel);
    
    virtual bool init(KTPauseLayerDelegate *delegate);
    
    CREATE_FUNC_PARAM(AdUnlockPop, KTPauseLayerDelegate *, delegate);
    
    
};

#endif /* AdUnlockPop_hpp */
