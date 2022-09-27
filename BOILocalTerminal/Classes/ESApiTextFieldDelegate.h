#import "ESTextFieldDelegate.h"
#import "ESValueQuestionData.h"

@interface ESApiTextFieldDelegate : ESTextFieldDelegate {
    ESValueQuestionData * _data;
}

@property ESValueQuestionData * data;

- (ESApiTextFieldDelegate *)initWithValueRestrictions:(ESValueQuestionData *)data;
- (ESApiTextFieldDelegate *)init;
@end
