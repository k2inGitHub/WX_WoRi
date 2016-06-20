//
//  KTUtils.h
//  colorful
//
//  Created by SongYang on 13-10-27.
//
//

#ifndef colorful_KTUtils_h
#define colorful_KTUtils_h

#include "cocos2d.h"
USING_NS_CC;

#define screenSize Director::getInstance()->getWinSize()

#define isLandscape ((screenSize.width>screenSize.height)?1:0)
#define isPortrait ((screenSize.width<screenSize.height)?1:0)

// 屏幕长边上的比率
#define LPRatio ((isLandscape==1)?screenSize.width/screenSize.height:screenSize.height/screenSize.width)
#define LandRatio ((isLandscape==1)?screenSize.width/1024.0f:screenSize.height/1024.0f)
// 屏幕窄边上的比率
#define PortRatio ((isPortrait==1)?screenSize.width/768.0f:screenSize.height/768.0f)

//IOS
#define IS_IPAD ((LandRatio == 1.0f&&PortRatio == 1.0f)?1:0 )
#define IS_IPAD_HD  ((LandRatio == 2.0f&&PortRatio == 2.0f)?1:0 )
#define IS_IPHONE4 ((LPRatio == 1.5f)?1:0 )
#define IS_IPHONE5 ((LPRatio == 1136.0f/640.0f)?1:0 )
#define IS_IPHONE6 ((LPRatio == 1334.0f/750.0f)?1:0 )
#define IS_IPHONE6P ((LPRatio == 2208.0f/1242.0f)?1:0 )
//6 750 1334

//6p 1242.000000, 2208.000000


#define IS_RETINA (cocos2d::CCEGLView::sharedOpenGLView()->isRetinaEnabled()?1:0)

// 屏幕短边
#define SHORT_EDGE ((isLandscape==1)?screenSize.height:screenSize.width)
// 屏幕长边
#define TALL_EDGE ((isLandscape==1)?screenSize.width:screenSize.height)

#define IS_SMALL_SCREEN ((SHORT_EDGE<=480)?1:0)

#define IS_BIG_SCREEN ((SHORT_EDGE>480)?1:0)


#pragma mark - 适配

///背景图满屏
static inline void
lazyScale(Sprite *sp)
{
    cocos2d::Size size = Director::getInstance()->getWinSize();
    cocos2d::Size spSize = sp->getContentSize();
    
    sp->setScaleX(size.width/spSize.width);
    sp->setScaleY(size.height/spSize.height);
}
///精灵缩放一定比例
static inline void
lazyAdapt(Sprite *sp)
{
    cocos2d::Size size = Director::getInstance()->getWinSize();
    sp->setScaleX(sp->getScaleX()*(size.width/960.f));
    sp->setScaleY(sp->getScaleY()*(size.height/640.f));
}

/**
 不声明成员变量仅仅声明get set方法的宏定义
 */
#define CC_FUNC(varType, funName)\
public: virtual varType get##funName(void);\
public: virtual void set##funName(varType var);


#pragma mark - 带2个参数的create方法

#define CREATE_FUNC_PARAM2(__TYPE__,PTYPE,PNAME, PTYPE2,PNAME2) \
static __TYPE__* create(PTYPE PNAME,PTYPE2 PNAME2) \
{ \
__TYPE__ *pRet = new __TYPE__(); \
if (pRet && pRet->init(PNAME,PNAME2)) \
{ \
pRet->autorelease(); \
return pRet; \
} \
else \
{ \
delete pRet; \
pRet = NULL; \
return NULL; \
} \
}

#pragma mark - 带一个参数的create方法

#define CREATE_FUNC_PARAM(__TYPE__,PTYPE,PNAME) \
static __TYPE__* create(PTYPE PNAME) \
{ \
__TYPE__ *pRet = new __TYPE__(); \
if (pRet && pRet->init(PNAME)) \
{ \
pRet->autorelease(); \
return pRet; \
} \
else \
{ \
delete pRet; \
pRet = NULL; \
return NULL; \
} \
}

#pragma mark - LOG

static inline __String* CCStringFromPoint(cocos2d::Point point)
{
    
    return  __String::createWithFormat("{%f, %f}",point.x, point.y);
}

static inline __String* CCStringFromSize(cocos2d::Size size)
{
    return  __String::createWithFormat("{%f, %f}",size.width, size.height);
}

static inline __String* CCStringFromRect(cocos2d::Rect rect)
{
    return  __String::createWithFormat("{%s, %s}",CCStringFromPoint(rect.origin)->getCString(), CCStringFromSize(rect.size)->getCString());
}

static inline long long CCStringLongIntValue(const __String *string) {
    
    if (string->length() == 0)
    {
        return 0;
    }
    
    long long res = atoll(string->_string.c_str());
    
    CCLOG("str = %s", string->_string.c_str());
    CCLOG("res = %lld", res);
    return res;
};


#pragma mark - 获取cocos2d::Rect常用位置的坐标

