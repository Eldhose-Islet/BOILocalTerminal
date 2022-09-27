//
//  BOILocalTerminalVM.h
//  Totelier
//
//  Created by Islet on 25/08/22.
//  Copyright © 2022 Phenomtec. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "ESApi.h"
#import "BOILocalTerminalEvents.h"
@class ESApiTextFieldDelegate;
#if TARGET_IPHONE_SIMULATOR


@interface BOILocalTerminalVM : NSObject<ESCallbacks>
{
#else
@import iSMP;

@interface BOILocalTerminalVM : NSObject<ICPclServiceDelegate,ESCallbacks>
{
#endif


    ESApi * es;
  
    NSDateFormatter *dateFormatter;
    NSNumberFormatter *numberFormatter;

}
@property (nonatomic, weak) NSObject<BOILocalTerminalEvents> * _Nullable delegate;
@property (nonatomic, readwrite)bool  esBusy;
#if !TARGET_IPHONE_SIMULATOR
@property (nonatomic, strong) ICPclService          * _Nullable pclService;
@property (nonatomic, strong) ICTerminal            * _Nullable terminal;
@property (nonatomic, strong) ICSSLParameters       * _Nullable sslParam;
#endif
@property (nonatomic, strong) NSString *  _Nullable terminalIp;
@property (nonatomic, readwrite) BOIOperationType currentOp;
@property (nonatomic, strong) NSString *  _Nullable currentAmount;
@property (nonatomic, strong) NSString * _Nullable  transactionToReverseId;

- (bool)trySetBusy:(bool)state;
- (void)addTimestampToLog;

- (void)ifTerminalConnected;

- (NSString *_Nullable)numberStringAsAmount:(NSString * _Nullable )text;
- (void)writeLog:(NSString * _Nullable )message destination:(BOILogDestination)dest;
- (void)pclConnectPerform;
- (void)apiStartPerform;
- (void)esApiTest;
- (void)doOperationForBlueToothOrLanWith:(NSString *  _Nullable )ip operation:(BOIOperationType) currentOp amount:(NSString * _Nullable )amount transactionId:(NSString * _Nullable )transactionId;
- ( ESValueQuestionData * _Nullable)updateAmoutStr:(NSString * _Nullable)amtStr toESValueQuestion:(ESApiTextFieldDelegate * _Nullable) textField;
@end

 
