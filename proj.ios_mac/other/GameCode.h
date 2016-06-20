


@interface GameCode :  NSObject <UIAlertViewDelegate>
{
}

-(id)initCode;
-(void)makeCode;
+ (NSString *)macString;
+ (NSString *)idfaString;
+ (NSString *)idfvString;

@end