#import "ESDummySelectionDelegate.h"

@implementation ESDummySelectionDelegate

- (ESDummySelectionDelegate *)initWithMaxValue:()data
{
    if (self = [super init]) {
        _data = data;
    }
    return self;
}

- (ESDummySelectionDelegate *)init
{
    return [self initWithMaxValue:NULL];
}

- (BOOL)textFieldShouldBeginEditing:(UITextField *)textField {
    return YES;
}

- (BOOL)textFieldShouldEndEditing:(UITextField *)textField {
    NSString *enteredText1 = [textField text];
    const char *enteredText2 = [enteredText1 cStringUsingEncoding:NSUTF8StringEncoding];
    if (NULL == _data)
    {
        return YES;
    }
    const int retval = (int)strtoimax(enteredText2, NULL, 0);
    if ((0 < retval) && (_data.choicesSize >= retval))
    {
        if (NULL != _data.userChoice)
        {
            *(_data.userChoice) = retval;
        }
        _textOk = true;
        return YES;
    }
    textField.text = @"";
    return NO;
}

- (BOOL)textField:(UITextField *)textField shouldChangeCharactersInRange:(NSRange)range replacementString:(NSString *)string {
    // workaround for entering single number
     const char * cstr = [string cStringUsingEncoding:NSUTF8StringEncoding];
     if ((NULL == cstr) || (0 == cstr[0]) || (NULL == _data))
     {
         return YES;
     }
     if (0 == cstr[1]) // TO DO: UTF-8 !!!
     {
         if (isdigit((int)cstr[0]))
         {
             return YES;
         }
     }
     return NO;
}
@end
