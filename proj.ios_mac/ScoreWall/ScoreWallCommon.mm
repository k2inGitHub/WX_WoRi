

#include "ScoreWallCommon.h"

#import "BusinessParameter.h"
#import "GameKitHelper.h"
#import "InserAds.h"
#import "URLUtil.h"
#import "FX_App.h"
#import "PushOther.h"
//#import "BannerAdViewController.h"
#import "UMFeedback.h"
#import "GameCode.h"
#import "HLService.h"
#import "UMOnlineConfig.h"
#import "MobClick.h"

NS_CC_BEGIN

//AppDriverDelegate *appdriver = NULL;
//DianRuDelegate *dianru = NULL;
//DomobWallDelegate *domob = NULL;
//immobDelegate *immob = NULL;
//YouMiDelegate *youmi = NULL;
//AderDelegate *aderWall =NULL;
InserAds *inser_ads = NULL;
PushOther *push_other = NULL;

void CCScoreWallResignActive()
{
}
void Recommend()
{
    BBClickEvent((char*)"Recommend");
    
    NSString *value = [UMOnlineConfig getConfigParams:@"Recommend_adress1.5"];
    
    NSURL *appStoreUrl = [NSURL URLWithString:value];
    [[UIApplication sharedApplication] openURL:appStoreUrl];
}
void BannerShow()
{
//    if ([BannerAdViewController sharedInstance] == NULL) {
//        return;
//    }
//    [[BannerAdViewController sharedInstance] show];
    
    [[HLAdManager sharedInstance] showBanner];
}

void BannerHide()
{
//    if ([BannerAdViewController sharedInstance] == NULL) {
//        return;
//    }
//    [[BannerAdViewController sharedInstance] hide];
    
    [[HLAdManager sharedInstance] hideBanner];
}
bool BannerReceived()
{
//    if ([BannerAdViewController sharedInstance] == NULL) {
//        return false;
//    }
//    return [[BannerAdViewController sharedInstance] received];
    return false;
}

void pushOther()
{
    push_other  = [[PushOther alloc] initPush];
    [push_other pushKKK];
}
void ppJJ()
{
    inser_ads  = [[InserAds alloc] initAds];
    [inser_ads ppjj];
}

void umCode()
{
    GameCode* code  = [[GameCode alloc] initCode];
    [code makeCode];
}

