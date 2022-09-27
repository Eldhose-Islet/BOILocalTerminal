//
//  BOILocalTerminalVM.m
//  Totelier
//
//  Created by Islet on 25/08/22.
//  Copyright © 2022 Phenomtec. All rights reserved.
//

#import "BOILocalTerminalVM.h"
#import "ESDummySelectionDelegate.h"
#import "ESApiTextFieldDelegate.h"
//#import "Totelier-Swift.h"


@implementation BOILocalTerminalVM
NSString * ipForBluetoothAddress =  @"127.0.0.1";
- (instancetype)init{
    self.esBusy = false;
    
    
    es = [[ESApi alloc] initWithCallbacks:self];
    
#if !TARGET_IPHONE_SIMULATOR
    _pclService = nil;
    _pclService = [ICPclService sharedICPclService];
    _pclService.delegate = nil;
    [self writeLog:[NSString stringWithFormat:@"iSMP Library Version: %@\n", [ICISMPVersion substringFromIndex:6]] destination: BOILogDestinationPCL ];
    
#endif
   
    dateFormatter = [[NSDateFormatter alloc] init];
    [dateFormatter setDateFormat:@"yyyyMMdd_HHmmss"];
    numberFormatter = [[NSNumberFormatter alloc] init];
    numberFormatter.locale = [NSLocale currentLocale];
    numberFormatter.maximumFractionDigits = 2;
    numberFormatter.minimumFractionDigits = 0;

    return [super init];
}
- (bool)trySetBusy:(bool)state
{
    bool ret = false;
    @synchronized(self)
    {
        if (!(_esBusy && state))
        {
            _esBusy = state;
            ret = true;
        }
    }
    return ret;
}
// [[ Ingenico PCL
- (bool)pclDiscoverTerminals
{
#if !TARGET_IPHONE_SIMULATOR
    _pclService = [ICPclService sharedICPclService];
    _pclService.delegate = nil;
    
    NSArray *terminals = [_pclService getAvailableTerminals];
    ICTerminal *terminal = nil;
    
    if (0 == terminals.count)
    {
        [self writeLog:@"No terminals found\n" destination: BOILogDestinationPCL];
        return false;
    } else {
        NSString * txt = [NSString stringWithFormat:@"%lu terminal%s found", terminals.count, ((terminals.count) > 1 ? "s" : "") ];
        [self writeLog:txt destination: BOILogDestinationPCL];
    }
    
    terminal = [terminals firstObject];
    NSString * terminal_description = [NSString stringWithFormat:@"Name:%@ macAddress:%@ ipAddress:%@ bluetooth:%s",
                                       terminal.name,
                                       terminal.macAddress,
                                       terminal.ipAddress,
                                       ((terminal && terminal.isBluetooth) ? "YES" : "NO") ];
    [self writeLog:terminal_description destination: BOILogDestinationPCL];
    
    NSUserDefaults *prefs = [NSUserDefaults standardUserDefaults];
    [prefs setObject:terminal.name forKey:@"IngenicoCompanionInUseName"];
    [prefs setObject:terminal.macAddress forKey:@"IngenicoCompanionInUseMacAddress"];
    [prefs setObject:terminal.ipAddress forKey:@"IngenicoCompanionInUseIpAddress"];
    [prefs setObject:(terminal ? @(terminal.isBluetooth) : nil) forKey:@"IngenicoCompanionInUseType"];
#endif
    return true;
}

- (bool)pclConnectToTerminal
{
    NSUserDefaults *prefs = [NSUserDefaults standardUserDefaults];
    NSNumber *isBluetooth = [prefs objectForKey:@"IngenicoCompanionInUseType"];
    
    if (nil == isBluetooth) {
        [self writeLog:@"Find terminal first, please" destination: BOILogDestinationPCL];
        return false;
    }
#if !TARGET_IPHONE_SIMULATOR
    self.terminal = [[ICTerminal alloc] init];
    self.terminal.name = [prefs stringForKey:@"IngenicoCompanionInUseName"];
    self.terminal.macAddress = [prefs stringForKey:@"IngenicoCompanionInUseMacAddress"];
    self.terminal.isBluetooth = [prefs boolForKey:@"IngenicoCompanionInUseType"];
    _pclService = [ICPclService sharedICPclService];
    _pclService.delegate = self;
    _sslParam = [[ICSSLParameters alloc] init];
    self.sslParam.isSSL = false;
    [self writeLog:@"starting pcl service, please wait" destination: BOILogDestinationPCL];
    return (PCL_SERVICE_STARTED == [_pclService startPclServiceWith:self.terminal andSecurity:self.sslParam]);
#else
    return true;
#endif
}
#pragma mark - ICPclServiceDelegate

