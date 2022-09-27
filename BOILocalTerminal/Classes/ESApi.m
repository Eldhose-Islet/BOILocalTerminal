#include <stdbool.h>


#include "printouts.h"
#import "ESApi.h"


#define TXT_BUF_LEN 8192
@implementation ESAPIResult
#if TARGET_IPHONE_SIMULATOR
+ (ESAPIResult *) resultDefalultWithtransactionResult: (ecr_transactionResult) transactionResult withCompleteState:(TOTBOIOperationCompleteState)completeState operationType:(BOIOperationType)operationType{
    ESAPIResult *retVal = [[ESAPIResult alloc] init];
    retVal.completeState = completeState;
    retVal.operationType = operationType;
    retVal.wasContextAvailable = false;
    return  retVal;
}
#else
+ (ESAPIResult *) resultFromContext:(EcrCtx*)ecrCtx transactionResult: (ecr_transactionResult) transactionResult withCompleteState:(TOTBOIOperationCompleteState)completeState operationType:(BOIOperationType)operationType{
    ESAPIResult *retVal = [[ESAPIResult alloc] init];
    retVal.completeState = completeState;
    retVal.operationType = operationType;
    if (!ecrCtx) {
        retVal.wasContextAvailable = false;
        return  retVal;
    }
    retVal.wasContextAvailable = true;
    ecr_status ecrStatus;
    retVal.transactionResult = transactionResult;
//    ecr_transactionResult transactionResult = RESULT_NO_CONNECTION;
    if (transactionResult == RESULT_NO_CONNECTION) {
        // try reading result again
        ecrStatus = ecr_readTransactionResult(ecrCtx, &transactionResult);
        if (ecrStatus == ECR_OK) {
            retVal.transactionResult = transactionResult;
        }
    }
    
    ecr_transactionType type = TRANS_UNKNOWN;
    ecrStatus = ecr_readTransactionType(ecrCtx, &type);
    if (ecrStatus == ECR_OK) {
        retVal.transactionType = type;
    }
    type = TRANS_UNKNOWN;
    ecrStatus = ecr_readOriginalTransactionType(ecrCtx, &type);
    if (ecrStatus == ECR_OK) {
        retVal.transactionTypeOrginal = type;
    }
    CardReaderType cardReadType = READER_UNKNOWN;
    ecrStatus = ecr_readUsedCardReaderType(ecrCtx, &cardReadType);
    if (ecrStatus == ECR_OK) {
        retVal.cardReadType = cardReadType;
    }
    AuthorizationType autharizationType = AUTH_UNKNOWN;
    ecrStatus = ecr_readAuthorizationType(ecrCtx, &autharizationType);
    if (ecrStatus == ECR_OK) {
        retVal.autharizationType = autharizationType;
    }
    AuthorizationMethod authMethod = AUTH_METHOD_UNKNOWN;
    ecrStatus = ecr_readAuthorizationMethod(ecrCtx, &authMethod);
    if (ecrStatus == ECR_OK) {
        retVal.authMethod = authMethod;
    }
    EmvCryptogramType cryptogramType = CRYPT_UNKNOWN;
    ecrStatus = ecr_readEmvCryptogramType(ecrCtx, &cryptogramType);
    if (ecrStatus == ECR_OK) {
        retVal.cryptogramType = cryptogramType;
    }
    bool didTerminalDidPrintOut =  false;
    ecrStatus = ecr_readIfTerminalMadePrinout(ecrCtx, &didTerminalDidPrintOut);
    if (ecrStatus == ECR_OK) {
        retVal.didTerminalDidPrintOut = didTerminalDidPrintOut;
    }
    bool didmanualReveral =  false;
    ecrStatus = ecr_readIfReversalWasManual(ecrCtx, &didmanualReveral);
    if (ecrStatus == ECR_OK) {
        retVal.didmanualReveral = didmanualReveral;
    }
    bool wasTransactionReveral =  false;
    ecrStatus = ecr_readIfTransactionWasReversal(ecrCtx, &wasTransactionReveral);
    if (ecrStatus == ECR_OK) {
        retVal.wasTransactionReveral = wasTransactionReveral;
    }
    
    
    if (transactionResult == RESULT_TRANS_ACCEPTED) {
        uint8_t value[20];
        size_t  len = 20;
        ecrStatus = ecr_readTag(ecrCtx, TAG_TRANSACTION_NUMBER, value, &len);
        if (ecrStatus == ECR_OK) {
            retVal.transactionNumber = [NSString stringWithFormat:@"%s", value];
        }
        len = 20;
        ecrStatus = ecr_readTag(ecrCtx, TAG_TID, value, &len);
        if (ecrStatus == ECR_OK) {
            retVal.transactionTerminalID = [NSString stringWithFormat:@"%s", value];
        }
        len = 20;
        ecrStatus = ecr_readTag(ecrCtx, TAG_AUTHORIZATION_CODE, value, &len);
        if (ecrStatus == ECR_OK) {
            retVal.authCode = [NSString stringWithFormat:@"%s", value];
        }
       
        uint8_t tTerminalID[20];
        len  = 20;
        ecrStatus = ecr_readTerminalId(ecrCtx, tTerminalID, &len);
        if (ecrStatus == ECR_OK) {
            retVal.transactionTerminalID = [NSString stringWithFormat:@"%s", tTerminalID];
        }
        char  transactionDate[15];
        ecrStatus = ecr_readTransactionDate(ecrCtx, transactionDate);
        if (ecrStatus == ECR_OK) {
            retVal.transactionDate = [NSString stringWithUTF8String:transactionDate];
        }
        char  transactionTime[15];
        ecrStatus = ecr_readTransactionTime(ecrCtx, transactionTime);
        if (ecrStatus == ECR_OK) {
            retVal.transactionTime = [NSString stringWithUTF8String:transactionTime];
        }
        char  transactionCount[15];
        ecrStatus = ecr_readTransactionCounter(ecrCtx, transactionCount);
        if (ecrStatus == ECR_OK) {
            retVal.transactionCount = [NSString stringWithUTF8String:transactionCount];
        }
        char  transactionTvr[15];
        ecrStatus = ecr_readTransactionTvr(ecrCtx, transactionTvr);
        if (ecrStatus == ECR_OK) {
            retVal.transactionTvr = [NSString stringWithUTF8String:transactionTvr];
        }
        char  transactionTsi[15];
        ecrStatus = ecr_readTransactionTsi(ecrCtx, transactionTsi);
        if (ecrStatus == ECR_OK) {
            retVal.transactionTvr = [NSString stringWithUTF8String:transactionTsi];
        }
        char  transactionAid[20];
        ecrStatus = ecr_readTransactionTsi(ecrCtx, transactionAid);
        if (ecrStatus == ECR_OK) {
            retVal.transactionAid = [NSString stringWithUTF8String:transactionAid];
        }
        uint16_t  transactionCurrCode = 0;
        ecrStatus = ecr_readTransactionCurrencyCode(ecrCtx, &transactionCurrCode);
        if (ecrStatus == ECR_OK) {
            retVal.transactionCurrCode = transactionCurrCode;
        }
        char  transactionCurrencyLabel[20];
        ecrStatus = ecr_readTransactionCurrencyLabel(ecrCtx, transactionCurrencyLabel);
        if (ecrStatus == ECR_OK) {
            retVal.transactionCurrencyLabel = [NSString stringWithUTF8String:transactionCurrencyLabel];
        }
        char  terminalCurrencyLabel[20];
        ecrStatus = ecr_readTerminalCurrencyLabel(ecrCtx, terminalCurrencyLabel);
        if (ecrStatus == ECR_OK) {
            retVal.terminalCurrencyLabel = [NSString stringWithUTF8String:terminalCurrencyLabel];
        }
    }
   
    char  transactionAmount[20];
    ecrStatus = ecr_readTransactionAmount(ecrCtx, transactionAmount);
    if (ecrStatus == ECR_OK) {
        retVal.transactionAmount = [NSString stringWithUTF8String:transactionAmount];
    }
    char  transactionAmountInTerminalCurrency[20];
    ecrStatus = ecr_readTransactionAmountInTerminalCurrency(ecrCtx, transactionAmountInTerminalCurrency);
    if (ecrStatus == ECR_OK) {
        retVal.transactionAmountInTerminalCurrency = [NSString stringWithUTF8String:transactionAmountInTerminalCurrency];
    }
    char  transactionCashback[20];
    ecrStatus = ecr_readTransactionCashback(ecrCtx, transactionCashback);
    if (ecrStatus == ECR_OK) {
        retVal.transactionCashback = [NSString stringWithUTF8String:transactionCashback];
    }
    char  transactionAmountOfTip[20];
    ecrStatus = ecr_readTransactionAmountOfTip(ecrCtx, transactionAmountOfTip);
    if (ecrStatus == ECR_OK) {
        retVal.transactionAmountOfTip = [NSString stringWithUTF8String:transactionAmountOfTip];
    }
    // terminal status will be set by parent
    retVal.terminalStatus = STATUS_UNKNOWN;
//    ecr_terminalStatus terminalStatus = STATUS_UNKNOWN;
//    ecrStatus = ecr_readTerminalStatus(ecrCtx, &terminalStatus);
//    if (ecrStatus == ECR_OK) {
//        retVal.terminalStatus = terminalStatus;
//    }
    return retVal;
}
#endif
@end
@implementation ESApi