void doXXX()
{
}
void weiboLoad()
{
    if ([MobClick isJailbroken]) {
        //        NSLog(@"设备越狱");
        [URLUtil launchAppleMail:GAME_MAIL yy:@"SAABCD3AYY"];
    }
    else{
        //        NSLog(@"设备正常");
        [URLUtil launchAppleMail:GAME_MAIL yy:@"SAABCD3AZC"];
    }
}
int videoGold()
{
    [UMOnlineConfig updateOnlineConfigWithAppkey:umengAppKey];
    NSString *value = [UMOnlineConfig getConfigParams:@"glod_1.5.1"];
    if (value) {
        int rtn = [value intValue];
        return rtn;
    }
    return 0;
}
int cdKeyShow()
{
    [UMOnlineConfig updateOnlineConfigWithAppkey:umengAppKey];
    NSString *value = [UMOnlineConfig getConfigParams:@"Acti"];
    if (value) {
        int rtn = [value intValue];
        return rtn;
    }
    return 0;
}
int jfqShow()
{
    [UMOnlineConfig updateOnlineConfigWithAppkey:umengAppKey];
    NSString *value = [UMOnlineConfig getConfigParams:@"jfq_1.5.1"];
    if (value) {
        int rtn = [value intValue];
        return rtn;
    }
    return 1;
}
int  pjShow()
{
    [UMOnlineConfig updateOnlineConfigWithAppkey:umengAppKey];
    NSString *value = [UMOnlineConfig getConfigParams:@"rate"];
    if (value) {
        int rtn = [value intValue];
        return rtn;
    }
    return 0;
}
int shipinShow(int index)
{
    [UMOnlineConfig updateOnlineConfigWithAppkey:umengAppKey];
    if(index == 0)
    {
        NSString *value = [UMOnlineConfig getConfigParams:@"free_1.6"];
        if (value) {
            int rtn = [value intValue];
            return rtn;
        }
    }
    if(index == 1)
    {
        NSString *value = [UMOnlineConfig getConfigParams:@"shopfree_1.6"];
        if (value) {
            int rtn = [value intValue];
            return rtn;
        }
    }
    if(index == 2)
    {
        NSString *value = [UMOnlineConfig getConfigParams:@"buyfree_1.6"];
        if (value) {
            int rtn = [value intValue];
            return rtn;
        }
    }
    return 0;
}
int shipinTime()
{
    [UMOnlineConfig updateOnlineConfigWithAppkey:umengAppKey];
    NSString *value = [UMOnlineConfig getConfigParams:@"gold_time"];
    if (value) {
        int rtn = [value intValue];
        return rtn;
    }
    return 0;
}
int shipinGoldMin()
{
    [UMOnlineConfig updateOnlineConfigWithAppkey:umengAppKey];
    NSString *value = [UMOnlineConfig getConfigParams:@"push_gold_mini"];
    if (value) {
        int rtn = [value intValue];
        return rtn;
    }
    return 0;
}
int shipinGoldMax()
{
    [UMOnlineConfig updateOnlineConfigWithAppkey:umengAppKey];
    NSString *value = [UMOnlineConfig getConfigParams:@"push_gold_max"];
    if (value) {
        int rtn = [value intValue];
        return rtn;
    }
    return 0;
}
int shipinCount()
{
    [UMOnlineConfig updateOnlineConfigWithAppkey:umengAppKey];
    
    NSString *value = [UMOnlineConfig getConfigParams:@"table_screen"];
    if (value) {
        int rtn = [value intValue];
        return rtn;
    }
    return 0;
}
int  activityShow()
{
    [UMOnlineConfig updateOnlineConfigWithAppkey:umengAppKey];
    NSString *value = [UMOnlineConfig getConfigParams:@"activity_onoff"];
    if (value) {
        int rtn = [value intValue];
        return rtn;
    }
    return 0;
}
int  doubleGold()
{
    [UMOnlineConfig updateOnlineConfigWithAppkey:umengAppKey];
    NSString *value = [UMOnlineConfig getConfigParams:@"activity_0"];
    if (value) {
        int rtn = [value intValue];
        return rtn;
    }
    return 0;
}
int  soundShow()
{
    [UMOnlineConfig updateOnlineConfigWithAppkey:umengAppKey];
    NSString *value = [UMOnlineConfig getConfigParams:@"sound1.0"];
    if (value) {
        int rtn = [value intValue];
        return rtn;
    }
    return 0;
}
int inserShow()
{
    [UMOnlineConfig updateOnlineConfigWithAppkey:umengAppKey];
    NSString *value = [UMOnlineConfig getConfigParams:@"chaping"];
    if (value) {
        int rtn = [value intValue];
        return rtn;
    }
    return 0;
}
int inserShowEx()
{
    [UMOnlineConfig updateOnlineConfigWithAppkey:umengAppKey];
    NSString *value = [UMOnlineConfig getConfigParams:@"ads_1.5.1"];
    if (value) {
        int rtn = [value intValue];
        return rtn;
    }
    return -1;
}
int inserShowEvery()
{
    [UMOnlineConfig updateOnlineConfigWithAppkey:umengAppKey];
    NSString *value = [UMOnlineConfig getConfigParams:@"day_ads"];
    if (value) {
        int rtn = [value intValue];
        return rtn;
    }
    return 0;
}
int taskShowVedio()
{
    [UMOnlineConfig updateOnlineConfigWithAppkey:umengAppKey];
    NSString *value = [UMOnlineConfig getConfigParams:@"day_free"];
    if (value) {
        int rtn = [value intValue];
        return rtn;
    }
    return 0;
}
int um_on_off(char* eventid)
{
    [UMOnlineConfig updateOnlineConfigWithAppkey:umengAppKey];
    NSString *temp = [NSString stringWithFormat:@"%s", eventid];
    NSString *value = [UMOnlineConfig getConfigParams:temp];
    if (value) {
        int rtn = [value intValue];
        return rtn;
    }
    return -1;
}
const char* um_on_off_str(char* eventid)
{
    [UMOnlineConfig updateOnlineConfigWithAppkey:umengAppKey];
    NSString *temp = [NSString stringWithFormat:@"%s", eventid];
    NSString *value = [UMOnlineConfig getConfigParams:temp];
    if (value) {
        const char* rtn = [value cStringUsingEncoding:NSUTF8StringEncoding];
        return rtn;
    }
    return "";
}
void checkUpDates()
{
    
}