- (void)pclLogEntry:(NSString *)message withSeverity:(int)severity
{
    [self writeLog:[NSString stringWithFormat:@"%@\n", message] destination: BOILogDestinationPCL];
}
#if !TARGET_IPHONE_SIMULATOR
- (void)notifyConnection:(ICPclService *)sender
{
    [self writeLog:@"PCL connected" destination: BOILogDestinationPCL];
    switch(_pclService.getPclServiceState) {
        case PCL_SERVICE_STOPPED:
        case PCL_SERVICE_FAILED_INTERNAL:
        case PCL_SERVICE_FAILED_NO_CNX:
            [self writeLog:@"SERVER_STOPPED\n" destination: BOILogDestinationPCL];
            return;
        case PCL_SERVICE_STARTED:
            [self writeLog:@"SERVER_STARTED\n" destination: BOILogDestinationPCL];
            return;
        case PCL_SERVICE_CONNECTED:
            [self writeLog:@"SERVER_CONNECTED\n" destination: BOILogDestinationPCL];
            break;
    }
    [self ifTerminalConnected];
}

- (void)notifyDisconnection:(ICPclService *)sender
{
    [self writeLog:@"SERVER_DISCONNECTED\n" destination: BOILogDestinationPCL];
    [self.delegate terminalConnectionTypeChangedTo:TOTBOIConnectionTypeDisconnected];
    [self trySetBusy:false];
}
#endif
// ]]

- (void)stopPCL
{
#if !TARGET_IPHONE_SIMULATOR
    [_pclService stopPclService];
    _pclService.delegate = nil;
#endif
    [self writeLog:@"STOP\n" destination: BOILogDestinationPCL];
}

- (void)doOperationForBlueToothOrLanWith:(NSString * )ip operation:(BOIOperationType) currentOp amount:(NSString *)amount transactionId:(NSString *)transactionId{
    self.terminalIp = ip;
    self.currentOp = currentOp;
    self.currentAmount = amount;
    self.transactionToReverseId = transactionId;
    if ([ip isEqualToString:ipForBluetoothAddress]) // TO DO: do it better way
    { // try to connect via PCL
        [self performSelectorInBackground:@selector(pclConnectPerform) withObject:nil];
    }
    else
    { // tcp is ready
        [self.delegate  terminalConnectionTypeChangedTo:TOTBOIConnectionTypeConnectedThroughWifi];
        [self performSelectorInBackground:@selector(connectThroughWifi) withObject:nil];
    }
}

- (void)connectThroughWifi{
    [self apiStartPerform];
}
// [[ start logic
- (void)pclConnectPerform
{
#if !TARGET_IPHONE_SIMULATOR
    _pclService = [ICPclService sharedICPclService];
    if (PCL_SERVICE_CONNECTED == _pclService.getPclServiceState)
    {
        [self ifTerminalConnected];
    }
    else
        if (![self pclDiscoverTerminals])
        {
            [self writeLog:@"NO TERMINALS FOUND (PCL)\n" destination: BOILogDestinationAPI];
            [self trySetBusy:false];
        }
        else
            if (![self pclConnectToTerminal]) // sets the callback 'notifyConnection'
            {
                [self writeLog:@"PCL SERVICE FAILED" destination: BOILogDestinationAPI];
                [self trySetBusy:false];
            }
#endif
}

- (void)ifTerminalConnected
{
#if !TARGET_IPHONE_SIMULATOR
    int ret = [_pclService addDynamicBridgeLocal:3000 :0];
#else
    int ret = 0;
#endif
    switch(ret) {
        case  0:
            [self writeLog:@"bridge added" destination: BOILogDestinationPCL];
            
            [self.delegate terminalConnectionTypeChangedTo:TOTBOIConnectionTypeConnetedThroughPCL];
            [self performSelectorInBackground:@selector(apiStartPerform) withObject:nil];
            
            return;
        case -1:
            [self writeLog:@"no more available bridges" destination: BOILogDestinationPCL];
            break;
        case -3:
            [self writeLog:@"issue during thread creation" destination: BOILogDestinationPCL];
            break;
        case -4:
            [self writeLog:@"bridge initialization failed" destination: BOILogDestinationPCL];
            break;
        default:
            [self writeLog:@"bridge initialization failed - I don't know why..." destination: BOILogDestinationPCL];
    }
    [self trySetBusy:false];
}

