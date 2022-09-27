#import "ESAsynchResp.h"

@implementation ESAsynchResp

@synthesize args = _args;

- (ESAsynchResp *)init
{
    if (self = [super init]) {
        _condition_var = [[NSCondition alloc] init];
        _state = 0;
    }
    return self;
}

- (void)send_response {
    [_condition_var lock];
    _state = 1;
    [_condition_var signal];
    [_condition_var unlock];
}

- (void)response_wait {
    [_condition_var lock];
    if (0 == _state)
    {
        [_condition_var wait];
    }
    [_condition_var unlock];
}
@end