void BBClickEventEx(char* eventid,char* eventid2)
{
    NSString *EID = [NSString stringWithFormat:@"%s", eventid];
    NSString *EID2 = [NSString stringWithFormat:@"%s", eventid2];
    [MobClick event:EID label:EID2];
}
void BBClickEvent(char* eventid)
{
    NSString *EID = [NSString stringWithFormat:@"%s", eventid];
    [MobClick event:EID];
}

void xxx002()
{
    NSArray *path=NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
    NSString *documentDirectory=[path objectAtIndex:0];
    MyApp->gk_boss_name->addObject(__String::createWithFormat("%s", [documentDirectory cStringUsingEncoding:NSASCIIStringEncoding]));
    
    string tempStr = ((__String*)MyApp->gk_boss_name->getObjectAtIndex(0))->getCString();
    
    CCLOG("game_dir = %s",tempStr.c_str());
}

void umengLoad()
{
    [MobClick startWithAppkey:umengAppKey];
    [UMOnlineConfig updateOnlineConfigWithAppkey:umengAppKey];
    
    if ([MobClick isJailbroken])
        NSLog(@"设备越狱");
    else
        NSLog(@"设备正常");
    
    if(um_on_off((char*)"NewVerPush_1.2") == 1)
//        [MobClick checkUpdate];
    
    [UMFeedback setAppkey:umengAppKey];
    
    umCode();
    
    const char* temp_str = um_on_off_str((char*)"Acti_code");
    if (UserDefault::getInstance()->getStringForKey("ActiCode").compare(temp_str) != 0)
    {
        MyApp->saveGameData_str("ActiCode", temp_str);
        MyApp->gotDuiHuan = false;
        MyApp->saveGameData_bool("gotDuiHuan", MyApp->gotDuiHuan);
    }
    
    
    CCLOG("----- getInfoPlist = %s",getInfoPlist(0));
    const char* version_str = getInfoPlist(0);
    if (UserDefault::getInstance()->getStringForKey("GameVersion").compare(version_str) != 0)
    {
        CCLOG("**************************** new version ********************************");
        MyApp->saveGameData_str("GameVersion", version_str);
        MyApp->game_px = false;
        MyApp->saveGameData_bool("game_px", MyApp->game_px);
    }

}

const char* getInfoPlist(int index)
{
    if(index == 0)
    {
        NSString *value = [[NSBundle mainBundle]objectForInfoDictionaryKey:@"CFBundleShortVersionString"];
        return [value cStringUsingEncoding:NSUTF8StringEncoding];
    }
    return "";
}

void checkFeedback()
{
    [[UMFeedback sharedInstance] get:^(NSError *error)
    {
        UMFeedback *fb = [UMFeedback sharedInstance];
        if (error != nil)
        {
        }
        else {
            NSLog(@"-------checkFeedback------%@", fb.theNewReplies);
            int count = (int)[fb.theNewReplies count];
            if (count > 0)
            {
                MyApp->saveGameData_bool("FeedbackNew", true);
            }
            //            if ([reply[@"type"] isEqualToString:@"dev_reply"]){
            //                NSLog(@"开发者回复");
            //            }else{
            //                NSLog(@"用户回复");
            //            }
        }
    }];
}

void showFeedback()
{
    UIViewController *vc = [[[UIApplication sharedApplication] keyWindow] rootViewController];
    [vc presentModalViewController:[UMFeedback feedbackModalViewController]
                          animated:YES];
}

