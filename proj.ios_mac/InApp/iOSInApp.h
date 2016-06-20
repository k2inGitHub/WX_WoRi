

#import <Foundation/Foundation.h>
#import <StoreKit/StoreKit.h>

// add a couple notifications sent out when the transaction completes
#define kInAppPurchaseManagerProductsFetchedNotification @"kInAppPurchaseManagerProductsFetchedNotification"
#define kInAppPurchaseManagerTransactionFailedNotification @"kInAppPurchaseManagerTransactionFailedNotification"
#define kInAppPurchaseManagerTransactionSucceededNotification @"kInAppPurchaseManagerTransactionSucceededNotification"

#define kProductPurchasedNotification       @"ProductPurchased"
#define kProductPurchaseFailedNotification  @"ProductPurchaseFailed"

/**
@brief    苹果商店内置收费.
*/
@interface iOSInApp : NSObject <SKProductsRequestDelegate, SKPaymentTransactionObserver>
{
    SKProduct *proUpgradeProduct;
    SKProductsRequest *productsRequest;
}

+(iOSInApp *)sharedInstance;

-(bool)canMakePurchases;
-(void)loadStore:(NSString*)defaultProductId;
-(void)purchaseProduct:(NSString*)productId;
-(void)restoreProducts;
-(void)provideContent:(NSString*)productId;

@end

