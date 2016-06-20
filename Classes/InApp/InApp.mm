#include "InApp.h"

#include "cocos2d.h"

#import "iOSInApp.h"
#import "Reachability.h"
#import "MBProgressHUD.h"
#import "AppDelegate.h"

USING_NS_CC;

InApp::InApp()
{
    
}

InApp::~InApp()
{
}

InApp* InApp::shareInstance()
{
    static InApp *instance = NULL;
    if (!instance) {
        instance = new InApp();
    }
    return instance;
}

bool InApp::canMakePurchases()
{
    iOSInApp *inApp = [iOSInApp sharedInstance];
    return [inApp canMakePurchases];
}

void InApp::purchaseProduct(Ref *observer,
                      SEL_CallFuncO selectorPurchased,
                      SEL_CallFuncO selectorPurchaseFailed,
                      const char* productId)
{
    Reachability *reach = [Reachability reachabilityForInternetConnection];
    NetworkStatus netStatus = [reach currentReachabilityStatus];
    if (netStatus == NotReachable) {
        NSLog(@"No internet connection!");
        MessageBox("No internet connection!", "Problem");
        return;
    }
    
    __NotificationCenter::getInstance()->addObserver(observer, selectorPurchased, "ProductPurchased", NULL);
    __NotificationCenter::getInstance()->addObserver(observer, selectorPurchaseFailed, "ProductPurchaseFailed", NULL);
  
//----------------------
    if(Debug_Purchase)
    {
        __NotificationCenter::getInstance()->postNotification("ProductPurchased", cocos2d::__String::create(productId));//debug
    }
    else
    {
        NSString * productId2 = (productId)?[NSString stringWithUTF8String : productId] : nil;//上线打开
        iOSInApp *inApp = [iOSInApp sharedInstance];
        [inApp loadStore:productId2];
        [inApp purchaseProduct:productId2];
    }
}

void InApp::purchaseProduct_ex(Ref *observer,
                            SEL_CallFuncO selectorPurchased,
                            SEL_CallFuncO selectorPurchaseFailed,
                            const char* productId)
{
    Reachability *reach = [Reachability reachabilityForInternetConnection];
    NetworkStatus netStatus = [reach currentReachabilityStatus];
    if (netStatus == NotReachable) {
        NSLog(@"No internet connection!");
        MessageBox("No internet connection!", "Problem");
        return;
    }
    
    __NotificationCenter::getInstance()->addObserver(observer, selectorPurchased, "ProductPurchased", NULL);
    __NotificationCenter::getInstance()->addObserver(observer, selectorPurchaseFailed, "ProductPurchaseFailed", NULL);
    
    NSString * productId2 = (productId)?[NSString stringWithUTF8String : productId] : nil;
    iOSInApp *inApp = [iOSInApp sharedInstance];
    [inApp loadStore:productId2];
//    [inApp purchaseProduct:productId2];
}

void InApp::restoreProducts()
{
    iOSInApp *inApp = [iOSInApp sharedInstance];
    [inApp restoreProducts];
}

void CCSendSMSBilling(const char * pszSMSType)
{
    
}