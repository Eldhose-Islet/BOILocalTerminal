#import "ESApiTextFieldDelegate.h"

@implementation ESApiTextFieldDelegate

#define MAX_PASTE_LEN 64

- (ESApiTextFieldDelegate *)initWithValueRestrictions:(ESValueQuestionData *)data
{
    if (self = [super init]) {
        _data = data;
    }
    return self;
}

- (ESApiTextFieldDelegate *)init
{
    return [self initWithValueRestrictions:NULL];
}

- (BOOL)textFieldShouldEndEditing:(UITextField *)textField {
    NSString *enteredText1 = [textField text];
    const char *enteredText2 = [enteredText1 cStringUsingEncoding:NSUTF8StringEncoding];
    const size_t enteredTextLen = strlen(enteredText2);
    if (NULL == _data)
    {
        return YES;
    }
    if (((_data.maxLen >= enteredTextLen) && (_data.minLen <= enteredTextLen)))
    {
        if ((NULL != _data.userData) && (0 < _data.userDataLen))
        {
            memset(_data.userData, 0, _data.userDataLen);
            strncpy(_data.userData, enteredText2, _data.userDataLen - 1);
        }
        _textOk = true;
        return YES;
    }
    textField.text = @"";
    return NO;
}

- (BOOL)textField:(UITextField *)textField shouldChangeCharactersInRange:(NSRange)range replacementString:(NSString *)replacement {
    if ((NULL == replacement)
        || (0 == replacement.length))
    {
        return YES;
    }
    if (MAX_PASTE_LEN < replacement.length)
    {
        return NO;
    }
    if ((NULL == _data)
        || (NULL == _data.isCharacterAllowed))
    {
        return YES;
    }
    const char * result = [replacement cStringUsingEncoding:_data.apiTextEncoding];
    if ((NULL == result)
        || (0 == result[0]))
    {
        return NO;
    }
    unsigned long cnt = 0;
    unsigned long result_len = strlen(result);
    while (cnt < result_len)
    {
        if (!_data.isCharacterAllowed(result[cnt]))
        {
            return NO;
        }
        cnt++;
    }
    return YES;
}
@end