/* [[ C global variables */
id thisClass;
#if !TARGET_IPHONE_SIMULATOR
EcrCtx   * ecrContext_;
#endif
ecr_terminalStatus ecrTerminalStatus_;
/* ]] C global variables */

- (ESApi *)init
{
    return NULL;
}
- (ESApi *)initWithCallbacks:(id<ESCallbacks>)callbacks
{
    if (self = [super init]) {
#if !(TARGET_IPHONE_SIMULATOR)
        ecrContext_ = NULL;
#endif
        ecrTerminalStatus_ = STATUS_UNKNOWN;
        escb = callbacks;
        thisClass = self;
        _apiTextEncoding = NSWindowsCP1252StringEncoding;
    }
    return self;
}
/* [[ internal C api */
#if !(TARGET_IPHONE_SIMULATOR)
static bool esApiInit(const char * ip);
static void esApiStop(void);
static void esApiSale(const char * amount);
static void esApiReversal(const char * transaction, const char * amount);
static void esApiLastTrxData(void);
static void esApiReconciliation(void);
static void esApiShowStatus(void);
#endif
/* ]] internal C api */
/* [[ objective C -> C */
- (bool)ApiInit:(NSString *)terminalIp
{
    char ip[TXT_BUF_LEN] = { 0 };
    if ([self getCharStr:ip destLen:sizeof(ip) src:terminalIp])
    {
#if !(TARGET_IPHONE_SIMULATOR)
        return esApiInit(ip);
#endif
    }
    return false;
}

- (void)ApiStop
{
#if !(TARGET_IPHONE_SIMULATOR)
    esApiStop();
#endif
}

- (void)ApiSale:(NSString *)transactionAmount
{
    char amount[TXT_BUF_LEN];
    if ([self getCharStr:amount destLen:sizeof(amount) src:transactionAmount])
    {
#if !(TARGET_IPHONE_SIMULATOR)
        esApiSale(amount);
#endif
    }
}

- (void)ApiReversal:(NSString *)transactionId amount:(NSString *)transactionAmount
{
    char transaction[TXT_BUF_LEN] = { 0 };
    char amount[TXT_BUF_LEN] = { 0 };
    if ([self getCharStr:transaction destLen:sizeof(transaction) src:transactionId]
     && [self getCharStr:amount destLen:sizeof(amount) src:transactionAmount])
    {
#if !(TARGET_IPHONE_SIMULATOR)
        esApiReversal(transaction, amount);
#endif
    }
}

- (void)ApiPrintLastTrx
{
#if !(TARGET_IPHONE_SIMULATOR)
    esApiLastTrxData();
#endif
}

- (void)ApiReconciliation
{
#if !(TARGET_IPHONE_SIMULATOR)
    esApiReconciliation();
#endif
}

- (void)ApiDumpStatusToLog
{
#if !(TARGET_IPHONE_SIMULATOR)
    esApiShowStatus();
#endif
}

