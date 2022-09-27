#import <UIKit/UIKit.h>

@interface ESTextFieldDelegate : NSObject <UITextFieldDelegate> {
    bool _textOk;
}

@property bool textOk;

- (ESTextFieldDelegate *)init;
@end
