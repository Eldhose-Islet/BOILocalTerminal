/* Copyright (C) 2017 by eService
 *
 * All rights reserved.  No part of this software may be reproduced,
 * transmitted, transcribed, stored in a retrieval system, or translated
 * into any language or computer language, in any form or by any means,
 * electronic, mechanical, magnetic, optical, chemical, manual or otherwise,
 * without the prior written permission of eService.
 */
/*
 * callbacks.h
 *
 *  Created on: 9 sty 2017
 *      Author: przemyslaw.ogorzalek
 */

#ifndef CALLBACKS_H_
#define CALLBACKS_H_

#include "dll_macro.h"
#include "enumerations.h"
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#define MAX_STRING_LEN 256

#ifdef __cplusplus
extern "C" {
#endif

typedef struct
{
    char userData[MAX_STRING_LEN + 1]; // NULL terminated string
    size_t maxLen;                     // String should be no longer than this value
    size_t minLen;                     // String should be no shorter than this value
} cb_UserProvidedData;

/**
 * Show developer log to user.
 *
 * Callback takes NULL terminated string which will be displayed to user
 */
typedef void (*cb_HandleDevLog)(const char*);
DLL_PUBLIC void cb_setHandleDevLog(cb_HandleDevLog handleDevLog);

/**
 * Show communication log to user.
 *
 * Callback takes NULL terminated string which will be displayed to user
 */
typedef void (*cb_HandleCommLog)(const char*);
DLL_PUBLIC void cb_setHandleCommLog(cb_HandleCommLog handleCommLog);

/**
 * Show business log to user.
 *
 * Callback takes NULL terminated string which will be displayed to user
 */
typedef void (*cb_HandleBusLog)(const char*);
DLL_PUBLIC void cb_setHandleBusLog(cb_HandleBusLog handleBusLog);

/**
 * Handle terminal status change
 *
 * Callback takes new terminal status
 */
typedef void (*cb_HandleStatusChange)(ecr_terminalStatus terminalStatus);
DLL_PUBLIC void cb_setHandleStatusChange(cb_HandleStatusChange handleStatusChange);

/**
 * Confirm cardholder's signature on ECR device.
 *
 * Callback takes NULL terminated string which will be displayed to user.
 * Returns true if signature is valid, false in any other case.
 */
typedef bool (*cb_SignatureRequest)(const char*);
DLL_PUBLIC void cb_setSignatureRequest(cb_SignatureRequest signatureRequest);

/**
 * Ask on ECR device if copy of ticket should be printed.
 *
 * Callback takes NULL terminated string which will be displayed to user.
 * Returns true if printing copy was requested, false otherwise
 */
typedef bool (*cb_CopyRequest)(const char*);
DLL_PUBLIC void cb_setCopyRequest(cb_CopyRequest copyRequest);

/**
 * Select transaction currency on ECR.
 *
 * Callback takes an array of NULL terminated string, size of list and pointer to index of selected currency.
 * Returns true if choice was made, false otherwise
 */
typedef bool (*cb_CurrencyRequest)(const char**, size_t, uint32_t*);
DLL_PUBLIC void cb_setCurrencyRequest(cb_CurrencyRequest currencyRequest);

/**
 * Select from provided options on ECR.
 *
 * Callback takes an array of NULL terminated string, size of list, pointer to index of selected option
 * and NULL terminated string which will be displayed to user.
 * Returns true if choice was made, false otherwise
 */
typedef bool (*cb_SelectRequest)(const char**, size_t, uint32_t*, const char*);
DLL_PUBLIC void cb_setSelectRequest(cb_SelectRequest selectRequest);

/**
 * Check if terminal should be still waiting for card.
 *
 * Callback takes NULL terminated string which will be displayed to user.
 * Returns false if waiting for card was interrupted, for example by cancel or timeout,
 * true otherwise.
 */
typedef bool (*cb_WaitForCard)(const char*);
DLL_PUBLIC void cb_setWaitForCard(cb_WaitForCard waitForCard);

/**
 * Inform the user, that card should be removed.
 *
 * Callback takes NULL terminated string which will be displayed to user.
 */
typedef void (*cb_WaitForCardRemoval)(const char*);
DLL_PUBLIC void cb_setWaitForCardRemoval(cb_WaitForCardRemoval waitForCardRemoval);

/**
 * Check if terminal should be still waiting for PIN.
 *
 * Callback takes NULL terminated string which will be displayed to user.
 * Returns false if waiting for PIN was interrupted, for example by cancel or timeout,
 * true otherwise.
 */
typedef bool (*cb_WaitForPin)(const char*);
DLL_PUBLIC void cb_setWaitForPin(cb_WaitForPin waitForPin);

/**
 * Display prompt until user acknowledges it by pressing a key, for example OK.
 *
 * Callback takes NULL terminated string, which should be displayed to user.
 */
typedef void (*cb_ShowOkScreen)(const char*);
DLL_PUBLIC void cb_setShowOkScreen(cb_ShowOkScreen showOkScreen);

/**
 * Present YES/NO question to the user.
 *
 * Callback takes NULL terminated string which will be displayed to user.
 * Returns true if user confirmed, false otherwise
 */
typedef bool (*cb_ShowYesNoScreen)(const char*);
DLL_PUBLIC void cb_setShowYesNoScreen(cb_ShowYesNoScreen showYesNoScreen);

/**
 * Show non-blocking screen to user.
 *
 * Callback takes NULL terminated string which will be displayed to user
 */
typedef void (*cb_ShowPromptScreen)(const char*);
DLL_PUBLIC void cb_setShowPromptScreen(cb_ShowPromptScreen showPromptScreen);

/**
 * Ask for cashback amount during transaction.
 *
 * Callback takes NULL terminated string which will be displayed to user.
 * Cashback amount should be provided in minor units, formatted as 12 ASCII characters, for example
 * "000000000599" for 5.99 PLN. Cashback amount should be written to userData field of cb_UserProvidedData structure.
 */
typedef void (*cb_GetCashbackAmount)(const char*, cb_UserProvidedData*);
DLL_PUBLIC void cb_setGetCashbackAmount(cb_GetCashbackAmount getCashbackAmount);

/**
 * Get authorization code for current transaction.
 *
 * Callback takes NULL terminated string which will be displayed to user.
 * Authorization code should be 4 to 6 alphanumerical characters, for example "123ABC".
 * Code should be written to userData field of cb_UserProvidedData structure.
 */
typedef void (*cb_GetAuthorizationCode)(const char*, cb_UserProvidedData*);
DLL_PUBLIC void cb_setGetAuthorizationCode(cb_GetAuthorizationCode getAuthorizationCode);

/**
 * Get data entry from user.
 *
 * Callback cb_isCharacterAllowed is provided by library and set in cb_setGetUserData function.
 * It should be used in cb_getUserData callback to validate input data. It takes single character and
 * returns true if it is valid input. It is never set to NULL.
 *
 * Callback cb_getUserData takes NULL terminated string with prompt, which will be displayed to user,
 * output argument with placeholder for acquired data, and callback for data validation.
 * Acquired data should be written to userData field of cb_UserProvidedData structure.
 */
typedef bool (*cb_isCharacterAllowed)(char character);
typedef void (*cb_getUserData)(const char*, cb_UserProvidedData*, cb_isCharacterAllowed);
DLL_PUBLIC void cb_setGetUserData(cb_getUserData getUserData);

/**
 * Get amount from user.
 *
 * Callback cb_getUserData takes NULL terminated string with prompt, which will be displayed to user
 * and output argument with placeholder for acquired data
 * Acquired data should be written to userData field of cb_UserProvidedData structure.
 */
typedef void (*cb_getAmount)(const char*, cb_UserProvidedData*);
DLL_PUBLIC void cb_setGetAmount(cb_getAmount getAmount);

#ifdef __cplusplus
}
#endif

#endif /* SRC_LIB_API_CALLBACKS_H_ */
