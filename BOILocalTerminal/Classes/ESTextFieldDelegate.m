#import "ESTextFieldDelegate.h"

@implementation ESTextFieldDelegate

@synthesize textOk = _textOk;

- (ESTextFieldDelegate *)init
{
    if (self = [super init]) {
        _textOk = false;
    }
    return self;
}

- (BOOL)textFieldShouldBeginEditing:(UITextField *)textField {
    return YES;
}

- (BOOL)textFieldShouldEndEditing:(UITextField *)textField {
    _textOk = true;
    return YES;
}

- (BOOL)textField:(UITextField *)textField shouldChangeCharactersInRange:(NSRange)range replacementString:(NSString *)string {
    return YES;
}
@end