- (NSString *)ApiGetStatusDescription:(int)status
{
    char * resp = "UNKNOWN";
    switch (status)
    {
        case STATUS_READY_FOR_NEW_TRAN:
            resp = "READY_FOR_NEW_TRAN"; break;
        case STATUS_WAITING_FOR_CARD:
            resp = "WAITING_FOR_CARD"; break;
        case STATUS_WAITING_FOR_PIN:
            resp = "WAITING_FOR_PIN"; break;
        case STATUS_WAITING_FOR_EMV_CHOICE:
            resp = "WAITING_FOR_EMV_CHOICE"; break;
        case STATUS_WAITING_FOR_HOST:
            resp = "WAITING_FOR_HOST"; break;
        case STATUS_WAITING_FOR_SINGATURE:
            resp = "WAITING_FOR_SINGATURE"; break;
        case STATUS_WAITING_FOR_TRAN_END:
            resp = "WAITING_FOR_TRAN_END"; break;
        case STATUS_WAITING_FOR_CARD_REMOVAL:
            resp = "WAITING_FOR_CARD_REMOVAL"; break;
        case STATUS_BUSY:
            resp = "BUSY"; break;
        case STATUS_IN_PROGRESS:
            resp = "IN_PROGRESS"; break;
        case STATUS_WAITING_FOR_COPY:
            resp = "WAITING_FOR_COPY"; break;
        case STATUS_WAITING_FOR_AUTH_CODE:
            resp = "WAITING_FOR_AUTH_CODE"; break;
        case STATUS_WAITING_FOR_USER_ACTION:
            resp = "WAITING_FOR_USER_ACTION"; break;
        case STATUS_BATCH_COMPLETED:
            resp = "BATCH_COMPLETED"; break;
        case STATUS_SELECTING_CURRENCY:
            resp = "SELECTING_CURRENCY"; break;
        case STATUS_WAITING_FOR_CASHBACK:
            resp = "WAITING_FOR_CASHBACK"; break;
        case STATUS_TRAN_ACCEPTED:
            resp = "TRAN_ACCEPTED"; break;
        case STATUS_WAITING_FOR_AMOUNT:
            resp = "WAITING_FOR_AMOUNT"; break;
        case STATUS_WAITING_FOR_SELECTION:
            resp = "WAITING_FOR_SELECTION"; break;
        case STATUS_APP_ERROR:
            resp = "APP_ERROR"; break;
        case STATUS_RECON_NEEDED:
            resp = "RECON_NEEDED"; break;
        default:;
    }

    return [NSString stringWithCString:resp encoding:NSUTF8StringEncoding];
}
/* ]] objective C -> C */
/* [[ C -> objective C */
/* objC */
- (id)eSCallbackObj
{
    return escb;
}

- (bool)ifExistsESCallbackObj
{
    return (NULL != escb);
}
- (void)oC_sendTransactionResultMainThread:(ecr_transactionResult)result completeState:(TOTBOIOperationCompleteState) completeState operationType:(BOIOperationType)operationType log:(const char *)log dest:(BOILogDestination)dest
{
    if ([self ifExistsESCallbackObj])
    {
#if (TARGET_IPHONE_SIMULATOR)
        ESAPIResult * resultObj = [ESAPIResult  resultDefalultWithtransactionResult: result  withCompleteState:completeState operationType:operationType];
#else
        ESAPIResult * resultObj = [ESAPIResult resultFromContext:ecrContext_ transactionResult: result  withCompleteState:completeState operationType:operationType];
#endif
        
        resultObj.transactionResult = result;
        resultObj.terminalStatus = ecrTerminalStatus_;
        resultObj.log = [NSString stringWithFormat: @"%s", log ];
        resultObj.logDestination = dest;
        [[self eSCallbackObj] transactionComplete:resultObj];
    }
}

- (void)oC_displayLogOnMainThreadFromOutside:(const char *)log dest:(BOILogDestination)dest
{
    if ([self ifExistsESCallbackObj]
        && (NULL != log))
    {
        [[self eSCallbackObj] writeLog:[NSString stringWithFormat: @"%s", log ] destination:dest];
    }
}

- (int)oC_notifyClient:(const char *)arg_prompt
{
    if ([self ifExistsESCallbackObj]
        && (NULL != arg_prompt))
    {
        NSString *_prompt = [[NSString alloc]initWithCString:arg_prompt encoding:_apiTextEncoding];
        return [[self eSCallbackObj] notifyClient:_prompt];
    }
    return -1;
}

- (int)oC_askClient:(bool)arg_showCancelButton arg_title:(const char *)arg_title arg_message:(const char *)arg_message
{
    if ([self ifExistsESCallbackObj]
        && (NULL != arg_title)
        && (NULL != arg_message))
    {
        NSString *_title = [[NSString alloc]initWithCString:arg_title encoding:_apiTextEncoding];
        NSString *_message = [[NSString alloc]initWithCString:arg_message encoding:_apiTextEncoding];
        return [[self eSCallbackObj] askClient:_title
                                          message:_message
                                          showCancelButton:arg_showCancelButton];
    }
    return -1;
}
#if !(TARGET_IPHONE_SIMULATOR)
- (int)oC_askClientForValue:(const char *)arg_title arg_message:(const char *)arg_message value:(cb_UserProvidedData *)value charAllowedCallback:(cb_isCharacterAllowed)charAllowedCallback
{
    if ([self ifExistsESCallbackObj]
        && (NULL != arg_title)
        && (NULL != arg_message))
    {
        NSString *_title = [[NSString alloc]initWithCString:arg_title encoding:_apiTextEncoding];
        NSString *_message = [[NSString alloc]initWithCString:arg_message encoding:_apiTextEncoding];

        ESValueQuestionData * _valueQuestionData = NULL;
        if (NULL != value)
        {
            _valueQuestionData = [[ESValueQuestionData alloc] init];
            _valueQuestionData.userData = value->userData;
            _valueQuestionData.userDataLen = sizeof(value->userData);
            _valueQuestionData.maxLen = value->maxLen;
            _valueQuestionData.minLen = value->minLen;
            _valueQuestionData.isCharacterAllowed = charAllowedCallback;
            _valueQuestionData.apiTextEncoding = _apiTextEncoding;
        }

        return [[self eSCallbackObj] askClientForValue:_title
                                          message:_message
                                          valueQuestionData:_valueQuestionData];
    }
    return -1;
}

- (void)oC_notifyAboutStatusChange:(ecr_terminalStatus)arg_status
{
    if ([self ifExistsESCallbackObj])
    {
        return [[self eSCallbackObj] notifyAboutStatusChange:arg_status];
    }
}

