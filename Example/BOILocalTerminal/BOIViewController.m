//
//  BOIViewController.m
//  BOILocalTerminal
//
//  Created by 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 on 09/23/2022.
//  Copyright (c) 2022 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. All rights reserved.
//

#import "BOIViewController.h"

@interface BOIViewController ()

@end

@implementation BOIViewController

NSString * ipSaveKey = @"BOI_Terminal_Ip";
BOIOperationType currentOp =BOIOperationTypeSale;

// [[ called from outside
- (void)viewDidLoad
{
    [super viewDidLoad];

    vm = [[BOILocalTerminalVM alloc] init];
    vm.delegate= self;
    currentOp = BOIOperationTypeCheckStatus;
    _textResult.hidden = false;
    _labelPclOn.hidden = true;
    _labelWIFI.hidden = true;

    _textIP.text = [[NSUserDefaults standardUserDefaults] stringForKey:ipSaveKey];
#if !DEBUG
    for (UIView * vw in self.viewsToHideOnRelease) {
        [vw setHidden:true];
    }
    [self.btnClearLogFile setHidden:true];
#else
    if (self.textIP.text.length < 1) {
        self.textIP.text = @"192.168.29.66";
    }
    
#endif
#if TARGET_IPHONE_SIMULATOR
    _textIP.text = @"BOI terminal not supported in simulator";
    _textIP.textColor = [UIColor redColor];
    _textIP.backgroundColor = [UIColor clearColor];
#endif
    
}

- (IBAction)btnSaveTouch:(id)sender {
    [[NSUserDefaults standardUserDefaults] setValue:_textIP.text forKey:ipSaveKey];

}

- (IBAction)buttonStartTouch:(id)sender
{
    
    // hide keyboard
    [_textIP resignFirstResponder];
    [_textAmount resignFirstResponder];
    [_textTransaction resignFirstResponder];
    // start
    if ([vm trySetBusy:true])
    {
        [vm addTimestampToLog];
       
        // IP
        NSString * ipWithSpaces = [ _textIP text ];
        NSString * ip = [ipWithSpaces stringByTrimmingCharactersInSet:[NSCharacterSet whitespaceCharacterSet]];
        // amount
        NSScanner * scanner = [NSScanner scannerWithString:[_textAmount text]];
        scanner.locale = [NSLocale currentLocale];
        int itmp = 0;
        [scanner scanInt:&itmp];
        NSString * amount = [[NSNumber numberWithInt:itmp] stringValue];
        // transaction id, for reversal
        NSString * transaction = [ _textTransaction text];
        [vm doOperationForBlueToothOrLanWith:ip operation:currentOp amount:amount transactionId:transaction];
       
    }
}


- (BOILogDestination) selectedLogType{
    return (BOILogDestination)self.switchResult.selectedSegmentIndex;
}
- (IBAction)switchResultChange:(UISegmentedControl *)sender
{
//    _textResult.text = [TOTBOILogBridge todayLogForLogType:[self selectedLogType]];
    switch ([self selectedLogType])
    {
        
        case BOILogDestinationAPI:
            _textResult.text = apiLog;
            break;
        case BOILogDestinationPCL:
            _textResult.text = pclLog;
            break;
        break;
        case BOILogDestinationPrintout:
            _textResult.text = printOuts;
            break;
        case BOILogDestinationStatus:
            _textResult.text = statusLog;
            break;
    }
}

- (IBAction)switchTrxTypeChanged:(UISegmentedControl *)sender
{
    switch ((unsigned int)sender.selectedSegmentIndex)
    {
        case 0:
            currentOp = BOIOperationTypeCheckStatus;
            break;
        case 1:
            currentOp = BOIOperationTypeSale;
            break;
        case 2:
            currentOp = BOIOperationTypeReversal;
            break;
        case 3:
            currentOp = BOIOperationTypeLastTrxData;
            break;
        case 4:
            currentOp = BOIOperationTypeReconciliation;
            break;
        default:;
    }
}

- (IBAction)textAmountEditingDidEnd:(UITextField *)sender
{
    sender.text = [vm numberStringAsAmount:sender.text];
    
}

- (IBAction)clearlogPerform:(id)sender
{
    _textResult.text = @"";
    apiLog = @"";
    pclLog = @"";
    printOuts = @"";
    statusLog = @"";
}

// ]]

// [[ utils


- (void)terminalTransactionStatusChangedTo:(BOITransactionStatus)stat description:(NSString *)desc {
    NSLog(@"Terminal status chnaged to %lu :%@",(unsigned long)stat,desc );
}
- (void)terminalConnectionTypeChangedTo:(TOTBOIConnectionType)stat{
    __weak typeof(self) weakSelf = self;
    dispatch_async(dispatch_get_main_queue(), ^{
        weakSelf.labelWIFI.hidden =  true;
        weakSelf.labelPclOn.hidden = true;
        switch (stat) {
            case TOTBOIConnectionTypeConnectedThroughWifi:
                weakSelf.labelWIFI.hidden = false;
                break;
            case TOTBOIConnectionTypeConnetedThroughPCL:
                weakSelf.labelPclOn.hidden = false;
                break;
            default:
                break;
        }
    });
    
}

