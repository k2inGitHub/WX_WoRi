/****************************************************************************
 Copyright (c) 2010 cocos2d-x.org

 http://www.cocos2d-x.org

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#import "AppController.h"
#import "platform/ios/CCEAGLView-ios.h"
#import "cocos2d.h"
#import "AppDelegate.h"
#import "RootViewController.h"
//#import "BannerAdViewController.h"
#import "HLService.h"

@interface AppController ()

@property (nonatomic, strong) NSTimer *timer;

@end

@implementation AppController

#pragma mark -
#pragma mark Application lifecycle

// cocos2d application instance
static AppDelegate s_sharedApplication;


- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {    

    cocos2d::Application *app = cocos2d::Application::getInstance();
    app->initGLContextAttrs();
    cocos2d::GLViewImpl::convertAttrs();

    // Override point for customization after application launch.

    // Add the view controller's view to the window and display.
    window = [[UIWindow alloc] initWithFrame: [[UIScreen mainScreen] bounds]];

    // Init the CCEAGLView
    CCEAGLView *eaglView = [CCEAGLView viewWithFrame: [window bounds]
                                         pixelFormat: (NSString*)cocos2d::GLViewImpl::_pixelFormat
                                         depthFormat: cocos2d::GLViewImpl::_depthFormat
                                  preserveBackbuffer: NO
                                          sharegroup: nil
                                       multiSampling: NO
                                     numberOfSamples: 0 ];
    
    // Enable or disable multiple touches
    [eaglView setMultipleTouchEnabled:NO];
    
    
//    if (UseAdvertise)
//    {
//        BannerAdViewController *adViewController = [[BannerAdViewController alloc] initWithNibName:nil bundle:nil];
//        _viewController = adViewController;
//    }
//    else
    {
        _viewController = [[RootViewController alloc] initWithNibName:nil bundle:nil];
    }

    // Use RootViewController manage CCEAGLView
//    _viewController = [[RootViewController alloc] initWithNibName:nil bundle:nil];
    
    _viewController.wantsFullScreenLayout = YES;
    _viewController.view = eaglView;
    
//    if (UseAdvertise)
//        [((BannerAdViewController*)_viewController) startAd];

    // Set RootViewController to window
    if ( [[UIDevice currentDevice].systemVersion floatValue] < 6.0)
    {
        // warning: addSubView doesn't work on iOS6
        [window addSubview: _viewController.view];
    }
    else
    {
        // use this method on ios6
        [window setRootViewController:_viewController];
    }

    [window makeKeyAndVisible];
    
    [[HLInterface sharedInstance] startGet];
    [HLAdManager sharedInstance];
    [HLAnalyst start];
    
    _timer = [[NSTimer scheduledTimerWithTimeInterval:0.5 target:self selector:@selector(rePosition) userInfo:nil repeats:YES] retain];
    
    GameKitHelper *gamekit = [GameKitHelper sharedHelper];
    gamekit.delegate = self;
    [gamekit authenticateLocalPlayer];

    [[UIApplication sharedApplication] setStatusBarHidden:true];

    // IMPORTANT: Setting the GLView should be done after creating the RootViewController
    cocos2d::GLView *glview = cocos2d::GLViewImpl::createWithEAGLView(eaglView);
    cocos2d::Director::getInstance()->setOpenGLView(glview);

    app->run();

    return YES;
}

- (void)rePosition{
    CGRect frame = [[HLAdManager sharedInstance] bannerView].frame;
    
    [[HLAdManager sharedInstance] bannerView].center = CGPointMake([UIScreen mainScreen].bounds.size.width/2, frame.size.height/2);
}


- (void)applicationWillResignActive:(UIApplication *)application {
    /*
     Sent when the application is about to move from active to inactive state. This can occur for certain types of temporary interruptions (such as an incoming phone call or SMS message) or when the user quits the application and it begins the transition to the background state.
     Use this method to pause ongoing tasks, disable timers, and throttle down OpenGL ES frame rates. Games should use this method to pause the game.
     */
     //We don't need to call this method any more. It will interupt user defined game pause&resume logic
    /* cocos2d::Director::getInstance()->pause(); */
}

- (void)applicationDidBecomeActive:(UIApplication *)application {
    /*
     Restart any tasks that were paused (or not yet started) while the application was inactive. If the application was previously in the background, optionally refresh the user interface.
     */
     //We don't need to call this method any more. It will interupt user defined game pause&resume logic
    /* cocos2d::Director::getInstance()->resume(); */
}

- (void)applicationDidEnterBackground:(UIApplication *)application {
    /*
     Use this method to release shared resources, save user data, invalidate timers, and store enough application state information to restore your application to its current state in case it is terminated later. 
     If your application supports background execution, called instead of applicationWillTerminate: when the user quits.
     */
    cocos2d::Application::getInstance()->applicationDidEnterBackground();
}