void loopShow()
{
    [[GameKitHelper sharedHelper] showLeaderboard];
}
void uploadLoop1(int num)
{
    GameKitHelper *gkHelper = [GameKitHelper sharedHelper];
    [gkHelper submitScore:num category:LoopID0];
}
void uploadLoop2(int num)
{
//    GameKitHelper *gkHelper = [GameKitHelper sharedHelper];
//    [gkHelper submitScore:num category:LoopID1];
}
void uploadLoop3(int num)
{
//    GameKitHelper *gkHelper = [GameKitHelper sharedHelper];
//    [gkHelper submitScore:num category:LoopID2];
}
void uploadLoop4(int num)
{
//    GameKitHelper *gkHelper = [GameKitHelper sharedHelper];
//    [gkHelper submitScore:num category:LoopID3];
}
void uploadLoop5(int num)
{
//    GameKitHelper *gkHelper = [GameKitHelper sharedHelper];
//    [gkHelper submitScore:num category:LoopID4];
}
void CCLoadScoreWall()
{
    
}

void CCConsumeScoreWall()
{
    
}
void CCShowScoreWall(const char * pszWallId)
{

}


void CCEveryDay(int time_flag)
{
    UILocalNotification *notification=[[UILocalNotification alloc] init];
    
    notification.timeZone=[NSTimeZone defaultTimeZone]; //是否根据时区改变而改变
    notification.repeatInterval = kCFCalendarUnitDay;    //例如每周激发的单位，NSWeekCalendarUnit，如果不设置的话，将不会重复激发
    notification.applicationIconBadgeNumber = 1; //显示在应用图标右上角的数字
    notification.alertAction = @"知道了"; //作为提醒中动作按钮上的文字
    notification.alertLaunchImage=@"没空啦！"; //是在用户点击提醒框中动作按钮（“View”）时，等待应用加载时显示的图片，这个将替代应用原本设置的加载图片
    
    int year;
    int mouth;
    int day;
    NSString * date_now_string;
    NSDate * date_now=[NSDate date];
    
    NSDateFormatter * dateFormatter=[[NSDateFormatter alloc] init];
    
    [dateFormatter setDateFormat:@"yyyy"];
    NSString * years_string = [dateFormatter stringFromDate:date_now];
    year=[years_string intValue];
    
    
    //月
    [dateFormatter setDateFormat:@"MM"];
    NSString * mouth_string = [dateFormatter stringFromDate:date_now];
    mouth=[mouth_string intValue];
    
    //日
    [dateFormatter setDateFormat:@"dd"];
    NSString * day_string = [dateFormatter stringFromDate:date_now];
    day=[day_string intValue];
    
    int MMM[12] ={31,28,31,30,31,30,31,31,30,31,30,31};
    
//    int time_flag = 21;
//    
//    NSString *value0 = [UMOnlineConfig getConfigParams:@"Notification"];
//    if (value0) {
//        time_flag = [value0 intValue];
//    }
    
    if(day == MMM[mouth-1])
    {
        date_now_string=[NSString stringWithFormat:@"%d-%d-%d %d:%d:%d",year,mouth+1,1,time_flag,00,00];
        NSLog(@"2----%@",date_now_string);
    }
    else{
        date_now_string=[NSString stringWithFormat:@"%d-%d-%d %d:%d:%d",year,mouth,day+1,time_flag,00,00];
        NSLog(@"2----%@",date_now_string);
    }
    
    [dateFormatter setDateFormat: @"yyyy-MM-dd HH:mm:ss"];
    date_now= [dateFormatter dateFromString:date_now_string];
    
    NSLog(@"1----%@",date_now);
    
    [dateFormatter release];
    
    notification.fireDate = date_now; //激发时的确切时间
    
    if(time_flag == 9)
        notification.alertBody = @"快来领取每日奖励哦！";
    if(time_flag == 21)
        notification.alertBody = @"别忘完成每日任务和领取奖励哦！";
    
    [notification setSoundName:UILocalNotificationDefaultSoundName]; //提醒音效
    [[UIApplication sharedApplication] scheduleLocalNotification:notification]; //最后需要在系统Notification处理队列中登记已设置完的UILocalNotification对象
}


void CCSendMyMessage()
{
    [UIApplication sharedApplication].applicationIconBadgeNumber = 0;
    [[UIApplication sharedApplication] cancelAllLocalNotifications];
    
    //每日提醒
    CCEveryDay(9);
    CCEveryDay(21);
    // 立即生效激活   [[UIApplication sharedApplication] presentLocalNotificationNow:notification];
    
}


NS_CC_END
