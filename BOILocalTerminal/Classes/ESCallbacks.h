#import "ESValueQuestionData.h"
#import "ESSelectionData.h"
#if !(TARGET_IPHONE_SIMULATOR)
#import "ecrlib.h"
#else
#import "enumerations.h"
#endif
#import "BOIEnums.h"


@interface ESAPIResult : NSObject

@property(nonatomic,readwrite) TOTBOIOperationCompleteState completeState;
@property(nonatomic,readwrite) BOIOperationType operationType;
@property(nonatomic,readwrite) ecr_transactionResult transactionResult;
@property(nonatomic,readwrite) ecr_transactionType transactionType;

@property(nonatomic,readwrite) ecr_transactionType transactionTypeOrginal;
@property(nonatomic,readwrite) CardReaderType cardReadType;
@property(nonatomic,readwrite) AuthorizationType autharizationType;
@property(nonatomic,readwrite) AuthorizationMethod authMethod;
@property(nonatomic,readwrite) EmvCryptogramType cryptogramType;
@property(nonatomic,readwrite) ecr_terminalStatus terminalStatus;
@property(nonatomic,readwrite) bool wasContextAvailable;
@property(nonatomic,readwrite) bool didTerminalDidPrintOut;
@property(nonatomic,readwrite) bool didmanualReveral;
@property(nonatomic,readwrite) bool wasTransactionReveral;
@property(nonatomic,strong)NSString * transactionNumber;
@property(nonatomic,strong)NSString * transactionDate;
@property(nonatomic,strong)NSString * transactionTime;
@property(nonatomic,strong)NSString * transactionCount;
@property(nonatomic,strong)NSString * transactionTvr;
@property(nonatomic,strong)NSString * transactionTsi;
@property(nonatomic,strong)NSString * transactionAid;
@property(nonatomic,readwrite)int transactionCurrCode;
@property(nonatomic,strong)NSString * transactionCurrencyLabel;
@property(nonatomic,strong)NSString * terminalCurrencyLabel;
@property(nonatomic,strong)NSString * transactionAmount;
@property(nonatomic,strong)NSString * transactionCashback;
@property(nonatomic,strong)NSString * transactionAmountInTerminalCurrency;
@property(nonatomic,strong)NSString * transactionAmountOfTip;
@property(nonatomic,strong)NSString * log;
@property(nonatomic,strong)NSString * transactionTerminalID;
@property(nonatomic,readwrite)BOILogDestination logDestination;
@property(nonatomic,strong)NSString * authCode;
#if TARGET_IPHONE_SIMULATOR
+ (ESAPIResult *) resultDefalultWithtransactionResult: (ecr_transactionResult) transactionResult withCompleteState:(TOTBOIOperationCompleteState)completeState operationType:(BOIOperationType)operationType;
#else
+ (ESAPIResult *) resultFromContext:(EcrCtx*)ecrCtx transactionResult: (ecr_transactionResult) transactionResult withCompleteState:(TOTBOIOperationCompleteState)completeState operationType:(BOIOperationType)operationType;
#endif

@end

@protocol ESCallbacks
-(void) writeLog:(NSString *)message destination:(BOILogDestination)dest;
-(int) notifyClient:(NSString *)prompt;
-(int) askClient:(NSString *)title message:(NSString *)message showCancelButton:(bool)showCancelButton;
-(int) askClientForValue:(NSString *)title message:(NSString *)message valueQuestionData:(ESValueQuestionData *)valueQuestionData;
-(void) notifyAboutStatusChange:(ecr_terminalStatus) status;
-(bool) askClientForSelection:(ESSelectionData *)selectionData;
- (void) transactionComplete:(ESAPIResult *)result;
@end
