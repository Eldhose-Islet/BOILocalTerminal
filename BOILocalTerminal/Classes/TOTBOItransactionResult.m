//
//  TOTBOItransactionResult.m
//  Totelier
//
//  Created by Islet on 03/09/22.
//  Copyright © 2022 Phenomtec. All rights reserved.
//

#import "TOTBOItransactionResult.h"
#import "ESCallbacks.h"

@implementation TOTBOItransactionResult
+ (TOTBOItransactionResult *) transactionResultFrom:(ESAPIResult *)apiResult{
    TOTBOItransactionResult * retVal = [[TOTBOItransactionResult alloc] init];
 
    retVal.transactionResult = (TOTBOIResult)apiResult.transactionResult;
    retVal.transactionType = (TOTBOITransactionType) apiResult.transactionType;
    retVal.transactionTypeOrginal = (TOTBOITransactionType) apiResult.transactionTypeOrginal;
    retVal.cardReadType = (TOTBOICardReadType)apiResult.cardReadType;
    retVal.autharizationType = (TOTBOICardAuthType)apiResult.autharizationType;
    retVal.authMethod = (TOTBOICardAuthMethod)apiResult.authMethod;
    retVal.cryptogramType = (TOTCryptoProgramType)apiResult.cryptogramType;
    retVal.didTerminalDidPrintOut = apiResult.didTerminalDidPrintOut;
    retVal.didmanualReveral = apiResult.didmanualReveral;
    retVal.wasTransactionReveral = apiResult.wasTransactionReveral;
    retVal.transactionNumber = apiResult.transactionNumber;
    retVal.transactionDate = apiResult.transactionDate;
    retVal.transactionTime = apiResult.transactionTime;
    retVal.transactionCount = apiResult.transactionCount;
    retVal.transactionTvr = apiResult.transactionTvr;
    retVal.transactionAid = apiResult.transactionAid;
   
    retVal.transactionCurrCode = apiResult.transactionCurrCode;
    retVal.transactionCurrencyLabel = apiResult.transactionCurrencyLabel;
    retVal.terminalCurrencyLabel = apiResult.terminalCurrencyLabel;
    retVal.transactionAmount =  apiResult.transactionAmount;
    retVal.transactionAmountInTerminalCurrency = apiResult.transactionAmountInTerminalCurrency;
    retVal.transactionCashback = apiResult.transactionCashback;
    retVal.transactionAmountOfTip = apiResult.transactionAmountOfTip;
    retVal.terminalStatus = (BOITransactionStatus)apiResult.terminalStatus;
    retVal.completeState = apiResult.completeState;
    retVal.operationType = apiResult.operationType;
    retVal.log = apiResult.log;
    retVal.logDestination = apiResult.logDestination;
    retVal.wasContextAvailable = apiResult.wasContextAvailable;
    NSCharacterSet * charactersToRemove = [[NSCharacterSet alphanumericCharacterSet] invertedSet];
    NSString * transID = [[apiResult.transactionTerminalID componentsSeparatedByCharactersInSet:charactersToRemove] componentsJoinedByString:@""];
    retVal.transactionTerminalID = transID;
    retVal.authCode = apiResult.authCode;
    return retVal;
}
@end
