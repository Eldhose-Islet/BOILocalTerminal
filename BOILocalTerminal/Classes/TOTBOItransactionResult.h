//
//  TOTBOItransactionResult.h
//  Totelier
//
//  Created by Islet on 03/09/22.
//  Copyright © 2022 Phenomtec. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "BOIEnums.h"


@class ESAPIResult;
@interface TOTBOItransactionResult : NSObject
@property(nonatomic,readwrite) TOTBOIOperationCompleteState completeState;
@property(nonatomic,readwrite) BOIOperationType operationType;
@property(nonatomic,readwrite) TOTBOIResult transactionResult;
@property(nonatomic,readwrite) TOTBOITransactionType transactionType;

@property(nonatomic,readwrite) TOTBOITransactionType transactionTypeOrginal;
@property(nonatomic,readwrite) TOTBOICardReadType cardReadType;
@property(nonatomic,readwrite) TOTBOICardAuthType autharizationType;
@property(nonatomic,readwrite) TOTBOICardAuthMethod authMethod;
@property(nonatomic,readwrite) TOTCryptoProgramType cryptogramType;
@property(nonatomic,readwrite) BOITransactionStatus terminalStatus;
@property(nonatomic,readwrite) bool wasContextAvailable;
@property(nonatomic,readwrite) bool didTerminalDidPrintOut;
@property(nonatomic,readwrite) bool didmanualReveral;
@property(nonatomic,readwrite) bool wasTransactionReveral;
@property(nonatomic,strong)NSString * _Nullable transactionNumber;
@property(nonatomic,strong)NSString * _Nullable transactionDate;
@property(nonatomic,strong)NSString * _Nullable transactionTime;
@property(nonatomic,strong)NSString * _Nullable transactionCount;
@property(nonatomic,strong)NSString * _Nullable transactionTvr;
@property(nonatomic,strong)NSString * _Nullable transactionTsi;
@property(nonatomic,strong)NSString * _Nullable transactionAid;
@property(nonatomic,readwrite)int transactionCurrCode;
@property(nonatomic,strong)NSString * _Nullable transactionCurrencyLabel;
@property(nonatomic,strong)NSString * _Nullable terminalCurrencyLabel;
@property(nonatomic,strong)NSString * _Nullable transactionAmount;
@property(nonatomic,strong)NSString * _Nullable transactionCashback;
@property(nonatomic,strong)NSString * _Nullable transactionAmountInTerminalCurrency;
@property(nonatomic,strong)NSString * _Nullable transactionAmountOfTip;
@property(nonatomic,strong)NSString * _Nullable log;
@property(nonatomic,strong)NSString * _Nullable transactionTerminalID;
@property(nonatomic,readwrite)BOILogDestination logDestination;
@property(nonatomic,strong)NSString * _Nullable authCode;

+ (TOTBOItransactionResult *  _Nonnull) transactionResultFrom:(ESAPIResult * _Nullable )apiResult;
@end

