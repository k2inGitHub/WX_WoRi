//
//  AdUnlockScene.hpp
//  MaLi2
//
//  Created by 宋扬 on 16/4/7.
//
//

#ifndef AdUnlockScene_hpp
#define AdUnlockScene_hpp

#include "cocos2d.h"

#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
#include "AdUnlockPop.hpp"

using namespace cocostudio;
using namespace cocostudio::timeline;
using namespace cocos2d::ui;
using namespace cocos2d;

class AdUnlockScene : public Layer,KTPauseLayerDelegate {
    
    
public:
    ~AdUnlockScene();
    bool init() override;
    CREATE_FUNC(AdUnlockScene);
    static Scene* scene();
    
    void onAlertViewClick(Ref *ref);
    virtual bool onTouchBegan(Touch *touch, Event *unused_event) override;
};

#endif /* AdUnlockScene_hpp */
