#import "ESValueQuestionData.h"

@implementation ESValueQuestionData

- (ESValueQuestionData *)init
{
    if (self = [super init]) {
        _userData = NULL;
        _userDataLen = 0;
        _maxLen = 0;
        _minLen = 0;
        _isCharacterAllowed = NULL;
        _apiTextEncoding = 0;
    }
    return self;
}
@end
