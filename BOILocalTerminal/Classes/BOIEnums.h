//
//  BOIEnums.h
//  Totelier
//
//  Created by Islet on 03/09/22.
//  Copyright © 2022 Phenomtec. All rights reserved.
//

#ifndef BOIEnums_h
#define BOIEnums_h

typedef NS_ENUM(NSUInteger,BOIOperationType) {
    BOIOperationTypeTerminalInitalization = 0,
    BOIOperationTypeCheckStatus,
    BOIOperationTypeSale,
    BOIOperationTypeReversal,
    BOIOperationTypeLastTrxData,
    BOIOperationTypeReconciliation,
    BOIOperationTypePrintOut,
    BOIOperationTypeClosingDayPrintOut
};

typedef NS_ENUM(NSUInteger,TOTBOIConnectionType) {
    TOTBOIConnectionTypeDisconnected =0,
    TOTBOIConnectionTypeConnectedThroughWifi,
    TOTBOIConnectionTypeConnetedThroughPCL
};

typedef NS_ENUM(NSUInteger,BOITerminalPclService) {
    BOITerminalPclServiceStopped,
    BOITerminalPclServiceStarted,
    BOITerminalPclServiceConnected,
    BOITerminalPclServiceFailedNoConnection,
    BOITerminalPclServiceFailedInternal
};
//ecr_terminalStatus
typedef NS_ENUM(NSUInteger,BOITransactionStatus) {
    BOITransactionStatusNewTransaction,
    BOITransactionStatusWattingForCard,
    BOITransactionStatusWattingForPIN,
    BOITransactionStatusWattingForEMVChoice,
    BOITransactionStatusWattingForHost,
    BOITransactionStatusWattingForSingature,
    BOITransactionStatusWattingForTransactionEnd,
    BOITransactionStatusWattingForCardRemoval,
    BOITransactionStatusBusy,
    BOITransactionStatusInProgress,
    BOITransactionStatusWattingForCopy,
    BOITransactionStatusWattingForAuthCode,
    BOITransactionStatusWattingForUserAction,
    BOITransactionStatusBatchCompleted,
    BOITransactionStatusSelectingCurrency,
    BOITransactionStatusWattingForCashback,
    BOITransactionStatusTransactionAccepted,
    BOITransactionStatusWattingForAmount,
    BOITransactionStatusWattingForSelection,
    BOITransactionStatusAppError,
    BOITransactionStatusReconNeeded,
    BOITransactionStatusUnknown
};
// ecr_transactionResult

typedef NS_ENUM(NSUInteger,TOTBOIResult) {
    TOTBOIResultAccepted =0,
    TOTBOIResultRefused = 1,
    TOTBOIResultNoConnection = 2,
    TOTBOIResultInterruptedByUser  = 7
};
//ecr_transactionType
typedef NS_ENUM(NSUInteger,TOTBOITransactionType) {
    TOTBOITransactionTypeSale= 0,
    TOTBOITransactionTypeCashBack = 1,
    TOTBOITransactionTypePreAuth = 2,
    TOTBOITransactionTypeCompletion = 3,
    TOTBOITransactionTypeRefund = 4,
    TOTBOITransactionTypeReversal = 5,
    TOTBOITransactionTypeGiftActivation = 6,
    TOTBOITransactionTypeGiftBalance = 7,
    TOTBOITransactionTypeReconcile = 8,
    TOTBOITransactionTypeTestConnection = 9,
    TOTBOITransactionTypeTMS = 10,
    TOTBOITransactionTypeGiftTopUp = 11,
    TOTBOITransactionTypeEVSalse = 12,
    TOTBOITransactionTypePreAuthTopUp = 13,
    TOTBOITransactionTypePreAuthCancel = 14,
    TOTBOITransactionTypeUnknown = 15
};
// CardReaderType
typedef NS_ENUM(NSUInteger,TOTBOICardReadType) {
    TOTBOICardReadTypeCTLS,
    TOTBOICardReadTypeManal,
    TOTBOICardReadTypeMagstripe,
    TOTBOICardReadTypeICC,
    TOTBOICardReadTypeunKnown
};
// AuthorizationType
typedef NS_ENUM(NSUInteger,TOTBOICardAuthType) {
    TOTBOICardAuthTypeUnknown,
    TOTBOICardAuthTypeOnLine,
    TOTBOICardAuthTypeOffline,
    TOTBOICardAuthTypeReferral
};

// AuthorizationMethod
typedef NS_ENUM(NSUInteger,TOTBOICardAuthMethod) {
    TOTBOICardAuthMethodUnknown,
    TOTBOICardAuthMethodPin,
    TOTBOICardAuthMethodSign,
    TOTBOICardAuthMethodPinSign,
    TOTBOICardAuthMethodNoCVM,
    TOTBOICardAuthMethodNoCVMSignatureOnFile,
    TOTBOICardAuthMethodCDCVM
};
// EmvCryptogramType
typedef NS_ENUM(NSUInteger,TOTCryptoProgramType) {
    TOTCryptoProgramTypeAAC,
    TOTCryptoProgramTypeTC,
    TOTCryptoProgramTypeARQC,
    TOTCryptoProgramTypeUnknown
};
// Only for TOT to handle error messages
typedef NS_ENUM(NSUInteger,TOTBOIOperationCompleteState) {
    TOTBOIOperationCompleteStateNoIp = 0,
    TOTBOIOperationCompleteStateInitalizationFailed,
    TOTBOIOperationCompleteStateSetTcpIpLinkInitalizationFailed,
    TOTBOIOperationCompleteStateSetCashRegisterIdInitalizationFailed,
    TOTBOIOperationCompleteStateSetHandleTerminalRequestsInitalizationFailed,
    TOTBOIOperationCompleteStateNoErContext,
    TOTBOIOperationCompleteStateGetTreminalStatusFailed,
    TOTBOIOperationCompleteStateReadTreminalStatusFailed,
    TOTBOIOperationCompleteStateErrorPreparingPrintOut,
    TOTBOIOperationCompleteStateErrorInitalizingPrintOut,
    TOTBOIOperationCompleteStateErrorStartingPrintOut,
    TOTBOIOperationCompleteStateInValidAmount,
    TOTBOIOperationCompleteStateErrorSetTransactionType,
    TOTBOIOperationCompleteStateErrorSettingAmount,
    TOTBOIOperationCompleteStateErrorStartingTransactionProcess,
    TOTBOIOperationCompleteStateTerminalNotReady,
    TOTBOIOperationCompleteStateErrorSetingTransactionNumber,
    TOTBOIOperationCompleteStateSucess
};
// Only for TOT in ESAi
typedef NS_ENUM(NSUInteger,BOILogDestination) {
    BOILogDestinationAPI,
    BOILogDestinationPCL,
    BOILogDestinationPrintout,
    BOILogDestinationStatus
} ;

#endif /* BOIEnums_h */
