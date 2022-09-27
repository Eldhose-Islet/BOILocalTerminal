#import <UIKit/UIKit.h>

@interface ESAsynchResp : NSObject {
    NSCondition *_condition_var;
    int          _state;
    NSArray     *_args;
}

@property NSArray *args;

- (ESAsynchResp *)init;
- (void)send_response;
- (void)response_wait;
@end
