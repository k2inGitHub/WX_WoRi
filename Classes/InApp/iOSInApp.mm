
#import "iOSInApp.h"
#import "MBProgressHUD.h"
//#import "VerificationController.h"
#include "cocos2d.h"

@implementation iOSInApp


#pragma mark -
#pragma mark SKProductsRequestDelegate methods

- (void)requestProUpgradeProductData:(NSString*)defaultProductId
{
    NSSet *productIdentifiers = [NSSet setWithObject:defaultProductId];
    productsRequest = [[[SKProductsRequest alloc] initWithProductIdentifiers:productIdentifiers] autorelease];
    productsRequest.delegate = self;
    [productsRequest start];
    
    // we will release the request object in the delegate callback
}

- (void)productsRequest:(SKProductsRequest *)request didReceiveResponse:(SKProductsResponse *)response
{
    NSArray *products = response.products;
    
    proUpgradeProduct = [products count] == 1 ? [[products objectAtIndex:0] retain] : nil;
    if (proUpgradeProduct)
    {
        NSLog(@"Product title: %@" , proUpgradeProduct.localizedTitle);
        NSLog(@"Product description: %@" , proUpgradeProduct.localizedDescription);
        NSLog(@"Product price: %@" , proUpgradeProduct.price);
        NSLog(@"Product id: %@" , proUpgradeProduct.productIdentifier);
    }
    
    for (NSString *invalidProductId in response.invalidProductIdentifiers)
    {
        NSLog(@"Invalid product id: %@" , invalidProductId);
    }
    
    // finally release the reqest we alloc/init’ed in requestProUpgradeProductData
    //[productsRequest release];
    
    [[NSNotificationCenter defaultCenter] postNotificationName:kInAppPurchaseManagerProductsFetchedNotification object:self userInfo:nil];
}


#pragma -
#pragma Public methods

//
// call this method once on startup
//
- (void)loadStore:(NSString*)defaultProductId
{

    // restarts any purchases if they were interrupted last time the app was open
    [[SKPaymentQueue defaultQueue] addTransactionObserver:self];
    
    // get the product description (defined in early sections)
    [self requestProUpgradeProductData:defaultProductId];
}


//
// call this before making a purchase
//
- (bool)canMakePurchases
{

    return [SKPaymentQueue canMakePayments];
}


-(void)purchaseProduct:(NSString*)productId
{

    SKPayment *payment = [SKPayment paymentWithProductIdentifier:productId];
    [[SKPaymentQueue defaultQueue] addPayment:payment];
    
    [MBProgressHUD showHUDAddedToWindow:
     [UIApplication sharedApplication].keyWindow animated:YES];
}


-(void)restoreProducts
{
    NSLog(@"..........................restoreProducts.................................");
    [[SKPaymentQueue defaultQueue] addTransactionObserver:self];

    [[SKPaymentQueue defaultQueue] restoreCompletedTransactions];
    
    [MBProgressHUD showHUDAddedToWindow:[UIApplication sharedApplication].keyWindow animated:YES];
    
}


#pragma -
#pragma Purchase helpers

- (void)paymentQueue:(SKPaymentQueue *)queue restoreCompletedTransactionsFailedWithError:(NSError *)error{
    
    
    NSLog(@"..........................12312123.................................");
    [MBProgressHUD hideHUDForView:[UIApplication sharedApplication].keyWindow animated:YES];
    
}
-(void)paymentQueueRestoreCompletedTransactionsFinished:(SKPaymentTransaction *)queue
{
    NSLog(@"..........................44444444.................................");
    [MBProgressHUD hideHUDForView:[UIApplication sharedApplication].keyWindow animated:YES];
    cocos2d::__NotificationCenter::getInstance()->postNotification([@"Q2" cStringUsingEncoding:NSASCIIStringEncoding], NULL);


}
//
// saves a record of the transaction by storing the receipt to disk
//
- (void)recordTransaction:(SKPaymentTransaction *)transaction
{
    NSLog(@"..........................recordTransaction.................................");
    [MBProgressHUD hideHUDForView:[UIApplication sharedApplication].keyWindow animated:YES];

    [[NSUserDefaults standardUserDefaults] setValue:transaction.transactionReceipt forKey:@"proUpgradeTransactionReceipt" ];
    [[NSUserDefaults standardUserDefaults] synchronize];
    
    NSLog(@"%@",transaction.payment.productIdentifier);
    
    cocos2d::__NotificationCenter::getInstance()->postNotification([@"Q1" cStringUsingEncoding:NSASCIIStringEncoding], cocos2d::__String::create([transaction.payment.productIdentifier cStringUsingEncoding:NSASCIIStringEncoding]));
    

}

//
// enable pro features
//
- (void)provideContent:(NSString *)productId
{
    NSLog(@"..........................1成功.................................");
    [MBProgressHUD hideHUDForView:[UIApplication sharedApplication].keyWindow animated:YES];

    [[NSUserDefaults standardUserDefaults] setBool:YES forKey:@"isProUpgradePurchased" ];
    [[NSUserDefaults standardUserDefaults] synchronize];
    
    cocos2d::__NotificationCenter::getInstance()->postNotification([kProductPurchasedNotification cStringUsingEncoding:NSASCIIStringEncoding], cocos2d::__String::create([productId cStringUsingEncoding:NSASCIIStringEncoding]));
    
    NSLog(@"%s",[productId cStringUsingEncoding:NSASCIIStringEncoding]);
    

}