// ]]
// [[ callbacks from eS API
- (void)askClientInMainThread:(ESAsynchResp *)answ
{
    NSString *title = [answ.args firstObject];
    NSString *message = (answ.args.count > 1) ? answ.args[1] : nil;
    bool showCancelButton = (answ.args.count > 2) ? [answ.args[2] boolValue] : false;
    __block  ESAsynchResp *_answ = answ;
    _answ.args  = [NSArray arrayWithObjects: @(-1), nil];

    UIAlertController *alertController = [UIAlertController alertControllerWithTitle:title
            message:message
            preferredStyle:UIAlertControllerStyleAlert];
    UIAlertAction *okAction = [UIAlertAction actionWithTitle:@"OK" style:UIAlertActionStyleDefault handler:^(UIAlertAction * action)
    {
            _answ.args  = [NSArray arrayWithObjects: [NSNumber numberWithInt:1], nil];
            [_answ send_response];
    }];
    [alertController addAction:okAction];
    if (showCancelButton)
    {
        UIAlertAction *cancelAction = [UIAlertAction actionWithTitle:@"Cancel" style:UIAlertActionStyleCancel handler:^(UIAlertAction * action)
        {
            _answ.args  = [NSArray arrayWithObjects: [NSNumber numberWithInt:0], nil];
            [_answ send_response];
        }];
        [alertController addAction:cancelAction];
    }
    [self presentViewController:alertController animated:YES completion:nil];
}



- (void)askClientForValueInMainThread:(ESAsynchResp *)answ
{
    NSArray * args = answ.args;
    NSString *title = (args.count > 0) ? args[0] : nil;
    NSString *message = (args.count > 1) ? args[1] : nil;
    bool showCancelButton = (args.count > 2) ? [args[2] boolValue] :  false;
   
   
    __block ESAsynchResp *_answ = answ;
    _answ.args  = [NSArray arrayWithObjects:@(-1), nil];

    __block ESTextFieldDelegate * textFieldDelegate = (args.count > 3) ? args[3] : nil;
    UIAlertController *alertController = [UIAlertController alertControllerWithTitle:title
            message:message
            preferredStyle:UIAlertControllerStyleAlert];
    if (textFieldDelegate) {
        [alertController addTextFieldWithConfigurationHandler:^(UITextField *aTextField) {
            aTextField.delegate =  textFieldDelegate;
        }];
    }
    
    UIAlertAction *okAction = [UIAlertAction actionWithTitle:@"OK" style:UIAlertActionStyleDefault handler:^(UIAlertAction * action)
    {
            _answ.args  = [NSArray arrayWithObjects: [NSNumber numberWithInt:1], nil];
            [_answ send_response];
    }];
    [alertController addAction:okAction];

    if (showCancelButton)
    {
        UIAlertAction *cancelAction = [UIAlertAction actionWithTitle:@"Cancel" style:UIAlertActionStyleCancel handler:^(UIAlertAction * action)
        {
            _answ.args  = [NSArray arrayWithObjects: [NSNumber numberWithInt:0], nil];
            [_answ send_response];
        }];
        [alertController addAction:cancelAction];
    }
    [self presentViewController:alertController animated:YES completion:nil];
}

// ]]


- (void)logUpdated:(NSArray *)taskArgs{
    
    BOILogDestination logDest = BOILogDestinationStatus;
    if (taskArgs.count > 1) {
        logDest = [taskArgs[1] intValue];
    }
    [_textResult insertText:[taskArgs firstObject]];
    [_textResult scrollRangeToVisible:NSMakeRange(_textResult.text.length - 1, 0)];
    switch(logDest)
    {
         
        case BOILogDestinationStatus:
            statusLog = [taskArgs firstObject];
            break;
        case BOILogDestinationAPI:
            apiLog = [taskArgs firstObject];
            break;
        case BOILogDestinationPCL:
            pclLog = [taskArgs firstObject];
            break;
        case BOILogDestinationPrintout:
            printOuts = [taskArgs firstObject];
            break;
        default:;
    }
}



- (void)gotTransctionResult:(TOTBOItransactionResult * _Nullable)result {
    NSLog(@"Transaction result log %@",result.log);
    switch (result.operationType) {
        
        case BOIOperationTypeTerminalInitalization:
             
             break;
        case BOIOperationTypeCheckStatus:
             break;
       
        case BOIOperationTypeSale:
        {
            if (result.completeState == TOTBOIOperationCompleteStateSucess) {
                NSString * transactionID = result.transactionNumber;
                NSLog(@"Transaction id :%@",transactionID);
            }
            
        }
            break;

        case BOIOperationTypeReversal:
        
            break;
        case BOIOperationTypeLastTrxData:
        
            break;
        case BOIOperationTypeReconciliation:
        
            break;
        case BOIOperationTypePrintOut:
        
            break;
        case BOIOperationTypeClosingDayPrintOut:
        
            break;
        }
}

@end
