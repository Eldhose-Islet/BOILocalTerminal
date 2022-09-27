#import <UIKit/UIKit.h>

@interface ESSelectionData : NSObject {
    const char** _choices;
    size_t _choicesSize;
    uint32_t* _userChoice;
    const char* _text;
}

@property const char** choices;
@property size_t choicesSize;
@property uint32_t* userChoice;
@property const char* text;

- (ESSelectionData *)init;
@end
