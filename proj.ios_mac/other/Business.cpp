#include "Business.h"


#include "InApp.h"
//#include "ClickCommon.h"

#include "cocos2d.h"
//#include "SNSCommon.h"
//#include "ScoreCommon.h"
USING_NS_CC;

void BBBusinessLoad()
{
//    CCClick::shareInstance()->updateOnlineParams();
   
    BBLoginGameCenter();
  
}
void BBBusinessEnterBackground()
{
//    BBGenerateLocalNotification();
}
void BBBusinessShutdown()
{
//    BBGenerateLocalNotification();
}

void BBBusinessResignActive()
{
}


//商店
void BBPurchaseProduct(Ref *observer,
                       SEL_CallFuncO selectorPurchased,
                       SEL_CallFuncO selectorPurchaseFailed,
                       const char* productId)
{
    InApp *inapp = InApp::shareInstance();
    inapp->purchaseProduct(observer, selectorPurchased, selectorPurchaseFailed, productId);
}

void BBPurchaseProduct_ex(Ref *observer,
                       SEL_CallFuncO selectorPurchased,
                       SEL_CallFuncO selectorPurchaseFailed,
                       const char* productId)
{
    InApp *inapp = InApp::shareInstance();
    inapp->purchaseProduct_ex(observer, selectorPurchased, selectorPurchaseFailed, productId);
}

void BBRestoreProducts()
{
    InApp *inapp = InApp::shareInstance();
    inapp->restoreProducts();
}

//友盟
void BBUpdateOnlineParams()
{
//    CCClick *click = CCClick::shareInstance();
//    click->updateOnlineParams();
}

//分享
void CC_DLL BBShare(int time, int score1, int score2, int score3 , int which)
{
//    CCShare(time, score1, score2, score3,which);
}

//排行榜

void BBLoginGameCenter()
{
//    CCLogin();
}

void BBSubmitScore(int score, const char * identifier)
{
//    CCSubmitScore(score, identifier);
}

void BBShowLeaderboard()
{
//    CCShowLeaderboard();
}
void BBShowAchievements()
{
//    CCShowAchievements();
}

void BBReportAchievementWithID(const char *identifier, float percent)
{
//    CCReportAchievementWithID(identifier, percent);
}
// 积分强
void BBConsumeScoreWall()
{
}

void BBShowScoreWall(const char * pszWallId)
{
}

