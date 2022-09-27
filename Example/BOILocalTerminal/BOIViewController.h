//
//  BOIViewController.h
//  BOILocalTerminal
//
//  Created by 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 on 09/23/2022.
//  Copyright (c) 2022 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. All rights reserved.
//

#import "BOILocalTerminal.h"
@import UIKit;

@interface BOIViewController : UIViewController<BOILocalTerminalEvents>
{
    
    BOILocalTerminalVM * vm;
    NSString * statusLog;
    NSString * apiLog;
    NSString * pclLog;
    NSString * printOuts;

}
@property (weak, nonatomic) IBOutlet UITextField *textIP;
@property (weak, nonatomic) IBOutlet UITextField *textAmount;
@property (weak, nonatomic) IBOutlet UITextField *textTransaction;
@property (weak, nonatomic) IBOutlet UITextView *textResult;
@property (weak, nonatomic) IBOutlet UISegmentedControl *switchResult;
@property (weak, nonatomic) IBOutlet UISegmentedControl *switchTrxType;
@property (weak, nonatomic) IBOutlet UIButton *btnClearLogFile;
@property (weak, nonatomic) IBOutlet UILabel *labelPclOn;
@property (weak, nonatomic) IBOutlet UIButton *LogCLearButton;
@property (weak, nonatomic) IBOutlet UIButton *StartButton;
@property (weak, nonatomic) IBOutlet UILabel *labelWIFI;

@end