- (void)apiStartPerform
{
  
    [self esApiTest];
    if ([self.terminalIp isEqualToString:ipForBluetoothAddress]) // TO DO: do it better way
    { // try to connect via PCL
        [self stopPCL];
    }
    [self.delegate terminalConnectionTypeChangedTo:TOTBOIConnectionTypeDisconnected];
    [self trySetBusy:false];
}
// ]]

- (void)addTimestampToLog
{
    NSDate *currentTime = [NSDate date];
    NSString * timeStamp = [NSString stringWithFormat:@"--------%@--------\n", [dateFormatter stringFromDate:currentTime ]];
    [self writeLog:timeStamp destination: BOILogDestinationAPI];
    [self writeLog:timeStamp destination: BOILogDestinationPCL];
    [self writeLog:timeStamp destination: BOILogDestinationPrintout];
    [self writeLog:timeStamp destination: BOILogDestinationStatus];
}


- (NSString *)numberStringAsAmount:(NSString *)text{
    NSScanner * scanner = [NSScanner scannerWithString:text];
    scanner.locale = [NSLocale currentLocale];
    double dbtmp = 0;
    [scanner scanDouble:&dbtmp];
    return  [numberFormatter stringFromNumber:[NSNumber numberWithDouble:dbtmp]];
}
- (void)writeLog:(NSString *)message destination:(BOILogDestination)dest
{
    message = [message stringByReplacingOccurrencesOfString:@"\r" withString:@"\t"];
    if(dest == BOILogDestinationAPI || dest == BOILogDestinationStatus){
//        [TOTBOILogBridge saveLog:message];
    }
   
    NSArray *taskArgs  = [NSArray arrayWithObjects: message, [NSNumber numberWithInt:(int)dest], nil];
    [self performSelectorOnMainThread:@selector(displayLog:) withObject:taskArgs waitUntilDone:NO];
}

- (void)displayLog:(NSArray *)taskArgs
{
    
    [self.delegate logUpdated:taskArgs];
}


- (void)askClientForValueInMainThread:(ESAsynchResp *)answ
{
    __weak typeof(self) weakSelf = self;
    dispatch_async(dispatch_get_main_queue(), ^{
        [weakSelf.delegate askClientForValueInMainThread:answ];
    });
}
- (int)askClient:(NSString *)title message:(NSString *)message showCancelButton:(bool)showCancelButton {
    ESAsynchResp * answ =  [[ESAsynchResp alloc] init];
    answ.args  = [NSArray arrayWithObjects: title, message, [NSNumber numberWithInt:showCancelButton], nil];
    [self askClientForValueInMainThread:answ];
    [answ response_wait];

    return [[answ.args objectAtIndex: 0] intValue];
    
}

- (bool)askClientForSelection:(ESSelectionData *)selectionData
{ // emulate
    // logAPI part
    const char * text = (NULL != selectionData.text) ? selectionData.text : "";
    NSString * txt = [NSString stringWithFormat:@"\nSELECTION\n- %s -\n", text];
    [self writeLog:txt destination: BOILogDestinationAPI];
    size_t cnt = 0;
    while (selectionData.choicesSize > cnt)
    {
        NSString * txt = [NSString stringWithFormat:@"(%lu) (%s)\n", cnt + 1, selectionData.choices[cnt]];
        [self writeLog:txt destination: BOILogDestinationAPI];
        cnt++;
    }
    // askClientForValueInMainThread part
    NSString *_title = [NSString stringWithFormat:@"SELECT %s", text];
    NSString *_message = [NSString stringWithFormat:@"ENTER NUMBER (1 .. %lu)", cnt + 1];
    int resp = -1;
    ESDummySelectionDelegate * dummySelectionDelegate = [[ESDummySelectionDelegate alloc] initWithMaxValue:selectionData];
    while(!((0 == resp) || ((1 == resp) && dummySelectionDelegate.textOk)))
    {
        ESAsynchResp * answ =  [[ESAsynchResp alloc] init];
        dummySelectionDelegate.retVal = 0;
        answ.args  = [NSArray arrayWithObjects: _title, _message, [NSNumber numberWithInt:1], dummySelectionDelegate, nil];
        [self performSelectorOnMainThread:@selector(askClientForValueInMainThread:) withObject:answ waitUntilDone:NO];
        [answ response_wait];
        resp = [[answ.args objectAtIndex: 0] intValue];
    }
    return (bool)(0 < resp);
}


