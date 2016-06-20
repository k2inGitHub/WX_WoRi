

#import "InserAds.h"
#import "cocos2d.h"
#import "BusinessParameter.h"
#import "FX_App.h"

@implementation InserAds
@synthesize presenting;

-(id)initAds {
    
    self = [super init];
    return self;
}
-(void)ppjj
{
    UIAlertView *alertView = [[[UIAlertView alloc] initWithTitle:NULL
                                                         message:@"喜欢我们的游戏吗？\n到App Store给游戏5星评价！"
                                                        delegate:self
                                               cancelButtonTitle:@"我要评价"
                                               otherButtonTitles:@"知道了", nil] autorelease];
    [alertView show];
}
-(void)present
{
    presenting = true;
}

-(void)alertView:(UIAlertView *)alertView clickedButtonAtIndex:(NSInteger)buttonIndex
{
    switch (buttonIndex) {
        case 1:
//            NSLog(@"0");
			break;
		case 0:
//            NSLog(@"1");
            NSString *url = [NSString stringWithFormat:@"itms-apps://itunes.apple.com/WebObjects/MZStore.woa/wa/viewContentsUserReviews?type=Purple+Software&id=%@", AppId];
            [[UIApplication sharedApplication] openURL:[NSURL URLWithString:url]];
            
            MyApp->game_px = true;
            MyApp->saveGameData_bool("game_px", MyApp->game_px);
            
//            MyApp->info_total_diamond+=30;
//            MyApp->saveInfoData(60);

			break;

	}
}
@end