#import "ESTextFieldDelegate.h"
#import "ESSelectionData.h"

@interface ESDummySelectionDelegate : ESTextFieldDelegate {
    ESSelectionData * _data;
}

@property bool retVal;

- (ESDummySelectionDelegate *)initWithMaxValue:(ESSelectionData *)data;
- (ESDummySelectionDelegate *)init;
@end