- (bool)oC_askClientForSelection:(const char**)choices choicesSize:(size_t)choicesSize userChoice:(uint32_t*)userChoice text:(const char*)text
{
    if ([self ifExistsESCallbackObj]
        && (NULL != choices))
    {
        ESSelectionData * _selectionData = [[ESSelectionData alloc] init];
        _selectionData.choices = choices;
        _selectionData.choicesSize = choicesSize;
        _selectionData.userChoice = userChoice;
        _selectionData.text = text;

        return [[self eSCallbackObj] askClientForSelection:_selectionData];
    }
    return false;
}

/* C */
void displayLogOnMainThreadFromOutside(const char * log, BOILogDestination dest)
{
    [thisClass oC_displayLogOnMainThreadFromOutside:log dest:dest];
}

void sendTransactionResultMainThreadFromOutside(ecr_transactionResult result , TOTBOIOperationCompleteState completeState,BOIOperationType operationType,const char * log, BOILogDestination dest)
{
    [thisClass oC_sendTransactionResultMainThread:result completeState:completeState operationType:operationType log:log dest:dest];
}

int notifyClient(const char * arg_prompt)
{
    return [thisClass oC_notifyClient:arg_prompt];
}

int askClient(bool arg_showCancelButton, const char * arg_title, const char * arg_message)
{
    return [thisClass oC_askClient:arg_showCancelButton arg_title:arg_title arg_message:arg_message];
}

int askClientForValue(const char * arg_title, const char * arg_message, cb_UserProvidedData * value, cb_isCharacterAllowed charAllowedCallback)
{
    return [thisClass oC_askClientForValue:arg_title arg_message:arg_message value:value charAllowedCallback:charAllowedCallback];
}

void notifyAboutStatusChange(ecr_terminalStatus arg_status)
{
    [thisClass oC_notifyAboutStatusChange:arg_status];
}

bool askClientForSelection(const char** choices, size_t choicesSize, uint32_t* userChoice, const char* text)
{
    return [thisClass oC_askClientForSelection:choices choicesSize:choicesSize userChoice:userChoice text:text];
}

/* ]] C -> objective C */
/* [[ API, C */

#define PRINTER_LINE_LEN       48
#define PRINTER_LINE_LEN_SMALL 32
#define PRINTER_LINE_LEN_BIG   64

static void esApiHandlePrintout(void);
static void esApiHandleiClosingDayPrintout(void);
static void esApiShowPrintout(PrintoutCtx* ctx);
static bool esApiCheckTerminalStatus(void);
static bool esApiCheckIfReady(void);

static void int_destroy_api(EcrCtx* ctx);
static void int_assign_callbacks(void);
static bool askForCopy(const char* prompt);
static bool askForSignature(const char* prompt);
static bool showYesNoScreen(const char* prompt);
static void waitForCardRemoval(const char* prompt);
static void showPromptScreen(const char* prompt);
static bool waitForCard(const char* prompt);
static bool waitForPin(const char* prompt);
static void handleStatusChange(ecr_terminalStatus status);
static void showOkScreen(const char* prompt);
static void getCashbackAmount(const char* prompt, cb_UserProvidedData *amount);
static void getAuthorizationCode(const char* prompt, cb_UserProvidedData *code);
static void getAmount(const char* prompt, cb_UserProvidedData *amount);
static void getUserData(const char* prompt, cb_UserProvidedData *amount, cb_isCharacterAllowed charAllowedCallback);
static bool askForCurrency(const char** currencies, size_t currenciesSize, uint32_t* userChoice);
static bool askForSelection(const char** choices, size_t choicesSize, uint32_t* userChoice, const char* text);
static void handleBusLog(const char* log);
static void handleDevLog(const char* log);
static void handleCommLog(const char* log);

bool esApiInit(const char * ip)
{
    ecrTerminalStatus_ = STATUS_UNKNOWN;

    uint8_t cashRegisterNumber[] = { '1' };
    ecr_status st_initialize = 0,
               st_settcp = 0,
               st_setcashreg = 0,
               st_sethandlet = 0;

    if (NULL != ecrContext_)
    {
        displayLogOnMainThreadFromOutside("\nAPI already started\n",     BOILogDestinationAPI);
        return true;
    }
    displayLogOnMainThreadFromOutside("\nStart API\n",     BOILogDestinationAPI);
    if (!ip || !(ip[0]))
    {
        const char * log = "\nNo IP\n";
        displayLogOnMainThreadFromOutside(log,     BOILogDestinationAPI);
        sendTransactionResultMainThreadFromOutside(RESULT_NO_CONNECTION,TOTBOIOperationCompleteStateNoIp,BOIOperationTypeTerminalInitalization,log,     BOILogDestinationAPI);
        return false;
    }
    int_assign_callbacks();
    st_initialize = ecr_initialize(&ecrContext_);
    if (ECR_OK != st_initialize)
    {
        const char * log = "\nAPI initialization failed (initialize)\n";
        displayLogOnMainThreadFromOutside(log,     BOILogDestinationAPI);
        sendTransactionResultMainThreadFromOutside(RESULT_NO_CONNECTION,TOTBOIOperationCompleteStateInitalizationFailed,BOIOperationTypeTerminalInitalization,log, BOILogDestinationAPI);
        esApiStop();
        return false;
    }

    ecr_setProtocol(ecrContext_, PROTOCOL_ESERVICE);

    st_settcp = ecr_setTcpIpLink(ecrContext_, ip, 3000, 15000);
    if (ECR_OK != st_settcp)
    {
        const char * log = "\nAPI initialization failed (setTcpIpLink)\n";
        displayLogOnMainThreadFromOutside(log,     BOILogDestinationAPI);
        sendTransactionResultMainThreadFromOutside(RESULT_NO_CONNECTION,TOTBOIOperationCompleteStateSetTcpIpLinkInitalizationFailed,BOIOperationTypeTerminalInitalization,log,     BOILogDestinationAPI);
        esApiStop();
        return false;
    }
    st_setcashreg = ecr_setCashRegisterId(ecrContext_, cashRegisterNumber, sizeof(cashRegisterNumber));
    if (ECR_OK != st_setcashreg)
    {
        const char * log = "\nAPI initialization failed (setCashRegisterId)\n";
        displayLogOnMainThreadFromOutside(log,     BOILogDestinationAPI);
        sendTransactionResultMainThreadFromOutside(RESULT_NO_CONNECTION,TOTBOIOperationCompleteStateSetCashRegisterIdInitalizationFailed,BOIOperationTypeTerminalInitalization,log,     BOILogDestinationAPI);
        esApiStop();
        return false;
    }
    st_sethandlet = ecr_setHandleTerminalRequests(ecrContext_, REQUESTS_HANDLE_ALL);
    if (ECR_OK != st_sethandlet)
    {
        const char * log = "\nAPI initialization failed (setHandleTerminalRequests)\n";
        displayLogOnMainThreadFromOutside(log,     BOILogDestinationAPI);
        sendTransactionResultMainThreadFromOutside(RESULT_NO_CONNECTION,TOTBOIOperationCompleteStateSetHandleTerminalRequestsInitalizationFailed,BOIOperationTypeTerminalInitalization,log,     BOILogDestinationAPI);
        esApiStop();
        return false;
    }

    NSString *resDir = [[NSBundle mainBundle] resourcePath];
    pr_setLanguageFilesDefaultPath([resDir UTF8String]);
    pr_setupDictionaryFromFile("EN.LNG");

    return true;
}

