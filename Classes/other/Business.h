#ifndef  _Business_H_
#define  _Business_H_

#include "cocos2d.h"
//#include "CCClick.h"

USING_NS_CC;

// 应用生命周期
void CC_DLL BBBusinessLoad();

void CC_DLL BBBusinessEnterBackground();

void CC_DLL BBBusinessShutdown();


void CC_DLL BBBusinessResignActive();




// 更新在线参数
void CC_DLL BBUpdateOnlineParams();

// 购买、恢复商品
void CC_DLL BBPurchaseProduct(Ref *observer,
                      SEL_CallFuncO selectorPurchased,
                      SEL_CallFuncO selectorPurchaseFailed,
                              const char* productId);

void CC_DLL BBPurchaseProduct_ex(Ref *observer,
                              SEL_CallFuncO selectorPurchased,
                              SEL_CallFuncO selectorPurchaseFailed,
                              const char* productId);

void CC_DLL BBRestoreProducts();

// 短信付费

// 装载评价系统

// 评价系统记录重要事件

// 成绩系统
void CC_DLL BBLoginGameCenter();
void CC_DLL BBSubmitScore(int score, const char * identifier);
void CC_DLL BBShowLeaderboard();
void CC_DLL BBShowAchievements();
void CC_DLL BBReportAchievementWithID(const char *identifier, float percent);

// 本地通知

// SNS分享
void CC_DLL BBShare(int time, int score1, int score2, int score3, int which);

static inline bool getOnlineBoolFlag(const char*key)
{
//    return CCClick::shareInstance()->getOnlineBoolFlag(key);
    return true;
}

static inline int getOnlineIntFlag(const char*key)
{
    return UserDefault::getInstance()->getIntegerForKey(key);
}

#endif // _Business_H_

