//
//  KTPauseLayer.cpp
//  KTGame
//
//  Created by 宋扬 on 13-12-7.
//
//

#include "KTPauseLayer.h"

bool KTPauseLayer::init()
{
    if (!KTLayer::init()) {
        return false;
    }
    
    return true;
}

bool KTPauseLayer::init(KTPauseLayerDelegate *delegate)
{
    if (!KTLayer::init()) {
        return false;
    }
    
    _delegate = delegate;
    
    
    
    return true;
}

void KTPauseLayer::onEnter()
{
    Layer::onEnter();
    
    if (_coverOthers) {
        auto listener = EventListenerTouchOneByOne::create();
        listener->setSwallowTouches(true);
        listener->onTouchBegan = CC_CALLBACK_2(KTPauseLayer::onTouchBegan, this);
        listener->onTouchMoved = CC_CALLBACK_2(KTPauseLayer::onTouchMoved, this);
        listener->onTouchEnded = CC_CALLBACK_2(KTPauseLayer::onTouchEnded, this);
        listener->onTouchCancelled = CC_CALLBACK_2(KTPauseLayer::onTouchCancelled, this);
        _listener = listener;
        
        if (_fixedPriority != 0)
        {
            _eventDispatcher->addEventListenerWithFixedPriority(_listener, _fixedPriority);
        }
        else
        {
            _eventDispatcher->addEventListenerWithSceneGraphPriority(_listener, this);
        }
    } 
}

bool KTPauseLayer::onTouchBegan(Touch *touch, Event *unused_event)
{
    return true;
}

 void KTPauseLayer::onTouchMoved(Touch *touch, Event *unused_event)
{

}

 void KTPauseLayer::onTouchEnded(Touch *touch, Event *unused_event)
{

}

 void KTPauseLayer::onTouchCancelled(Touch *touch, Event *unused_event)
{

}

void KTPauseLayer::onExit()
{
    if (_listener) {
        _eventDispatcher->removeEventListener(_listener);
    }
    
    Layer::onExit();
}

void KTPauseLayer::doCancel()
{
    _delegate->pauseLayerDidCancel(this);
}

void KTPauseLayer::doMakeSure()
{
    _delegate->pauseLayerDidMakeSure(this);
}

void KTPauseLayer::doRestart()
{
    _delegate->pauseLayerDidRestart(this);
}
void KTPauseLayer::doResume()
{
    _delegate->pauseLayerDidResume(this);
    removeFromParentAndCleanup(true);
}
void KTPauseLayer::doQuit()
{
    _delegate->pauseLayerDidQuit(this);
}

KTPauseLayer::~KTPauseLayer()
{
    _delegate = NULL;
}

KTPauseLayer::KTPauseLayer()
{
    _delegate = NULL;
    winSize = cocos2d::Size::ZERO;
    _fixedPriority = 0;
    _listener = NULL;
    _coverOthers = true;
}
