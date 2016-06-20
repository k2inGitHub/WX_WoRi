//
//  AdUnlockListener.hpp
//  MaLi2
//
//  Created by 宋扬 on 16/4/8.
//
//

#ifndef AdUnlockListener_hpp
#define AdUnlockListener_hpp

#include "cocos2d.h"
using namespace cocos2d;

class AdUnlockListener : public Ref{
public:
    AdUnlockListener();
    
    ~AdUnlockListener();
    
    void showUnlock();
    
    typedef std::function<void(Ref*)> AdUnlockCallback;
    
    typedef std::function<void(Ref*)> AdUnlockFinishCallback;
    
    virtual void addEventListener(const AdUnlockListener::AdUnlockCallback& callback, const AdUnlockListener::AdUnlockFinishCallback& finishCallback);
    
    int getCurrentUnlockNum();
    
    int getTotalUnlockNum();
    
    void setTotalUnlockNum(int num);
    
    void onUnlockEvent(int type);
    
protected:
    
    void *adUnlockiOS;
    
    
    AdUnlockCallback _unlockCallback;
    
    AdUnlockFinishCallback _unlockFinishCallback;
};

#endif /* AdUnlockPop_hpp */
