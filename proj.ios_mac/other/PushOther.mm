

#import "PushOther.h"
#import "cocos2d.h"
#import "BusinessParameter.h"
#import "FX_App.h"
#import "MobClick.h"
#import "ScoreWallCommon.h"

@implementation PushOther

-(id)initPush
{
    self = [super init];
    return self;
}
-(void)pushKKK
{
    BBClickEvent((char*)"UIAlertViewApperCount");
    UIAlertView *alertView = [[[UIAlertView alloc] initWithTitle:NULL
                                                         message:[NSString stringWithCString:MyApp->push_content.c_str() encoding:NSUTF8StringEncoding]
                                                        delegate:self
                                               cancelButtonTitle:@"取消"
                                               otherButtonTitles:@"确定", nil] autorelease];
    [alertView show];
}

-(void)alertView:(UIAlertView *)alertView clickedButtonAtIndex:(NSInteger)buttonIndex
{
    switch (buttonIndex)
    {
        case 0:
            //            NSLog(@"0");
            break;
        case 1:
            BBClickEvent((char*)"ClickOk");
            
            [MobClick updateOnlineConfig];
            NSString *value = [MobClick getConfigParams:@"adress1.5"];
            
            NSURL *appStoreUrl = [NSURL URLWithString:value];
            [[UIApplication sharedApplication] openURL:appStoreUrl];
            
            break;
    }
}
@end