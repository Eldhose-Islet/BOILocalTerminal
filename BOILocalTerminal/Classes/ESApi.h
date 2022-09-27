
#include <stdbool.h>
#if !(TARGET_IPHONE_SIMULATOR)
#include "ecrlib.h"
#include "callbacks.h"
#include "printouts.h"
#endif


#import "ESAsynchResp.h"
#import "ESCallbacks.h"



@interface ESApi : NSObject {
id<ESCallbacks> __weak escb;
}
@property NSStringEncoding apiTextEncoding;

- (ESApi *)init;
- (ESApi *)initWithCallbacks:(id<ESCallbacks>)callbacks;
- (bool)ApiInit:(NSString *)terminalIp;
- (void)ApiStop;
- (void)ApiSale:(NSString *)transactionAmount;
- (void)ApiReversal:(NSString *)transactionId amount:(NSString *)transactionAmount;
- (void)ApiPrintLastTrx;
- (void)ApiReconciliation;
- (void)ApiDumpStatusToLog;
- (NSString *)ApiGetStatusDescription:(int)status;
@end