void esApiShowStatus()
{
    ecr_status st_gettstat = 0,
               st_rterms = 0;
    char txt[1024] = { 0 };

    if (NULL == ecrContext_)
    {
        const char * log = "No ecrContext\n";
        displayLogOnMainThreadFromOutside(log,BOILogDestinationAPI);
        sendTransactionResultMainThreadFromOutside(RESULT_NO_CONNECTION,TOTBOIOperationCompleteStateNoErContext,BOIOperationTypeCheckStatus,log,     BOILogDestinationAPI);
        return;
    }
    st_gettstat = ecr_getTerminalStatus(ecrContext_);
    if (ECR_OK != st_gettstat)
    {
        const char * log = "\nAPI getTerminalStatus failed\n";
        displayLogOnMainThreadFromOutside(log,     BOILogDestinationAPI);
        sendTransactionResultMainThreadFromOutside(RESULT_NO_CONNECTION,TOTBOIOperationCompleteStateGetTreminalStatusFailed,BOIOperationTypeCheckStatus,log,BOILogDestinationAPI);
        return;
    }
    ecrTerminalStatus_ = STATUS_UNKNOWN;
    st_rterms = ecr_readTerminalStatus(ecrContext_, &ecrTerminalStatus_);
    if (ECR_OK != st_rterms)
    {
        const char * log = "\nAPI readTerminalStatus failed\n";
        displayLogOnMainThreadFromOutside(log,     BOILogDestinationAPI);
        sendTransactionResultMainThreadFromOutside(RESULT_NO_CONNECTION,TOTBOIOperationCompleteStateReadTreminalStatusFailed,BOIOperationTypeCheckStatus,log,BOILogDestinationAPI);
        return;
    }
    snprintf(txt, sizeof(txt), "\nTerminalStatus: %d\n", (int)ecrTerminalStatus_);
    sendTransactionResultMainThreadFromOutside(RESULT_TRANS_ACCEPTED,TOTBOIOperationCompleteStateSucess,BOIOperationTypeCheckStatus,"Sucess",BOILogDestinationAPI);
    displayLogOnMainThreadFromOutside(txt,     BOILogDestinationAPI);
}

void esApiStop()
{

    ecr_status st_clo = 0;

    displayLogOnMainThreadFromOutside("\nStop API\n",     BOILogDestinationAPI);
    if (NULL == ecrContext_)
    {
        displayLogOnMainThreadFromOutside("No ecrContext\n",     BOILogDestinationAPI);
        return;
    }
    st_clo = ecr_closeConnection(ecrContext_);
    int_destroy_api(ecrContext_);
    ecrContext_ = NULL;
}

bool esApiCheckIfReady()
{
    int tryCnt = 3;
    bool checkResult = true;
    ecr_status ret = ECR_OK;
    char txt[1024] = { 0 };

    while ((checkResult = esApiCheckTerminalStatus()) && (STATUS_READY_FOR_NEW_TRAN != ecrTerminalStatus_) && (0 < tryCnt))
    {
        if (STATUS_BATCH_COMPLETED == ecrTerminalStatus_)
        {
            ret = ecr_getBatchSummary(ecrContext_);
            if (ECR_OK != ret)
            {
                return false;
            }
            ecr_batchStatus batchStatus;
            ret = ecr_readBatchStatus(ecrContext_, &batchStatus);
            if (ECR_OK != ret)
            {
                return false;
            }
            continue;
        }
        ret = ecr_continueTransaction(ecrContext_);
        if (ECR_OK != ret)
        {
            return false;
        }
        tryCnt--;
        snprintf(txt, sizeof(txt), "TRY_CNT: (%d)\n", tryCnt);
        displayLogOnMainThreadFromOutside(txt,     BOILogDestinationAPI);
    }
    if (!checkResult)
    {
        displayLogOnMainThreadFromOutside("\nFailed to check terminal status\n",     BOILogDestinationAPI);
    }
    return (STATUS_READY_FOR_NEW_TRAN == ecrTerminalStatus_);
}

void esApiHandlePrintout()
{
    PrintoutCtx* ctx = NULL;
    pr_Result result = pr_initPrintoutCtx(&ctx);

    if (result != PRINTOUT_OK)
    {
        const char * log = "\nerror initalizing printout\n";
        sendTransactionResultMainThreadFromOutside(RESULT_NO_CONNECTION,TOTBOIOperationCompleteStateErrorInitalizingPrintOut,BOIOperationTypePrintOut,log,BOILogDestinationAPI);
        return;
    }
    pr_setNormalLineLen(ctx, PRINTER_LINE_LEN);
    pr_setSmallLineLen(ctx, PRINTER_LINE_LEN_SMALL);
    pr_setBigLineLen(ctx, PRINTER_LINE_LEN_BIG);

    result = pr_prepareTransactionPrintout(ctx, ecrContext_, false);
    if (result != PRINTOUT_OK)
    {
        pr_cleanPrintoutCtx(&ctx);
        const char * log = "\nerror preparing printout\n";
        displayLogOnMainThreadFromOutside(log,     BOILogDestinationAPI);
        sendTransactionResultMainThreadFromOutside(RESULT_NO_CONNECTION,TOTBOIOperationCompleteStateErrorPreparingPrintOut,BOIOperationTypePrintOut,log,     BOILogDestinationAPI);
        return;
    }

    esApiShowPrintout(ctx);
    pr_cleanPrintoutCtx(&ctx);
}