static inline cocos2d::Point
ccRectCenter(cocos2d::Rect s_visibleRect)
{
    return cocos2d::Point(s_visibleRect.origin.x + s_visibleRect.size.width/2, s_visibleRect.origin.y + s_visibleRect.size.height / 2);
}

static inline cocos2d::Point
ccRectRight(cocos2d::Rect s_visibleRect)
{
    return cocos2d::Point(s_visibleRect.origin.x + s_visibleRect.size.width, s_visibleRect.origin.y + s_visibleRect.size.height / 2);
}
static inline cocos2d::Point
ccRectLeft(cocos2d::Rect s_visibleRect)
{
    return cocos2d::Point(s_visibleRect.origin.x, s_visibleRect.origin.y + s_visibleRect.size.height / 2);
}
static inline cocos2d::Point
ccRectTop(cocos2d::Rect s_visibleRect)
{
    return cocos2d::Point(s_visibleRect.origin.x + s_visibleRect.size.width / 2, s_visibleRect.origin.y + s_visibleRect.size.height);
}
static inline cocos2d::Point
ccRectBottom(cocos2d::Rect s_visibleRect)
{
    return cocos2d::Point(s_visibleRect.origin.x + s_visibleRect.size.width / 2, s_visibleRect.origin.y);
}
static inline cocos2d::Point
ccRectLeftTop(cocos2d::Rect s_visibleRect)
{
    return cocos2d::Point(s_visibleRect.origin.x, s_visibleRect.origin.y + s_visibleRect.size.height);
}
static inline cocos2d::Point
ccRectLeftBottom(cocos2d::Rect s_visibleRect)
{
    return s_visibleRect.origin;
}
static inline cocos2d::Point
ccRectRightTop(cocos2d::Rect s_visibleRect)
{
    return cocos2d::Point(s_visibleRect.origin.x + s_visibleRect.size.width, s_visibleRect.origin.y + s_visibleRect.size.height);
}
static inline cocos2d::Point
ccRectRightBottom(cocos2d::Rect s_visibleRect)
{
    return cocos2d::Point(s_visibleRect.origin.x + s_visibleRect.size.width, s_visibleRect.origin.y);
}



#pragma mark - 辅助类
class KTUtils : public Ref {
    
public:
    
    static Animation* createAnimation(const char* str,int frameCount,float delay,int index = 1);
    
    ///整数位数
    static int getNumDig(long double n){
        int len = 0;
        
        do {
            len++;
            n/=10;
        } while (floorl(n)!=0);

        return len;
    };
    
    static std::vector<int> getDigValues(long double n) {
    
        std::vector<int> values;
    
        char str[128] = {0};
        
        sprintf(str, "%.0Lf", floorl(n));
        
        CCLOG("str = %s", str);
        
        ssize_t l = strlen(str);
        
        for (int i = 0; i < l; i++) {
            if (str[i] == '.') {
                break;
            }
            values.push_back(str[i] - 48);
            
        }
        return values;
    }
    
    template <class T>
    static std::string getString(T value) {
    
        std::stringstream ss;
        ss << value;
        return ss.str();
    };
    
    static std::string stringFormat(const char * format, ...){
        
            char buf[1024];
            va_list arglist;
            va_start(arglist, format);
            vsnprintf(buf, 1024, format, arglist);
            va_end(arglist);
            return std::string(buf);
        
    };
    
    
    static struct tm getCurrentTime()
    {
        time_t rawtime;
        struct tm * timeinfo;
        
        time ( &rawtime );
        timeinfo = localtime ( &rawtime );
    
        return *timeinfo;
    };
    
    static long double MIRRound(long double n) {
    
        //整数
        long double x = floorl(n);

        //小数
        float val = n-(float)x;
        
        if (val > 0.9f ) {
            return x + 1;
        } else {
            return x;
        }
    }
    
    ///MIR 订制
    static std::string MIRString(long double n) {
        
        int ct = 0;
        long double  tmp = 0;
        long double num = n;
        do {
            tmp = n;
            ct++;
            if (ct > 2) {
                num /= 1000.0;
            }
            n /= 1000.0;
        } while (n >= 1);
        const char* append;

        switch (ct - 1) {
            case 1:{
                append = "K";
            }break;
            case 2:{
                append = "M";
            }break;
            case 3:{
                append = "B";
            }break;
            case 4:{
                append = "KB";
            }break;
            case 5:{
                append = "MB";
            }break;
            case 6:{
                append = "BB";
            }break;
            default:{
                append = "";
            }
                break;
        }
        
        if (tmp - (int)tmp) {
            return stringFormat("%.2Lf%s",tmp, append);
        } else {
        
            return stringFormat("%.0Lf%s",tmp, append);
        }
    };
    
    
    static long double atold(const char *str)
    {
        
        long double r = 0;
        size_t l = strlen(str);
        int flag = 0, count = 1;
        
        for (size_t i = 0; i < l; i++) {
            if (str[i] == '.') {
                flag = 1;
                continue;
            }
            if (flag == 1)
                count *= 10;
            r = r * 10 + (str[i] - '0');
        }
        return (long double)r / count;

    }
    
    static const char* localString(const char *key);
};


#endif
