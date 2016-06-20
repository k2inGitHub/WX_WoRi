//
//

#ifndef  _APP_DELEGATE_H_
#define  _APP_DELEGATE_H_

#include "cocos2d.h"

// 方便上线配置和调试，广告、内付、在线参数等
#define UseAdvertise            true  // true
#define Debug_Purchase          false  // false

typedef struct tagResource
{
    cocos2d::Size size;
    char directory[100];
}Resource;

static Resource res320x480    =  { cocos2d::Size(320,  480),    "res320x480"    };
static Resource res640x960    =  { cocos2d::Size(640,  960),    "res640x960"    };
static Resource res640x1136   =  { cocos2d::Size(640,  1136),   "res640x1136"   };
static Resource res768x1024   =  { cocos2d::Size(768,  1024),   "res768x1024"   };
static Resource res1536x2048  =  { cocos2d::Size(1536, 2048),   "res1536x2048"  };

static cocos2d::Size designResolutionSize = cocos2d::Size(640,  960);

/**
 @brief    The cocos2d Application.
 
 The reason for implement as private inheritance is to hide some interface call by Director.
 */
class  AppDelegate : private cocos2d::Application
{
public:
    AppDelegate();
    virtual ~AppDelegate();
    
    virtual void initGLContextAttrs();
    
    /**
     @brief    Implement Director and Scene init code here.
     @return true    Initialize success, app continue.
     @return false   Initialize failed, app terminate.
     */
    virtual bool applicationDidFinishLaunching();
    
    /**
     @brief  The function be called when the application enter background
     @param  the pointer of the application
     */
    virtual void applicationDidEnterBackground();
    
    /**
     @brief  The function be called when the application enter foreground
     @param  the pointer of the application
     */
    virtual void applicationWillEnterForeground();
};

#endif // _APP_DELEGATE_H_