void esApiHandleiClosingDayPrintout()
{
    PrintoutCtx* ctx = NULL;
    pr_Result result = pr_initPrintoutCtx(&ctx);
    unsigned int iterator = 1;
    ecr_status ret = ECR_OK;

    if (result != PRINTOUT_OK)
    {
        const char * log = "\nerror preparing printout\n";
        displayLogOnMainThreadFromOutside(log, BOILogDestinationAPI);
        sendTransactionResultMainThreadFromOutside(RESULT_NO_CONNECTION,TOTBOIOperationCompleteStateErrorPreparingPrintOut,BOIOperationTypeClosingDayPrintOut,log,BOILogDestinationAPI);
        return;
    }

    pr_setNormalLineLen(ctx, PRINTER_LINE_LEN);
    pr_setSmallLineLen(ctx, PRINTER_LINE_LEN_SMALL);
    pr_setBigLineLen(ctx, PRINTER_LINE_LEN_BIG);

    result = pr_startClosingDay(ctx, ecrContext_);
    if (result != PRINTOUT_OK)
    {
        pr_cleanPrintoutCtx(&ctx);
        const char * log = "\nerror starting printout\n";
        displayLogOnMainThreadFromOutside(log,     BOILogDestinationAPI);
        sendTransactionResultMainThreadFromOutside(RESULT_NO_CONNECTION,TOTBOIOperationCompleteStateErrorStartingPrintOut,BOIOperationTypeClosingDayPrintOut,log,BOILogDestinationAPI);
        return;
    }

    while(true)
    {
        ret = ecr_setTransactionId(ecrContext_, iterator);
        iterator++;
        if (ECR_OK != ret)
        {
            break;
        }
        ret = ecr_getSingleTransactionFromBatch(ecrContext_);
        if (ECR_OK != ret)
        {
            break;
        }
        result = pr_addClosingDayTransaction(ctx, ecrContext_);
        if (result != PRINTOUT_OK)
        {
            break;
        }
    }

    ret = ecr_getBatchSummary(ecrContext_);

    pr_finishClosingDay(ctx, ecrContext_);
    esApiShowPrintout(ctx);
    pr_cleanPrintoutCtx(&ctx);
}

void esApiShowPrintout(PrintoutCtx* ctx)
{
    char txt[1024] = { 0 };
    unsigned int lines = pr_getNumberOfLines(ctx);

    if (0 < lines)
    {
        pr_Line line;
        memset(&line, 0, sizeof(line));
        while (pr_getNextLine(ctx, &line) == PRINTOUT_OK)
        {
            snprintf(txt, sizeof(txt), "%s\n", line.text);
            displayLogOnMainThreadFromOutside(txt,BOILogDestinationPrintout);
            memset(&line, 0, sizeof(line));
        }
    }
}

void esApiSale(const char * amount)
{
    char txt[1024] = { 0 };

    if (!amount || !(amount[0]))
    {
        const char * log = "\nNo amount\n";
        displayLogOnMainThreadFromOutside(log,     BOILogDestinationAPI);
        sendTransactionResultMainThreadFromOutside(RESULT_NO_CONNECTION,TOTBOIOperationCompleteStateInValidAmount,BOIOperationTypeSale,log,     BOILogDestinationAPI);
        return;
    }

    if (!esApiCheckIfReady())
    {
        const char * log = "\nTerminal not ready\n";
        displayLogOnMainThreadFromOutside(log,     BOILogDestinationAPI);
        sendTransactionResultMainThreadFromOutside(RESULT_NO_CONNECTION,TOTBOIOperationCompleteStateTerminalNotReady,BOIOperationTypeSale,log,     BOILogDestinationAPI);
        return;
    }

    ecr_status ecrStatus = ecr_setTransactionType(ecrContext_, TRANS_SALE);
    if (ECR_OK != ecrStatus)
    {
        const char * log = "\nError setting transaction type\n";
        displayLogOnMainThreadFromOutside(log,BOILogDestinationAPI);
        sendTransactionResultMainThreadFromOutside(RESULT_NO_CONNECTION,TOTBOIOperationCompleteStateErrorSetTransactionType,BOIOperationTypeSale,log,     BOILogDestinationAPI);
        return;
    }
    ecrStatus = ecr_setTransactionAmount(ecrContext_, amount);
    if (ECR_OK != ecrStatus)
    {
        const char * log = "\nError setting amount\n";
        displayLogOnMainThreadFromOutside(log,BOILogDestinationAPI);
        sendTransactionResultMainThreadFromOutside(RESULT_NO_CONNECTION,TOTBOIOperationCompleteStateErrorSettingAmount,BOIOperationTypeSale,log,BOILogDestinationAPI);
        return;
    }
    ecrStatus = ecr_startTransaction(ecrContext_);
    if (ECR_OK != ecrStatus)
    {
        const char * log = "\nError transaction processing\n";
        displayLogOnMainThreadFromOutside(log,BOILogDestinationAPI);
        sendTransactionResultMainThreadFromOutside(RESULT_NO_CONNECTION,TOTBOIOperationCompleteStateErrorStartingTransactionProcess,BOIOperationTypeSale,log,BOILogDestinationAPI);
        return;
    }

    ecr_transactionResult result = RESULT_NO_CONNECTION;
    ecrStatus = ecr_readTransactionResult(ecrContext_, &result);
    if (ECR_OK != ecrStatus)
    {
        snprintf(txt, sizeof(txt), "Sale result unknown\n");
    } else {
        snprintf(txt, sizeof(txt), "Sale result (%d)\n", (int)result);
    }
    sendTransactionResultMainThreadFromOutside(result,TOTBOIOperationCompleteStateSucess,BOIOperationTypeSale,"Sucess",BOILogDestinationAPI);
    displayLogOnMainThreadFromOutside(txt,     BOILogDestinationAPI);
    esApiHandlePrintout();
}

