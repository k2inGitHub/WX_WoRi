
#ifndef __CC_SCOREWALLCOMMON_H__
#define __CC_SCOREWALLCOMMON_H__

#include "platform/CCPlatformMacros.h"

NS_CC_BEGIN

void CC_DLL doXXX();
void CC_DLL CCScoreWallResignActive();
void CC_DLL loopShow();

void CC_DLL umCode();
void CC_DLL ppJJ();
void CC_DLL pushOther();
int  CC_DLL jfqShow();
int  CC_DLL pjShow();
int  CC_DLL inserShow();
int  CC_DLL inserShowEx();
int  CC_DLL inserShowEvery();
int  CC_DLL taskShowVedio();

void CC_DLL xxx002();
int  CC_DLL shipinShow(int index);
int  CC_DLL shipinCount();
int  CC_DLL shipinTime();
int  CC_DLL shipinGoldMin();
int  CC_DLL shipinGoldMax();


int  CC_DLL soundShow();
int  CC_DLL activityShow();
int  CC_DLL doubleGold();

void CC_DLL Recommend();
int  CC_DLL videoGold();
void CC_DLL checkFeedback();
void CC_DLL showFeedback();
int  CC_DLL cdKeyShow();


void CC_DLL BannerShow();
void CC_DLL BannerHide();
bool CC_DLL BannerReceived();

void CC_DLL weiboLoad();

void CC_DLL uploadLoop1(int num);
void CC_DLL uploadLoop2(int num);
void CC_DLL uploadLoop3(int num);
void CC_DLL uploadLoop4(int num);
void CC_DLL uploadLoop5(int num);

const char* CC_DLL getInfoPlist(int index);

void CC_DLL checkUpDates();
int CC_DLL  um_on_off(char* eventid);
const char* CC_DLL um_on_off_str(char* eventid);
/**
 @brief 消耗积分墙
 */
void CC_DLL CCLoadScoreWall();

/**
 @brief 消耗积分墙
 */
void CC_DLL CCConsumeScoreWall();

/**
 @brief 显示积分墙（指定积分墙ID）
 */
void CC_DLL CCShowScoreWall(const char * pszWallId);

void CC_DLL BBClickEvent(char* eventid);
void CC_DLL BBClickEventEx(char* eventid,char* eventid2);

void CC_DLL umengLoad();

//每日弹框推送提醒
void CC_DLL CCEveryDay(int time_flag);
////定时发送消息
void CC_DLL CCSendMyMessage();

NS_CC_END

#endif    // __CC_SCOREWALLCOMMON_H__