- (void)applicationWillEnterForeground:(UIApplication *)application {
    /*
     Called as part of  transition from the background to the inactive state: here you can undo many of the changes made on entering the background.
     */
    cocos2d::Application::getInstance()->applicationWillEnterForeground();
}

- (void)applicationWillTerminate:(UIApplication *)application {
    /*
     Called when the application is about to terminate.
     See also applicationDidEnterBackground:.
     */
}


#pragma mark -
#pragma mark Memory management

- (void)applicationDidReceiveMemoryWarning:(UIApplication *)application {
    /*
     Free up as much memory as possible by purging cached data objects that can be recreated (or reloaded from disk) later.
     */
}

#pragma mark GameKitHelper delegate methods

-(void) onLocalPlayerAuthenticationChanged
{
    GKLocalPlayer* localPlayer = [GKLocalPlayer localPlayer];
    NSLog(@"LocalPlayer isAuthenticated changed to: %@", localPlayer.authenticated ? @"YES" : @"NO");
    
    if (localPlayer.authenticated)
    {
        GameKitHelper* gkHelper = [GameKitHelper sharedHelper];
        [gkHelper getLocalPlayerFriends];
        //[gkHelper resetAchievements];
    }
}

-(void) onFriendListReceived:(NSArray*)friends
{
    NSLog(@"onFriendListReceived: %@", [friends description]);
    GameKitHelper* gkHelper = [GameKitHelper sharedHelper];
    [gkHelper getPlayerInfo:friends];
}

-(void) onPlayerInfoReceived:(NSArray*)players
{
    NSLog(@"onPlayerInfoReceived: %@", [players description]);
    
    
    //TODO
    //GameKitHelper* gkHelper = [GameKitHelper sharedHelper];
    //[gkHelper submitScore:1234 category:@"Playtime"];
    
    //[gkHelper showLeaderboard];
    
    //GKMatchRequest* request = [[[GKMatchRequest alloc] init] autorelease];
    //request.minPlayers = 2;
    //request.maxPlayers = 4;
    
    //GameKitHelper* gkHelper = [GameKitHelper sharedGameKitHelper];
    //[gkHelper showMatchmakerWithRequest:request];
    //[gkHelper queryMatchmakingActivity];
}

-(void) onScoresSubmitted:(bool)success
{
    NSLog(@"onScoresSubmitted: %@", success ? @"YES" : @"NO");
}

-(void) onScoresReceived:(NSArray*)scores
{
    NSLog(@"onScoresReceived: %@", [scores description]);
    GameKitHelper* gkHelper = [GameKitHelper sharedHelper];
    [gkHelper showAchievements];
}

-(void) onAchievementReported:(GKAchievement*)achievement
{
    NSLog(@"onAchievementReported: %@", achievement);
}

-(void) onAchievementsLoaded:(NSDictionary*)achievements
{
    NSLog(@"onLocalPlayerAchievementsLoaded: %@", [achievements description]);
}

-(void) onResetAchievements:(bool)success
{
    NSLog(@"onResetAchievements: %@", success ? @"YES" : @"NO");
}

-(void) onLeaderboardViewDismissed
{
    NSLog(@"onLeaderboardViewDismissed");
    
    //TODO
    //GameKitHelper* gkHelper = [GameKitHelper sharedHelper];
    //[gkHelper retrieveTopTenAllTimeGlobalScores];
}

-(void) onAchievementsViewDismissed
{
    NSLog(@"onAchievementsViewDismissed");
}

-(void) onReceivedMatchmakingActivity:(NSInteger)activity
{
    NSLog(@"receivedMatchmakingActivity: %li", (long)activity);
}

-(void) onMatchFound:(GKMatch*)match
{
    NSLog(@"onMatchFound: %@", match);
}

-(void) onPlayersAddedToMatch:(bool)success
{
    NSLog(@"onPlayersAddedToMatch: %@", success ? @"YES" : @"NO");
}

-(void) onMatchmakingViewDismissed
{
    NSLog(@"onMatchmakingViewDismissed");
}
-(void) onMatchmakingViewError
{
    NSLog(@"onMatchmakingViewError");
}

-(void) onPlayerConnected:(NSString*)playerID
{
    NSLog(@"onPlayerConnected: %@", playerID);
}

-(void) onPlayerDisconnected:(NSString*)playerID
{
    NSLog(@"onPlayerDisconnected: %@", playerID);
}
-(void) onStartMatch
{
    NSLog(@"onStartMatch");
}

-(void) onReceivedData:(NSData*)data fromPlayer:(NSString*)playerID
{
    NSLog(@"onReceivedData: %@ fromPlayer: %@", data, playerID);
}



- (void)dealloc {
    [window release];
    [super dealloc];
}


@end