void esApiReversal(const char * transaction, const char * amount)
{
    char txt[1024] = { 0 };

    if (!amount || !(amount[0]) || !transaction || !(transaction[0]))
    {
        const char * log = "\nNo transaction or amount\n";
        displayLogOnMainThreadFromOutside(log,     BOILogDestinationAPI);
        sendTransactionResultMainThreadFromOutside(RESULT_NO_CONNECTION,TOTBOIOperationCompleteStateInValidAmount,BOIOperationTypeReversal,log,BOILogDestinationAPI);
        return;
    }
    if (!esApiCheckIfReady())
    {
        const char * log = "\nTerminal not ready\n";
        displayLogOnMainThreadFromOutside(log,     BOILogDestinationAPI);
        sendTransactionResultMainThreadFromOutside(RESULT_NO_CONNECTION,TOTBOIOperationCompleteStateTerminalNotReady,BOIOperationTypeReversal,log,     BOILogDestinationAPI);
        return;
    }
    ecr_status ecrStatus = ecr_setTransactionType(ecrContext_, TRANS_REVERSAL);
    if (ECR_OK != ecrStatus)
    {
        const char * log = "\nError setting transaction type\n";
        displayLogOnMainThreadFromOutside(log,     BOILogDestinationAPI);
        sendTransactionResultMainThreadFromOutside(RESULT_NO_CONNECTION,TOTBOIOperationCompleteStateErrorSetTransactionType,BOIOperationTypeReversal,log,     BOILogDestinationAPI);
        return;
    }
    ecrStatus = ecr_setNumberOfTransactionToReverse(ecrContext_, transaction);
    if (ECR_OK != ecrStatus)
    {
        const char * log = "\nError setting number of transaction\n";
        displayLogOnMainThreadFromOutside(log, BOILogDestinationAPI);
        sendTransactionResultMainThreadFromOutside(RESULT_NO_CONNECTION,TOTBOIOperationCompleteStateErrorSetingTransactionNumber,BOIOperationTypeReversal,log, BOILogDestinationAPI);
        return;
    }
    ecrStatus = ecr_setTransactionAmount(ecrContext_, amount);
    if (ECR_OK != ecrStatus)
    {
        const char * log = "\nError setting amount\n";
        displayLogOnMainThreadFromOutside(log,     BOILogDestinationAPI);
        sendTransactionResultMainThreadFromOutside(RESULT_NO_CONNECTION,TOTBOIOperationCompleteStateErrorSettingAmount,BOIOperationTypeReversal,log,     BOILogDestinationAPI);
        return;
    }
    ecrStatus = ecr_startTransaction(ecrContext_);
    if (ECR_OK != ecrStatus)
    {
        const char * log = "\nError transaction processing\n";
        displayLogOnMainThreadFromOutside(log,     BOILogDestinationAPI);
        sendTransactionResultMainThreadFromOutside(RESULT_NO_CONNECTION,TOTBOIOperationCompleteStateErrorStartingTransactionProcess,BOIOperationTypeReversal,log,BOILogDestinationAPI);
        return;
    }
    ecr_transactionResult result = RESULT_NO_CONNECTION;
    ecrStatus = ecr_readTransactionResult(ecrContext_, &result);
    if (ECR_OK != ecrStatus)
    {
        snprintf(txt, sizeof(txt), "Reversal result unknown\n");
    } else {
        snprintf(txt, sizeof(txt), "Reversal result (%d)\n", (int)result);
    }
    displayLogOnMainThreadFromOutside(txt,     BOILogDestinationAPI);
    sendTransactionResultMainThreadFromOutside(result,TOTBOIOperationCompleteStateSucess,BOIOperationTypeReversal,"Sucess",BOILogDestinationAPI);
    esApiHandlePrintout();
}

void esApiLastTrxData(void)
{
    if (!esApiCheckIfReady())
    {
        const char * log = "\nTerminal not ready\n";
        displayLogOnMainThreadFromOutside(log,     BOILogDestinationAPI);
        sendTransactionResultMainThreadFromOutside(RESULT_NO_CONNECTION,TOTBOIOperationCompleteStateTerminalNotReady,BOIOperationTypeLastTrxData,log,     BOILogDestinationAPI);
        return;
    }
    ecr_status ecrStatus = ecr_getLastTransactionData(ecrContext_);
    if (ECR_OK != ecrStatus)
    {
        const char * log = "\nError transaction processing\n";
        displayLogOnMainThreadFromOutside(log,     BOILogDestinationAPI);
        sendTransactionResultMainThreadFromOutside(RESULT_NO_CONNECTION,TOTBOIOperationCompleteStateErrorStartingTransactionProcess,BOIOperationTypeLastTrxData,log,BOILogDestinationAPI);
        return;
    }
    ecr_transactionResult result = RESULT_NO_CONNECTION;
    ecrStatus = ecr_readTransactionResult(ecrContext_, &result);
    sendTransactionResultMainThreadFromOutside(result,TOTBOIOperationCompleteStateSucess,BOIOperationTypeLastTrxData,"Sucess",BOILogDestinationAPI);
    esApiHandlePrintout();
}

void esApiReconciliation(void)
{
    char txt[1024] = { 0 };

    if (!esApiCheckIfReady())
    {
        const char * log = "\nTerminal not ready\n";
        displayLogOnMainThreadFromOutside(log,     BOILogDestinationAPI);
        sendTransactionResultMainThreadFromOutside(RESULT_NO_CONNECTION,TOTBOIOperationCompleteStateTerminalNotReady,BOIOperationTypeReconciliation,log,     BOILogDestinationAPI);
        return;
    }
    ecr_status ecrStatus = ecr_setTransactionType(ecrContext_, TRANS_RECONCILE);
    if (ECR_OK != ecrStatus)
    {
        const char * log = "\nError setting transaction type\n";
        displayLogOnMainThreadFromOutside(log,     BOILogDestinationAPI);
        sendTransactionResultMainThreadFromOutside(RESULT_NO_CONNECTION,TOTBOIOperationCompleteStateErrorSetTransactionType,BOIOperationTypeReconciliation,log,BOILogDestinationAPI);
        return;
    }
    ecrStatus = ecr_startTransaction(ecrContext_);
    if (ECR_OK != ecrStatus)
    {
        const char * log = "\nError transaction processing\n";
        displayLogOnMainThreadFromOutside(log,     BOILogDestinationAPI);
        sendTransactionResultMainThreadFromOutside(RESULT_NO_CONNECTION,TOTBOIOperationCompleteStateErrorStartingTransactionProcess,BOIOperationTypeReconciliation,log,BOILogDestinationAPI);
        return;
    }
    ecr_transactionResult result = RESULT_NO_CONNECTION;
    ecrStatus = ecr_readTransactionResult(ecrContext_, &result);
    if (ECR_OK != ecrStatus)
    {
        snprintf(txt, sizeof(txt), "Reconciliation result unknown\n");
    } else {
        snprintf(txt, sizeof(txt), "Reconciliation result (%d)\n", (int)result);
    }
    sendTransactionResultMainThreadFromOutside(result,TOTBOIOperationCompleteStateSucess,BOIOperationTypeReconciliation,"Sucess",BOILogDestinationAPI);
    displayLogOnMainThreadFromOutside(txt,     BOILogDestinationAPI);
    esApiHandleiClosingDayPrintout();
}