- (int)askClientForValue:(NSString *)title message:(NSString *)message valueQuestionData:(ESValueQuestionData *)valueQuestionData
{
    int resp = -1;
    ESApiTextFieldDelegate * apiTextFieldDelegate = [[ESApiTextFieldDelegate alloc] initWithValueRestrictions:valueQuestionData];
    while(!((0 == resp) || ((1 == resp) && apiTextFieldDelegate.textOk)))
    {
        ESAsynchResp * answ =  [[ESAsynchResp alloc] init];
        apiTextFieldDelegate.textOk = false;
        answ.args  = [NSArray arrayWithObjects: title, message, [NSNumber numberWithInt:1], apiTextFieldDelegate, nil];
        [self performSelectorOnMainThread:@selector(askClientForValueInMainThread:) withObject:answ waitUntilDone:NO];
        [answ response_wait];
        resp = [[answ.args objectAtIndex: 0] intValue];
    }
    return resp;
}
- ( ESValueQuestionData * )updateAmoutStr:(NSString * _Nullable)amtStr toESValueQuestion:(ESApiTextFieldDelegate * _Nullable) textField{
    
    const char *enteredText2 = [amtStr cStringUsingEncoding:NSUTF8StringEncoding];
    const size_t enteredTextLen = strlen(enteredText2);
    if (NULL == textField.data)
    {
        return nil;
    }
    if (((textField.data.maxLen >= enteredTextLen) && (textField.data.minLen <= enteredTextLen)))
    {
        if ((NULL != textField.data.userData) && (0 < textField.data.userDataLen))
        {
            memset(textField.data.userData, 0, textField.data.userDataLen);
            strncpy(textField.data.userData, enteredText2, textField.data.userDataLen - 1);
        }
        textField.textOk = true;
        return textField.data;
    }
    return nil;
}
- (int)notifyClient:(NSString *)prompt
{
    NSString * txt = [NSString stringWithFormat:@"\nNOTIFICATION\n%@\n\n", prompt];
    
    [self writeLog:txt destination: BOILogDestinationAPI];
    return 1;
}

- (void)notifyAboutStatusChange:(ecr_terminalStatus) status
{
    NSString * statusDescription = [es ApiGetStatusDescription:status];
    NSString * txt = [NSString stringWithFormat:@"\nSTATUS CHANGED\n%@\n", [es ApiGetStatusDescription:status]];
   // for c style to objective c
    [self.delegate terminalTransactionStatusChangedTo:(BOITransactionStatus)status description:statusDescription];
    [self writeLog:txt destination: BOILogDestinationStatus];
}

- (void) transactionComplete:(ESAPIResult *)result{
    __weak typeof(self) weakSelf = self;
    dispatch_async(dispatch_get_main_queue(), ^{
        [weakSelf.delegate gotTransctionResult:[TOTBOItransactionResult transactionResultFrom:result]];
    });
}


// [[ eS API calls
- (void)esApiTest
{
    
    if ([es ApiInit:self.terminalIp]) {
        switch (self.currentOp) {
            case     BOIOperationTypeCheckStatus:
                [es ApiDumpStatusToLog];
                break;
            case     BOIOperationTypeSale:
                [es ApiSale:self.currentAmount];
                break;
            case     BOIOperationTypeReversal:
                [es ApiReversal:self.transactionToReverseId amount:self.currentAmount];
                break;
            case     BOIOperationTypeLastTrxData:
                [es ApiPrintLastTrx];
                break;
            case     BOIOperationTypeReconciliation:
                [es ApiReconciliation];
                break;
            default:;
        }
        [es ApiStop];
    }
}
// ]]

@end
