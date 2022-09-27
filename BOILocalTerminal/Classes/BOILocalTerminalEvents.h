//
//  BOILocalTerminalEvents.h
//  Totelier
//
//  Created by Islet on 25/08/22.
//  Copyright © 2022 Phenomtec. All rights reserved.
//

#ifndef BOILocalTerminalEventProtocal_h
#define BOILocalTerminalEventProtocal_h
#import "ESAsynchResp.h"
#import "TOTBOItransactionResult.h"
#import "BOIEnums.h"

@protocol BOILocalTerminalEvents <NSObject>
- (void) logUpdated:(NSArray  *  _Nullable)taskArgs;
- (void) terminalConnectionTypeChangedTo:(TOTBOIConnectionType)stat;
- (void) askClientForValueInMainThread:(ESAsynchResp * _Nullable)answ;
- (void) terminalTransactionStatusChangedTo:(BOITransactionStatus)stat description:(NSString * _Nullable)desc;
- (void) gotTransctionResult:(TOTBOItransactionResult * _Nullable)result;
@end


#endif /* BOILocalTerminalEventProtocal_h */