//
// removes the transaction from the queue and posts a notification with the transaction result
//
- (void)finishTransaction:(SKPaymentTransaction *)transaction wasSuccessful:(BOOL)wasSuccessful
{
    NSLog(@"..........................2成功.................................");
    // remove the transaction from the payment queue.
    [[SKPaymentQueue defaultQueue] finishTransaction:transaction];
    
    NSDictionary *userInfo = [NSDictionary dictionaryWithObjectsAndKeys:transaction, @"transaction" , nil];
    if (wasSuccessful)
    {
        // send out a notification that we’ve finished the transaction
        [[NSNotificationCenter defaultCenter] postNotificationName:kInAppPurchaseManagerTransactionSucceededNotification object:self userInfo:userInfo];
    }
    else
    {
        // send out a notification for the failed transaction
        [[NSNotificationCenter defaultCenter] postNotificationName:kInAppPurchaseManagerTransactionFailedNotification object:self userInfo:userInfo];
    }
}

//
// called when the transaction was successful
//
- (void)completeTransaction:(SKPaymentTransaction *)transaction
{
    NSLog(@"..........................3成功.................................");
//    [self recordTransaction:transaction];
    [self provideContent:transaction.payment.productIdentifier];
    [self finishTransaction:transaction wasSuccessful:YES];
}

//
// called when a transaction has been restored and and successfully completed
//
- (void)restoreTransaction:(SKPaymentTransaction *)transaction
{
    NSLog(@"..........................4成功.................................");
    [self recordTransaction:transaction.originalTransaction];
//    [self provideContent:transaction.originalTransaction.payment.productIdentifier];
    [self finishTransaction:transaction wasSuccessful:YES];
}

//
// called when a transaction has failed
//
- (void)failedTransaction:(SKPaymentTransaction *)transaction
{
    NSLog(@"..........................failedTransaction.................................");

    if (transaction.error.code != SKErrorPaymentCancelled)
    {
        NSLog(@"..........................failedTransaction11.................................");
        // error!
        [self finishTransaction:transaction wasSuccessful:NO];
        [MBProgressHUD hideHUDForView: [UIApplication sharedApplication].keyWindow animated:YES];//TODO:
        
        cocos2d::__NotificationCenter::getInstance()->postNotification([kProductPurchaseFailedNotification cStringUsingEncoding:NSASCIIStringEncoding], NULL);
    }
    else
    {
        NSLog(@"..........................failedTransaction22.................................");
        [MBProgressHUD hideHUDForView: [UIApplication sharedApplication].keyWindow animated:YES];
        // this is fine, the user just cancelled, so don’t notify
        [[SKPaymentQueue defaultQueue] finishTransaction:transaction];
        cocos2d::__NotificationCenter::getInstance()->postNotification([kProductPurchaseFailedNotification cStringUsingEncoding:NSASCIIStringEncoding], NULL);

    }
    
}


#pragma mark -
#pragma mark SKPaymentTransactionObserver methods

//
// called when the transaction status is updated
//
- (void)paymentQueue:(SKPaymentQueue *)queue updatedTransactions:(NSArray *)transactions
{
    
    NSLog(@"..........................paymentQueue.................................");
    for (SKPaymentTransaction *transaction in transactions)
    {
        switch (transaction.transactionState)
        {
            case SKPaymentTransactionStatePurchased:
//                [[VerificationController sharedInstance] verifyPurchase:transaction];
                [self completeTransaction:transaction];
                [MBProgressHUD hideHUDForView:[UIApplication sharedApplication].keyWindow animated:YES];
                break;
            case SKPaymentTransactionStateFailed:
                [self failedTransaction:transaction];
                [MBProgressHUD hideHUDForView:[UIApplication sharedApplication].keyWindow animated:YES];
                break;
            case SKPaymentTransactionStateRestored:
                //[[VerificationController sharedInstance] verifyPurchase:transaction];
                [self restoreTransaction:transaction];
                [MBProgressHUD hideHUDForView:[UIApplication sharedApplication].keyWindow animated:YES];
                break;
            default:
                break;
        }
    }
}
#pragma mark -
#pragma mark singleton

static iOSInApp *_sharedInAppManager = nil;

+ (iOSInApp *)sharedInstance
{
	@synchronized([iOSInApp class])
	{
		if (!_sharedInAppManager)
			[[self alloc] init];
		
		return _sharedInAppManager;
	}
	return nil;
}

+(id)alloc
{
	@synchronized([iOSInApp class])
	{
		NSAssert(_sharedInAppManager == nil, @"Attempted to allocate a second instance of a singleton.");
		_sharedInAppManager = [super alloc];
		return _sharedInAppManager;
	}
	return nil;
}
@end