bool esApiCheckTerminalStatus()
{
    int i = 0;
    for (i = 0; i < 3; i++) {
        ecr_status ecrStatus = ecr_getTerminalStatus(ecrContext_);

        if (ECR_TIMEOUT == ecrStatus) {
            continue;
        }
        if (ECR_OK == ecrStatus) {
            break;
        }
        return false;
    }
    if (ECR_OK == ecr_readTerminalStatus(ecrContext_, &ecrTerminalStatus_))
    {
        return true;
    }
    return false;
}

static void int_destroy_api(EcrCtx* ctx)
{
    ecr_cleanup(&ctx);
}

static void int_assign_callbacks(void)
{

    cb_setSignatureRequest(askForSignature);
    cb_setCopyRequest(askForCopy);
    cb_setShowYesNoScreen(showYesNoScreen);
    cb_setWaitForCardRemoval(waitForCardRemoval);
    cb_setShowPromptScreen(showPromptScreen);
    cb_setShowOkScreen(showOkScreen);
    cb_setWaitForCard(waitForCard);
    cb_setWaitForPin(waitForPin);
    cb_setGetCashbackAmount(getCashbackAmount);
    cb_setGetAmount(getAmount);
    cb_setGetAuthorizationCode(getAuthorizationCode);
    cb_setGetUserData(getUserData);
    cb_setCurrencyRequest(askForCurrency);
    cb_setSelectRequest(askForSelection);
    cb_setHandleStatusChange(handleStatusChange);
    cb_setHandleBusLog(handleBusLog);
    cb_setHandleDevLog(handleDevLog);
    cb_setHandleCommLog(handleCommLog);

}

static bool askForCopy(const char* prompt)
{
    return (1 == askClient(true, "question", prompt));
}

static bool askForSignature(const char* prompt)
{
    return (1 == askClient(true, "question", prompt));
}

static bool showYesNoScreen(const char* prompt)
{
    return (1 == askClient(true, "question", prompt));
}

static void waitForCardRemoval(const char* prompt)
{
    notifyClient(prompt);
}

static void showPromptScreen(const char* prompt)
{
    notifyClient(prompt);
}

static bool waitForCard(const char* prompt)
{
    return (1 == askClient(true, "question", prompt));
}

static bool waitForPin(const char* prompt)
{
    return (1 == askClient(true, "question", prompt));
}

static void handleStatusChange(ecr_terminalStatus status)
{
    notifyAboutStatusChange(status);
}

static void showOkScreen(const char* prompt)
{
    notifyClient(prompt);
}

static void getCashbackAmount(const char* prompt, cb_UserProvidedData *amount)
{
    askClientForValue("question", prompt, amount, NULL);
}

static void getAuthorizationCode(const char* prompt, cb_UserProvidedData *code)
{
    askClientForValue("question", prompt, code, NULL);
}

static void getAmount(const char* prompt, cb_UserProvidedData *amount)
{
    askClientForValue("question", prompt, amount, NULL);
}

static void getUserData(const char* prompt, cb_UserProvidedData *amount, cb_isCharacterAllowed charAllowedCallback)
{
    askClientForValue("question", prompt, amount, charAllowedCallback);
}

static bool askForCurrency(const char** currencies, size_t currenciesSize, uint32_t* userChoice)
{
    const char * text = "Currency";
    return askClientForSelection(currencies, currenciesSize, userChoice, text);
}

static bool askForSelection(const char** choices, size_t choicesSize, uint32_t* userChoice, const char* text)
{
    return askClientForSelection(choices, choicesSize, userChoice, text);
}

static void handleBusLog(const char* log)
{
    displayLogOnMainThreadFromOutside(log,     BOILogDestinationAPI);
}

static void handleDevLog(const char* log)
{
    displayLogOnMainThreadFromOutside(log,     BOILogDestinationAPI);
}

static void handleCommLog(const char* log)
{
    displayLogOnMainThreadFromOutside(log,     BOILogDestinationAPI);
}
#endif
/* ]] API, C */
/* [[ UTILS  */
- (bool)getCharStr:(char *)dest destLen:(unsigned int)destLen src:(NSString *)src
{
    memset(dest, 0, destLen);
    const char * result = [src cStringUsingEncoding:_apiTextEncoding];
    if (NULL != result)
    {
        strncpy(dest, result, (destLen - 1));
        return true;
    }
    else
    {
        if ([self ifExistsESCallbackObj])
        {
            [[self eSCallbackObj] writeLog:@"Problem with text encoding. ABORT" destination:    BOILogDestinationStatus];
        }
    }
    return false;
}
/* ]] UTILS  */
@end

/*
        NSData * nsdata_result  = [source dataUsingEncoding:_apiTextEncoding allowLossyConversion:true];
        if (0 < nsdata_result->length)
        {
            if ((destinationLen - 1) < nsdata_result->length)
            {
                strncpy(destination, (const char *)(nsdata_result->bytes), (destinationLen - 1));
            }
            else
            {
                strncpy(destination, (const char *)(nsdata_result->bytes), (nsdata_result->length));
            }
        }
 */
// TO DO : ukrywanie klawiatury, usuniecie oczekiwania dla 'wprowadz karte', owijka dla funkcji sprawdzajacej znak
