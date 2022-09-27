#import <UIKit/UIKit.h>

@interface ESValueQuestionData : NSObject {
    char   * _userData;
    size_t   _userDataLen;
    size_t   _maxLen;
    size_t   _minLen;
    bool   (*_isCharacterAllowed)(char character);
    NSStringEncoding _apiTextEncoding;
}

@property char   * userData;
@property size_t   userDataLen;
@property size_t   maxLen;
@property size_t   minLen;
@property bool   (*isCharacterAllowed)(char character);
@property NSStringEncoding apiTextEncoding;

- (ESValueQuestionData *)init;
@end
