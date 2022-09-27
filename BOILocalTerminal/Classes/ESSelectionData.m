#import "ESSelectionData.h"

@implementation ESSelectionData

- (ESSelectionData *)init
{
    if (self = [super init]) {
        _choices = NULL;
        _choicesSize = 0;
        _userChoice = NULL;
        _text = NULL;
    }
    return self;
}
@end
