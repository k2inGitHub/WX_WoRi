//
//  KTPauseLayer.h
//  KTGame
//
//  Created by 宋扬 on 13-12-7.
//
//

#ifndef __KTGame__KTPauseLayer__
#define __KTGame__KTPauseLayer__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
//#include "VisibleRect.h"
//#include "KTFactory.h"
#include "KTUtils.h"
#include "KTLayer.h"
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;

using namespace CocosDenshion;

class KTPauseLayer;

/**
 KTPauseLayer的协议
 */
class KTPauseLayerDelegate {
    
public:
    ///恢复游戏
    virtual void pauseLayerDidResume(KTPauseLayer *layer){CC_UNUSED_PARAM(layer);};
    ///重新开始游戏
    virtual void pauseLayerDidRestart(KTPauseLayer *layer){CC_UNUSED_PARAM(layer);};
    ///退出
    virtual void pauseLayerDidQuit(KTPauseLayer *layer){CC_UNUSED_PARAM(layer);};
    ///取消
    virtual void pauseLayerDidCancel(KTPauseLayer *layer){CC_UNUSED_PARAM(layer);};
    ///确定
    virtual void pauseLayerDidMakeSure(KTPauseLayer *layer){CC_UNUSED_PARAM(layer);};
};

//enum{
//    //KTPauseLayer触摸优先级
//    kKTPauseLayerHandlerPriorityNormal  = 0 - 1,
//    kKTPauseLayerHandlerPriorityHight   = 0 - 128,
//    kKTPauseLayerHandlerPriorityAlert   = 0 - 256,
//} ;

//
// KTPauseLayer
//
/**
 @brief KTPauseLayer是CCLayer的子类，实现KTPauseLayerDelegate协议，弹出Layer的基类，可以覆盖CCMenu，可以创建使用，也可以继承使用
 */
class KTPauseLayer : public KTLayer, public KTPauseLayerDelegate {
    
public:
    
    CC_SYNTHESIZE(bool, _coverOthers, CoverOthers);
    
    EventListenerTouchOneByOne *_listener;
    
    CC_SYNTHESIZE(int, _fixedPriority, FixedPriority);
    
    ///代理
    CC_SYNTHESIZE(KTPauseLayerDelegate*, _delegate, Delegate);
    
    CREATE_FUNC(KTPauseLayer);
    
    CREATE_FUNC_PARAM(KTPauseLayer, KTPauseLayerDelegate *, delegate);
    
    
protected:
    
    
    //pauseLayer
    virtual void doMakeSure();
    virtual void doCancel();
    virtual void doRestart();
    virtual void doResume();
    virtual void doQuit();
    
    virtual bool onTouchBegan(Touch *touch, Event *unused_event);
    virtual void onTouchMoved(Touch *touch, Event *unused_event);
    virtual void onTouchEnded(Touch *touch, Event *unused_event);
    virtual void onTouchCancelled(Touch *touch, Event *unused_event);
    
    virtual void onEnter();
    virtual void onExit();
    
    virtual bool init();
    virtual bool init(KTPauseLayerDelegate *delegate);
    
    KTPauseLayer();
    ~KTPauseLayer();
};



#endif /* defined(__KTGame__KTPauseLayer__) */
