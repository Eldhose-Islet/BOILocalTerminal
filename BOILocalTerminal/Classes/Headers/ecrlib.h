/* Copyright (C) 2017 by eService
 *
 * All rights reserved.  No part of this software may be reproduced,
 * transmitted, transcribed, stored in a retrieval system, or translated
 * into any language or computer language, in any form or by any means,
 * electronic, mechanical, magnetic, optical, chemical, manual or otherwise,
 * without the prior written permission of eService.
 */
/*
 * ecrlib.h
 *
 *  Created on: 4 sty 2017
 *      Author: przemyslaw.ogorzalek
 */

#ifndef ECRLIB_H_
#define ECRLIB_H_

#include "tags.h"

#include "dll_macro.h"
#include "enumerations.h"
#include "tlv.h"

#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/**********************************************************************************************************
 *******************                           Data types                               *******************
 **********************************************************************************************************/



// Definition of the structure is not provided, as it should not be modified by higher abstraction layers.
// Object will be dynamically created in ecr_initialize and deleted in ecr_cleanup
struct EcrCtx_s;
typedef struct EcrCtx_s EcrCtx;

/**********************************************************************************************************
 *******************                         Library setup                              *******************
 **********************************************************************************************************/

/**
    Get version of the ecr library.

    return Library version in format [MAJOR VERSION].[MINOR VERSION]
*/
DLL_PUBLIC const char* ecr_getVersion();

/**
    Prepare the library before the first use, create ecrCtx.

    param[in,out]  ecrCtx  Address of pointer to EcrCtx. Client application controls pointer's lifetime, but
                            instance of EcrCtx is created dynamically and must be safely deleted by ecr_cleanup
    return ECR_OK if initialization was performed successfully, error status otherwise
*/
DLL_PUBLIC ecr_status ecr_initialize(EcrCtx** ecrCtx);

/**
 * Release all resources and delete ecrCtx.
 *
 * param[in,out] ecrCtx  Address of pointer to EcrCtx, will be set to NULL at the end
 */
DLL_PUBLIC void ecr_cleanup(EcrCtx** ecrCtx);

/**
 * Set protocol for terminal communication.
 *
 * param[in,out] ecrCtx    Pointer to EcrCtx
 * param[in]     protocol  ID of protocol used in ECR-terminal communication,
 *                 list of available options present in enumerations.h file
 */
DLL_PUBLIC void ecr_setProtocol(EcrCtx* ecrCtx, ecr_communicationProtocol protocol);

/**
 * Connect to remote host by TCP/IP protocol.
 *
 * param[in,out] ecrCtx  Pointer to EcrCtx, where connection setting will be stored
 * param[in]     ip      Remote host IP address in format NNN.NNN.NNN.NNN
 * param[in]     port    TCP port awaiting for connection on host's side
 * param[in]     timeout Connection timeout in milliseconds
 * return  ECR_OK if connection successful
 */
DLL_PUBLIC ecr_status ecr_setTcpIpLink(EcrCtx* ecrCtx, const char* ip, uint16_t port, uint32_t timeout);

/**
 * Connect to host by serial port.
 *
 * param[in,out] ecrCtx  Pointer to EcrCtx, where connection setting will be stored
 * param[in]     port    Local serial port identifier
 * param[in]     mode    Word format for serial communication, available options listed in enumerations.h
 * param[in]     baud    Baudrate for serial communication, available options listed in enumerations.h
 * param[in]     timeout Communication timeout in milliseconds
 * return  ECR_OK if connection successful
 */
DLL_PUBLIC ecr_status ecr_setSerialLink(EcrCtx* ecrCtx, const char* port, comm_SerialDataMode mode,
        comm_SerialBaudrate baud, uint32_t timeout);

/**
 * Disconnect from host.
 *
 * param[in,out] ecrCtx  Pointer to EcrCtx
 * return  ECR_OK if disconnection successful
 */
DLL_PUBLIC ecr_status ecr_closeConnection(EcrCtx* ecrCtx);

/**
 * Set Cash Register ID.
 *
 * note Unless this function is used, default value 0 will be used
 * note For eService protocol single-character ID is expected
 *
 * param[in,out] ecrCtx  Pointer to EcrCtx, where id will be stored
 * param[in]     id      Buffer where cash register ID is stored
 * param[in]     idLen   Buffer length
 * return  ECR_OK if ID stored successfully
 */
DLL_PUBLIC ecr_status ecr_setCashRegisterId(EcrCtx* ecrCtx, uint8_t* id, size_t idLen);

/**********************************************************************************************************
 *******************                         Setting input data                         *******************
 **********************************************************************************************************/
// More setters can be provided if requested

// Transaction functions

/**
 * Set transaction type (tag TAG_TRANSACTION_TYPE).
 *
 * param[in,out] ecrCtx  Pointer to EcrCtx, where data will be stored
 * param[in]     type    Transaction type. Available transaction types listed in enumerations.h
 * return ECR_OK if stored successfully
 */
DLL_PUBLIC ecr_status ecr_setTransactionType(EcrCtx* ecrCtx, ecr_transactionType type);

/**
 * Set transaction amount (tag TAG_AMOUNT).
 *
 * param[in,out] ecrCtx  Pointer to EcrCtx, where data will be stored
 * param[in]     amount    Transaction amount, no more than 12 digits
 * return ECR_OK if stored successfully
 */
DLL_PUBLIC ecr_status ecr_setTransactionAmount(EcrCtx* ecrCtx, const char* amount);

/**
 * Set transaction title (tag TAG_TRANSACTON_TITLE).
 *
 * param[in,out] ecrCtx  Pointer to EcrCtx, where data will be stored
 * param[in]     title    Transaction title
 * return ECR_OK if stored successfully
 */
DLL_PUBLIC ecr_status ecr_setTransactionTitle(EcrCtx* ecrCtx, const char* title);

/**
 * Set BLIK code to use it in purchase transaction.
 *
 * param[in,out] ecrCtx  Pointer to EcrCtx, where data will be stored
 * param[in]     blikCode    BLIK code
 * return ECR_OK if stored successfully
 */
DLL_PUBLIC ecr_status ecr_setTransactionBlikCode(EcrCtx* ecrCtx, const char* blikCode);

/**
 * Set Additional Printout Data.
 *
 * param[in,out] ecrCtx  Pointer to EcrCtx, where data will be stored
 * param[in]     additionalPrintoutData    Additional Printout Data
 * return ECR_OK if stored successfully
 */
DLL_PUBLIC ecr_status ecr_setAdditionalPrintoutData(EcrCtx* ecrCtx, const char* additionalPrintoutData);

/**
 * Set Transaction Variable Symbol
 *
 * param[in,out] ecrCtx  Pointer to EcrCtx, where data will be stored
 * param[in]     variableSymbol    Transaction Variable Symbol
 * return ECR_OK if stored successfully
 */
DLL_PUBLIC ecr_status ecr_setTransactionVariableSymbol(EcrCtx* ecrCtx, const char* variableSymbol);

/**
 * Set Transaction Specific Symbol
 *
 * param[in,out] ecrCtx  Pointer to EcrCtx, where data will be stored
 * param[in]     specificSymbol    Transaction Specific Symbol
 * return ECR_OK if stored successfully
 */
DLL_PUBLIC ecr_status ecr_setTransactionSpecificSymbol(EcrCtx* ecrCtx, const char* specificSymbol);

/**
 * Set Transaction Currency
 *
 * param[in,out] ecrCtx  Pointer to EcrCtx, where data will be stored
 * param[in]     currency    Transaction Currency
 * return ECR_OK if stored successfully
 */
DLL_PUBLIC ecr_status ecr_setTransactionCurrency(EcrCtx* ecrCtx, const char* currency);

/**
 * Set Cashier Language
 *
 * param[in,out] ecrCtx  Pointer to EcrCtx, where data will be stored
 * param[in]     language    ISO 639-1 language
 * return ECR_OK if stored successfully
 */
DLL_PUBLIC ecr_status ecr_setCashierLanguage(EcrCtx* ecrCtx, const char* language);

/**
 * Set Cardholder Language
 *
 * param[in,out] ecrCtx  Pointer to EcrCtx, where data will be stored
 * param[in]     language    ISO 639-1 language
 * return ECR_OK if stored successfully
 */
DLL_PUBLIC ecr_status ecr_setCardholderLanguage(EcrCtx* ecrCtx, const char* language);

/**
 * Set send supported languages enabled
 *
 * param[in,out] ecrCtx  Pointer to EcrCtx, where data will be stored
 * return ECR_OK if stored successfully
 */
DLL_PUBLIC ecr_status ecr_setSendSupportedLanguagesEnabled(EcrCtx* ecrCtx);

/**
 * Set Fleet card product data.
 *
 * param[in,out] ecrCtx    Pointer to EcrCtx, where data will be stored
 * param[in]     data      TLV buffer consisting all fleet card data
 * param[in]     dataSize  Size of provided data buffer
 * return ECR_OK if stored successfully
 */
DLL_PUBLIC ecr_status ecr_addFleetCardProductData(EcrCtx* ecrCtx, const uint8_t *data, size_t dataSize);

/**
 * Set MultiSplit Payment data.
 *
 * param[in,out] ecrCtx    Pointer to EcrCtx, where data will be stored
 * param[in]     data      TLV buffer consisting all MultiSplit Payment data
 * param[in]     dataSize  Size of provided data buffer
 * return ECR_OK if stored successfully
 */

DLL_PUBLIC ecr_status ecr_addMSPData(EcrCtx* ecrCtx, const uint8_t *data, size_t dataSize);

/**
 * Enable Token Generation
 *
 * param[in,out] ecrCtx  Pointer to EcrCtx, where data will be stored
 * return ECR_OK if stored successfully
 */
DLL_PUBLIC ecr_status ecr_setTransactionTokenGenerationEnabled(EcrCtx* ecrCtx);

/**
 * Set transaction number for completion (tag TAG_TRANSACTION_TO_COMPLETE).
 *
 * param[in,out] ecrCtx  Pointer to EcrCtx, where data will be stored
 * param[in]     number  Sequence number of preauthorization to be completed
 * return ECR_OK if stored successfully
 */
DLL_PUBLIC ecr_status ecr_setNumberOfTransactionToComplete(EcrCtx* ecrCtx, const char* number);

/**
 * Set transaction number for reversal (tag TAG_TRANSACTION_TO_REVERSE).
 *
 * param[in,out] ecrCtx  Pointer to EcrCtx, where data will be stored
 * param[in]     number  Sequence number of reversed transaction
 * return ECR_OK if stored successfully
 */
DLL_PUBLIC ecr_status ecr_setNumberOfTransactionToReverse(EcrCtx* ecrCtx, const char* number);

/**
 * Set tag's value in ECR context
 *
 * param[in,out] ecrCtx  Pointer to EcrCtx, where data will be stored
 * param[in]     tag     Tag which will be set, must conform to rules set in EMV BOOK 3
 * param[in]     value   Buffer which will be assigned to tag
 * param[in]     len     Simple buffer's len, will be converted to format requested by EMV BOOK 3 internally
 * return ECR_OK if stored successfully
 */
DLL_PUBLIC ecr_status ecr_setTag(EcrCtx* ecrCtx, TlvTag tag, const uint8_t* value, size_t len);

/**
 * Remove tag's value from ECR context
 *
 * param[in,out] ecrCtx  Pointer to EcrCtx, where data will be stored
 * param[in]     tag     Tag which will be cleared
 * return ECR_OK cleared successfully
 */
DLL_PUBLIC ecr_status ecr_setTagToEmpty(EcrCtx* ecrCtx, TlvTag tag);

// Reports functions

/**
 * Set ID of transaction to be retrieved from terminal (tag TAG_TRANSACTION_ID)
 *
 * param[in,out] ecrCtx             Pointer to EcrCtx, where data will be stored
 * param[in]     transactionId      Transaction ID
 * return ECR_OK if stored successfully
 */
DLL_PUBLIC ecr_status ecr_setTransactionId(EcrCtx* ecrCtx, uint32_t transactionId);

/**
 * Set ID of cardset to be retrieved from terminal (tag TAG_CARDSET_ID)
 *
 * param[in,out] ecrCtx         Pointer to EcrCtx, where data will be stored
 * param[in]     cardsetId      Cardset ID
 * return ECR_OK if stored successfully
 */
DLL_PUBLIC ecr_status ecr_setCardsetId(EcrCtx* ecrCtx, uint32_t cardsetId);

/**
 * Set currency ID (tag TAG_CURRENCY_ID)
 *
 * param[in,out] ecrCtx         Pointer to EcrCtx, where data will be stored
 * param[in]     currencyId      Currency ID
 * return ECR_OK if stored successfully
 */
DLL_PUBLIC ecr_status ecr_setCurrencyId(EcrCtx* ecrCtx, uint32_t currencyId);

/**
 * Set indicator for report reset (tag TAG_RESET_REPORT)
 *
 * param[in,out] ecrCtx         Pointer to EcrCtx, where data will be stored
 * param[in]     resetReport    Resetting report indicator
 * return ECR_OK if stored successfully
 */
DLL_PUBLIC ecr_status ecr_setResetReport(EcrCtx* ecrCtx, bool resetReport);

// Maintenance functions

/**
 * Setting terminal index (tag TAG_TERMINAL_INDEX)
 *
 * param[in,out] ecrCtx         Pointer to EcrCtx, where data will be stored
 * param[in]     terminalIndex  Index of terminal
 * return ECR_OK if stored successfully
 */
DLL_PUBLIC ecr_status ecr_setTerminalIndex(EcrCtx* ecrCtx, uint8_t terminalIndex);

/**
 * Setting indicator, whether user interaction should take place on ECR or terminal (tag TAG_HANDLE_REQUESTS)
 *
 * param[in,out] ecrCtx         Pointer to EcrCtx, where data will be stored
 * param[in]     handleRequests Chosen handling terminal requests mode
 * return ECR_OK if stored successfully
 */
DLL_PUBLIC ecr_status ecr_setHandleTerminalRequests(
    EcrCtx* ecrCtx, ecr_HandlingTerminalRequestsMode handleRequests);

/**
 * Set transaction number for completion (tag TAG_RELATED_AUTHORIZATION_CODE).
 *
 * param[in,out] ecrCtx  Pointer to EcrCtx, where data will be stored
 * param[in]     authCode  Authorization code of related transaction
 * return ECR_OK if stored successfully
 */
DLL_PUBLIC ecr_status ecr_setRelatedAuthorizationCode(EcrCtx* ecrCtx, const char* authCode);

/**********************************************************************************************************
 *******************                       Retrieving output data                       *******************
 **********************************************************************************************************/

/**
 * Read last command's return code.
 *
 * param[in,out] ecrCtx         Pointer to EcrCtx, from which data will be retrieved
 * param[out]    lastReturnCode Storage for last return code
 */
DLL_PUBLIC void ecr_getLastReturnCode(EcrCtx* ecrCtx, uint32_t* lastReturnCode);

// Transaction functions

/**
 * Read result of performed transaction (tag TAG_TRANSACTION_RETURN_CODE)
 *
 * param[in,out] ecrCtx     Pointer to EcrCtx, from which data will be retrieved
 * param[out]    result     Storage for transaction result, values are listed in enumerations.h
 * return ECR_OK if retrieved successfully
 */
DLL_PUBLIC ecr_status ecr_readTransactionResult(EcrCtx* ecrCtx, ecr_transactionResult* result);

/**
 * Read transaction type (tag TAG_TRANSACTION_TYPE)
 *
 * param[in,out] ecrCtx     Pointer to EcrCtx, from which data will be retrieved
 * param[out]    type       Storage for transaction type, values are listed in enumerations.h
 * return ECR_OK if retrieved successfully
 */
DLL_PUBLIC ecr_status ecr_readTransactionType(EcrCtx* ecrCtx, ecr_transactionType* type);

/**
 * Read original transaction type in case of reversal (tag TAG_ORIGINAL_TRANSACTION_TYPE)
 *
 * param[in,out] ecrCtx     Pointer to EcrCtx, from which data will be retrieved
 * param[out]    type       Storage for transaction type, values are listed in enumerations.h
 * return ECR_OK if retrieved successfully
 */
DLL_PUBLIC ecr_status ecr_readOriginalTransactionType(EcrCtx* ecrCtx, ecr_transactionType* type);

/**
 * Read information how the card was inserted (tag TAG_USED_READER)
 *
 * param[in,out] ecrCtx     Pointer to EcrCtx, from which data will be retrieved
 * param[out]    type       Storage for reader type, values are listed in enumerations.h
 * return ECR_OK if retrieved successfully
 */
DLL_PUBLIC ecr_status ecr_readUsedCardReaderType(EcrCtx* ecrCtx, CardReaderType* type);

/**
 * Read information how the transaction was authorized - offline, online, by phone (tag TAG_AUTHORIZATION_TYPE)
 *
 * param[in,out] ecrCtx     Pointer to EcrCtx, from which data will be retrieved
 * param[out]    type       Storage for authorization type, values are listed in enumerations.h
 * return ECR_OK if retrieved successfully
 */
DLL_PUBLIC ecr_status ecr_readAuthorizationType(EcrCtx* ecrCtx, AuthorizationType* type);

/**
 * Read information how the transaction was authorized by customer - pin, signature, no CVM
 * (tag TAG_AUTHORIZATION_METHOD)
 *
 * param[in,out] ecrCtx     Pointer to EcrCtx, from which data will be retrieved
 * param[out]    method     Storage for authorization method, values are listed in enumerations.h
 * return ECR_OK if retrieved successfully
 */
DLL_PUBLIC ecr_status ecr_readAuthorizationMethod(EcrCtx* ecrCtx, AuthorizationMethod* method);

/**
 * Read information about type of transaction cryptogram - TC, ARQC, AAC (tag TAG_EMV_CRYPTOGRAM_TYPE)
 *
 * param[in,out] ecrCtx     Pointer to EcrCtx, from which data will be retrieved
 * param[out]    type       Storage for cryptogram type, values are listed in enumerations.h
 * return ECR_OK if retrieved successfully
 */
DLL_PUBLIC ecr_status ecr_readEmvCryptogramType(EcrCtx* ecrCtx, EmvCryptogramType* type);

/**
 * Read information whether printout was handled by terminal or should be performed by ECR
 * (tag TAG_PRINTING_INDICATOR)
 *
 * param[in,out] ecrCtx       Pointer to EcrCtx, from which data will be retrieved
 * param[out]    information  Storage for printout information, true if terminal printed the receipt,
 *                             false if ECR do it
 * return ECR_OK if retrieved successfully
 */
DLL_PUBLIC ecr_status ecr_readIfTerminalMadePrinout(EcrCtx* ecrCtx, bool* information);

/**
 * Read information whether printout should be in non-standard language as well
 * (part of tag TAG_ADDITIONAL_TRANSACTION_FLAG)
 *
 * param[in,out] ecrCtx       Pointer to EcrCtx, from which data will be retrieved
 * param[out]    information  Storage for printout information, true if printout should be multilanguage,
 *                             false otherwise
 * return ECR_OK if retrieved successfully
 */
DLL_PUBLIC ecr_status ecr_readIfMultilanguagePrintoutIsRequired(EcrCtx* ecrCtx, bool* information);

/**
 * Read information whether reversal was manual
 * (part of tag TAG_ADDITIONAL_TRANSACTION_FLAG)
 *
 * param[in,out] ecrCtx       Pointer to EcrCtx, from which data will be retrieved
 * param[out]    information  Storage for printout information, true if transaction was a manual reversal,
 *                             false otherwise
 * return ECR_OK if retrieved successfully
 */
DLL_PUBLIC ecr_status ecr_readIfReversalWasManual(EcrCtx* ecrCtx, bool* information);

/**
 * Read information whether transaction was a reversal (tag TAG_REVERSAL_INDICATOR)
 *
 * param[in,out] ecrCtx       Pointer to EcrCtx, from which data will be retrieved
 * param[out]    information  Storage for reversal information, true if transaction was indeed a reversal,
 *                             false otherwise
 * return ECR_OK if retrieved successfully
 */
DLL_PUBLIC ecr_status ecr_readIfTransactionWasReversal(EcrCtx* ecrCtx, bool* information);

/**
 * Read transaction number (ascii encoding) (tag TAG_TRANSACTION_NUMBER)
 *
 * param[in,out] ecrCtx     Pointer to EcrCtx, from which data will be retrieved
 * param[out]    number     Storage for transaction number, which can be up to 4 bytes bytes long,
 *                           so due to HEX encoding (+ NULL character),
 *                           provided buffer must be no shorter than 9 characters
 * return ECR_OK if retrieved successfully
 */
DLL_PUBLIC ecr_status ecr_readTransactionNumber(EcrCtx* ecrCtx, char* amount);

/**
 * Read transaction date in ISO format (ascii encoding) (tag TAG_TRANSACTION_DATE)
 *
 * param[in,out] ecrCtx     Pointer to EcrCtx, from which data will be retrieved
 * param[out]    isoDate    Storage for transaction date, expected format is YYYY-MM-DD (+ NULL character),
 *                           so provided buffer must be no shorter than 11 characters
 * return ECR_OK if retrieved successfully
 */
DLL_PUBLIC ecr_status ecr_readTransactionDate(EcrCtx* ecrCtx, char* isoDate);

/**
 * Read transaction time (ascii encoding) (tag TAG_TRANSACTION_TIME)
 *
 * param[in,out] ecrCtx     Pointer to EcrCtx, from which data will be retrieved
 * param[out]    time       Storage for transaction time, expected format is HH:MM:SS (+ NULL character),
 *                           so provided buffer must be no shorter than 9 characters
 * return ECR_OK if retrieved successfully
 */
DLL_PUBLIC ecr_status ecr_readTransactionTime(EcrCtx* ecrCtx, char* time);

/**
 * Read application cryptogram (ascii encoding) (tag TAG_AC)
 *
 * param[in,out] ecrCtx      Pointer to EcrCtx, from which data will be retrieved
 * param[out]    cryptogram  Storage for transaction cryptogram, which is 8 bytes long,
 *                            so due to HEX encoding (+ NULL character),
 *                            provided buffer must be no shorter than 17 characters
 * return ECR_OK if retrieved successfully
 */
DLL_PUBLIC ecr_status ecr_readTransactionCryptogram(EcrCtx* ecrCtx, char* cryptogram);

/**
 * Read transaction counter (ascii encoding) (tag TAG_ATC)
 *
 * param[in,out] ecrCtx                 Pointer to EcrCtx, from which data will be retrieved
 * param[out]    transactionCounter     Storage for transaction counter, which is 2 bytes long,
 *                                       so due to HEX encoding (+ NULL character),
 *                                       provided buffer must be no shorter than 5 characters
 * return ECR_OK if retrieved successfully
 */
DLL_PUBLIC ecr_status ecr_readTransactionCounter(EcrCtx* ecrCtx, char* transactionCounter);

/**
 * Read Terminal Verification Result (ascii encoding) (tag TAG_TVR)
 *
 * param[in,out] ecrCtx     Pointer to EcrCtx, from which data will be retrieved
 * param[out]    tvr        Storage for TVR, which is 5 bytes long,
 *                           so due to HEX encoding (+ NULL character),
 *                           provided buffer must be no shorter than 11 characters
 * return ECR_OK if retrieved successfully
 */
DLL_PUBLIC ecr_status ecr_readTransactionTvr(EcrCtx* ecrCtx, char* tvr);

/**
 * Read Transaction Status Information (ascii encoding) (tag TAG_TSI)
 *
 * param[in,out] ecrCtx     Pointer to EcrCtx, from which data will be retrieved
 * param[out]    tsi        Storage for TSI, which is 2 bytes long,
 *                           so due to HEX encoding (+ NULL character),
 *                           provided buffer must be no shorter than 5 characters
 * return ECR_OK if retrieved successfully
 */
DLL_PUBLIC ecr_status ecr_readTransactionTsi(EcrCtx* ecrCtx, char* tsi);

/**
 * Read Application Identifier (ascii encoding) (tag TAG_AID)
 *
 * param[in,out] ecrCtx     Pointer to EcrCtx, from which data will be retrieved
 * param[out]    aid        Storage for AID, which can be up to 16 bytes bytes long,
 *                           so due to HEX encoding (+ NULL character),
 *                           provided buffer must be no shorter than 33 characters
 * return ECR_OK if retrieved successfully
 */
DLL_PUBLIC ecr_status ecr_readTransactionAid(EcrCtx* ecrCtx, char* aid);

/**
 * Read transaction Currency Code (tag TAG_TRANSACTION_CURRENCY)
 *
 * param[in,out] ecrCtx     Pointer to EcrCtx, from which data will be retrieved
 * param[out]    code       Storage for currency code
 * return ECR_OK if retrieved successfully
 */
DLL_PUBLIC ecr_status ecr_readTransactionCurrencyCode(EcrCtx* ecrCtx, uint16_t* code);

/**
 * Read terminal Currency Code (tag TAG_TERMINAL_CURRENCY)
 *
 * param[in,out] ecrCtx     Pointer to EcrCtx, from which data will be retrieved
 * param[out]    code       Storage for currency code
 * return ECR_OK if retrieved successfully
 */
DLL_PUBLIC ecr_status ecr_readTerminalCurrencyCode(EcrCtx* ecrCtx, uint16_t* code);

/**
 * Read label for transaction currency, for example PLN if currency code is 0985
 *
 * param[in,out] ecrCtx     Pointer to EcrCtx, from which data will be retrieved
 * param[out]    label      Storage for currency label, since label has 3 characters
 *                           and is NULL-terminated, provided buffer must be no shorter
 *                           than 4 bytes
 * return ECR_OK if retrieved successfully
 */
DLL_PUBLIC ecr_status ecr_readTransactionCurrencyLabel(EcrCtx* ecrCtx, char* label);

/**
 * Read label for terminal currency, for example PLN if currency code is 0985
 *
 * param[in,out] ecrCtx     Pointer to EcrCtx, from which data will be retrieved
 * param[out]    label      Storage for currency label, since label has 3 characters
 *                           and is NULL-terminated, provided buffer must be no shorter
 *                           than 4 bytes
 * return ECR_OK if retrieved successfully
 */
DLL_PUBLIC ecr_status ecr_readTerminalCurrencyLabel(EcrCtx* ecrCtx, char* label);

/**
 * Read currency exponent (tag TAG_CURRENCY_EXPONENT)
 *
 * param[in,out] ecrCtx     Pointer to EcrCtx, from which data will be retrieved
 * param[out]    exponent   Storage for currency exponent, single character (not NULL terminated)
 * return ECR_OK if retrieved successfully
 */
DLL_PUBLIC ecr_status ecr_readCurrencyExponent(EcrCtx* ecrCtx, char* exponent);

/**
 * Read Transaction Amount (ascii encoding) (tag TAG_AMOUNT)
 *
 * param[in,out] ecrCtx     Pointer to EcrCtx, from which data will be retrieved
 * param[out]    amount     Storage for transaction amount, which can be up to 6 bytes bytes long,
 *                           so due to HEX encoding (+ NULL character),
 *                           provided buffer must be no shorter than 13 characters
 * return ECR_OK if retrieved successfully
 */
DLL_PUBLIC ecr_status ecr_readTransactionAmount(EcrCtx* ecrCtx, char* amount);

/**
 * Read Transaction Amount in terminal currency in case of DCC transaction (ascii encoding)
 * (tag TAG_AMOUNT_IN_TERMINAL_CURRENCY)
 *
 * param[in,out] ecrCtx     Pointer to EcrCtx, from which data will be retrieved
 * param[out]    amount     Storage for transaction amount, which can be up to 6 bytes bytes long,
 *                           so due to HEX encoding (+ NULL character),
 *                           provided buffer must be no shorter than 13 characters
 * return ECR_OK if retrieved successfully
 */
DLL_PUBLIC ecr_status ecr_readTransactionAmountInTerminalCurrency(EcrCtx* ecrCtx, char* amount);

/**
 * Read Cashback Amount (ascii encoding) (tag TAG_CASHBACK_AMOUNT)
 *
 * param[in,out] ecrCtx     Pointer to EcrCtx, from which data will be retrieved
 * param[out]    amount     Storage for cashback amount, which can be up to 6 bytes bytes long,
 *                           so due to HEX encoding (+ NULL character),
 *                           provided buffer must be no shorter than 13 characters
 * return ECR_OK if retrieved successfully
 */
DLL_PUBLIC ecr_status ecr_readTransactionCashback(EcrCtx* ecrCtx, char* cashback);

/**
 * Read Amount of tip (ascii encoding) (tag TAG_AMOUNT_OF_TIP)
 *
 * param[in,out] ecrCtx     Pointer to EcrCtx, from which data will be retrieved
 * param[out]    amount     Storage for amount of tip, which can be up to 6 bytes long,
 *                           so due to HEX encoding (+ NULL character),
 *                           provided buffer must be no shorter than 13 characters
 * return ECR_OK if retrieved successfully
 */
DLL_PUBLIC ecr_status ecr_readTransactionAmountOfTip(EcrCtx* ecrCtx, char* amount);

/**
 * Read additional printout data (ascii encoding) (tag TAG_ADDITIONAL_PRINTOUT_DATA_FROM_ECR)
 *
 * param[in,out] ecrCtx     Pointer to EcrCtx, from which data will be retrieved
 * param[out]    data       Storage for additional printout data
 * return ECR_OK if retrieved successfully
 */
DLL_PUBLIC ecr_status ecr_readAdditionalPrintoutData(EcrCtx* ecrCtx, char* data);

/**
 * Read transaction cardset name (CP1250 encoding) (tag TAG_CARDSET_NAME)
 *
 * param[in,out] ecrCtx        Pointer to EcrCtx, from which data will be retrieved
 * param[out]    cardsetName       Buffer for cardset name
 * param[in,out] cardsetNameSize   Buffer size
 *
 * return ECR_OK if retrieved successfully
 */
DLL_PUBLIC ecr_status ecr_readTransactionMultiMCCData(EcrCtx* ecrCtx, char* multiMCCData, size_t multiMCCDataSize);

/**
 * Read transaction multiMCC data (CP1250 encoding) (tag TAG_MULTIMCC_DATA)
 *
 * param[in,out] ecrCtx        Pointer to EcrCtx, from which data will be retrieved
 * param[out]    multiMCCData       Buffer for multiMCC data
 * param[in,out] multiMCCDataSize   Buffer size
 *
 * return ECR_OK if retrieved successfully
 */
DLL_PUBLIC ecr_status ecr_readTransactionCardsetName(EcrCtx* ecrCtx, char* cardsetName, size_t cardsetNameSize);

/**
 * Read transaction variable symbol (ascii encoding) (tag TAG_VARIABLE_SYMBOL)
 *
 * param[in,out] ecrCtx     Pointer to EcrCtx, from which data will be retrieved
 * param[out]    variableSymbol      Buffer for variable symbol
 * param[in,out] variableSymbolSize  Buffer size
 * return ECR_OK if retrieved successfully
 */
DLL_PUBLIC ecr_status ecr_readTransactionVariableSymbol(EcrCtx* ecrCtx, char* variableSymbol, size_t variableSymbolSize);

/**
 * Read transaction specific symbol (ascii encoding) (tag TAG_SPECIFIC_SYMBOL)
 *
 * param[in,out] ecrCtx     Pointer to EcrCtx, from which data will be retrieved
 * param[out]    specificSymbol      Buffer for specific symbol
 * param[in,out] specificSymbolSize  Buffer size
 * return ECR_OK if retrieved successfully
 */
DLL_PUBLIC ecr_status ecr_readTransactionSpecificSymbol(EcrCtx* ecrCtx, char* specificSymbol, size_t specificSymbolSize);

/**
 * Read merchant copy language (ascii encoding) (tag TAG_MERCHANT_COPY_LANGUAGE)
 *
 * param[in,out] ecrCtx     Pointer to EcrCtx, from which data will be retrieved
 * param[out]    language      Buffer for ISO 639-1 language
 * param[in,out] languageSize  Buffer size
 * return ECR_OK if retrieved successfully
 */
DLL_PUBLIC ecr_status ecr_readMerchantCopyLanguage(EcrCtx* ecrCtx, char* language, size_t languageSize);

/**
 * Read client copy language (ascii encoding) (tag TAG_CLIENT_COPY_LANGUAGE)
 *
 * param[in,out] ecrCtx     Pointer to EcrCtx, from which data will be retrieved
 * param[out]    language      Buffer for ISO 639-1 language
 * param[in,out] languageSize  Buffer size
 * return ECR_OK if retrieved successfully
 */
DLL_PUBLIC ecr_status ecr_readClientCopyLanguage(EcrCtx* ecrCtx, char* language, size_t languageSize);

/**
 * Read transaction markup (ascii encoding) (tag TAG_MARKUP)
 *
 * param[in,out] ecrCtx      Pointer to EcrCtx, from which data will be retrieved
 * param[out]    markup      Buffer for markup
 * param[in,out] markupSize  Buffer size
 * return ECR_OK if retrieved successfully
 */
DLL_PUBLIC ecr_status ecr_readTransactionMarkup(EcrCtx* ecrCtx, char* markup, size_t markupSize);

/**
 * Read transaction markup text (ascii encoding) (tag TAG_MARKUP_TEXT)
 *
 * param[in,out] ecrCtx     Pointer to EcrCtx, from which data will be retrieved
 * param[out]    markupText       Storage for markup text
 * param[in,out] markupTextSize  Buffer size
 * return ECR_OK if retrieved successfully
 */
DLL_PUBLIC ecr_status ecr_readTransactionMarkupText(EcrCtx* ecrCtx, char* markupText, size_t markupTextSize);

/**
 * Read transaction markup info (ascii encoding) (tag TAG_MARKUP_INFO)
 *
 * param[in,out] ecrCtx     Pointer to EcrCtx, from which data will be retrieved
 * param[out]    markupInfo       Storage for markup info
 * param[in,out] markupInfoSize  Buffer size
 * return ECR_OK if retrieved successfully
 */
DLL_PUBLIC ecr_status ecr_readTransactionMarkupInfo(EcrCtx* ecrCtx, char* markupInfo, size_t markupInfoSize);

/**
 * Read transaction DCC rates info (ascii encoding) (tag TAG_DCC_RATES_INFO)
 *
 * param[in,out] ecrCtx     Pointer to EcrCtx, from which data will be retrieved
 * param[out]    dccRatesInfo       Storage for DCC rates info
 * param[in,out] dccRatesInfoSize  Buffer size
 * return ECR_OK if retrieved successfully
 */
DLL_PUBLIC ecr_status ecr_readTransactionDccRatesInfo(EcrCtx* ecrCtx, char* dccRatesInfo, size_t dccRatesInfoSize);

/**
 * Read transaction exchange rate (ascii encoding) (tag TAG_EXCHANGE_RATE)
 *
 * param[in,out] ecrCtx            Pointer to EcrCtx, from which data will be retrieved
 * param[out]    exchangeRate      Buffer for exchangeRate
 * param[in,out] exchangeRateSize  Buffer size
 * return ECR_OK if retrieved successfully
 */
DLL_PUBLIC ecr_status ecr_readTransactionExchangeRate(EcrCtx* ecrCtx, char* exchangeRate, size_t exchangeRateSize);

/**
 * Read transaction DCC text 1 (ascii encoding) (tag TAG_DCC_TEXT_1)
 *
 * param[in,out] ecrCtx        Pointer to EcrCtx, from which data will be retrieved
 * param[out]    dccText1      Buffer for DCC text 1
 * param[in,out] dccText1Size  Buffer size
 * return ECR_OK if retrieved successfully
 */
DLL_PUBLIC ecr_status ecr_readTransactionDccText1(EcrCtx* ecrCtx, char* dccText1, size_t dccText1Size);

/**
 * Read transaction DCC text 2 (ascii encoding) (tag TAG_DCC_TEXT_2)
 *
 * param[in,out] ecrCtx        Pointer to EcrCtx, from which data will be retrieved
 * param[out]    dccText2      Buffer for DCC text 2
 * param[in,out] dccText2Size  Buffer size
 * return ECR_OK if retrieved successfully
 */
DLL_PUBLIC ecr_status ecr_readTransactionDccText2(EcrCtx* ecrCtx, char* dccText2, size_t dccText2Size);

/**
 * Read fleet card data tag value
 *
 * param[in,out]  ecrCtx        Pointer to EcrCtx, from which data will be retrieved
 * param[in]      fleetCardTag  Fleet card tag to be read
 * param[out]     data          Retrieved tag's value
 * param[in,out]  dataSize      As input argument, length of provided buffer, as output - retrieved data's length
 * return ECR_OK if retrieved successfully
 */
DLL_PUBLIC ecr_status ecr_readFleetCardData(EcrCtx* ecrCtx, TlvTag fleetCardTag, uint8_t* data, size_t *dataSize);

/**
 * Read fleet card product name (ascii encoding)
 *
 * param[in,out]  ecrCtx           Pointer to EcrCtx, from which data will be retrieved
 * param[in]      productId        Fleet card product id
 * param[out]     productName      Buffer for product name
 * param[in,out]  productNameSize  Buffer size
 * return ECR_OK if retrieved successfully
 */
DLL_PUBLIC ecr_status ecr_readFleetCardProductName(EcrCtx* ecrCtx, const char *productId, char* productName, size_t productNameSize);

/**
 * Read information whether fleet card indicator is present
 * (part of tag TAG_FLEET_CARD_TAG_FLAGS)
 *
 * param[in,out] ecrCtx       Pointer to EcrCtx, from which data will be retrieved
 * param[out]    information  Storage for printout information, true if is fleet card transaction,
 *                             false otherwise
 * return ECR_OK if retrieved successfully
 */
DLL_PUBLIC ecr_status ecr_readIfIsFleetCardIndicator(EcrCtx* ecrCtx, bool *information);

/**
 * Read information whether signature is required for fleet card
 * (part of tag TAG_FLEET_CARD_TAG_FLAGS)
 *
 * param[in,out] ecrCtx       Pointer to EcrCtx, from which data will be retrieved
 * param[out]    information  Storage for printout information, true if signature is required for fleet card transaction,
 *                             false otherwise
 * return ECR_OK if retrieved successfully
 */
DLL_PUBLIC ecr_status ecr_readIfIsFleetCardSignature(EcrCtx* ecrCtx, bool *information);

/**
 * Read fleet card product data from product sale list
 *
 * param[in,out]  ecrCtx        Pointer to EcrCtx, from which data will be retrieved
 * param[in]      index         Index in sale item list, starting for 1
 * param[out]     data          TLV buffer consisting all output fleet card product data found in EcrCtx
 * param[in,out]  dataSize      As input argument, size of provided buffer, as output - retrieved data's length
 *
 * return ECR_OK if retrieved successfully
 */
DLL_PUBLIC ecr_status ecr_readFleetCardProductData(EcrCtx* ecrCtx, uint8_t index, uint8_t *data, size_t *dataSize);

/**
 * Read MultiSplit Payment Data
 *
 * Records of MultiSplit Payment labels correlated with amounts (present if MSP Data Item list was send and MSP was used).
 * Label and amount shall be equality sign separated ‘=’ and records shall be pipe ‘|’ separated.
 * Encoding: CP1250
 *
 * param[in,out] ecrCtx        Pointer to EcrCtx, from which data will be retrieved
 * param[out]    mspData       Buffer for MSP data
 * param[in,out] mspDataSize   Buffer size
 *
 * return ECR_OK if retrieved successfully
 */
DLL_PUBLIC ecr_status ecr_readMSPData(EcrCtx* ecrCtx, char* mspData, size_t mspDataSize);

/**
 * Read Available Offline Spending Amount (ascii encoding) (tag TAG_VLP_LIMIT)
 *
 * param[in,out] ecrCtx     Pointer to EcrCtx, from which data will be retrieved
 * param[out]    amount     Storage for AOSA, which can be up to 6 bytes long,
 *                           so due to HEX encoding (+ NULL character),
 *                           provided buffer must be no shorter than 13 characters
 * return ECR_OK if retrieved successfully
 */
DLL_PUBLIC ecr_status ecr_readAosa(EcrCtx* ecrCtx, char* aosa);

/**
 * Read tag's value from ECR context. Any tag listed in tags.h can be read, assuming its present.
 *
 * param[in,out] ecrCtx     Pointer to EcrCtx, from which data will be retrieved
 * param[in]     tag        Tag to be read
 * param[out]    value      Retrieved tag's value
 * param[in,out] len        As input argument, length of provided buffer, as output - retrieved data's length
 * return ECR_OK if retrieved successfully
 */
DLL_PUBLIC ecr_status ecr_readTag(EcrCtx* ecrCtx, TlvTag tag, uint8_t* value, size_t* len);
/**
 * Read all transaction-related tags present in ECR context.
 *
 * param[in,out] ecrCtx          Pointer to EcrCtx, from which data will be retrieved
 * param[out]    resultTags      TLV buffer consisting all output data found in EcrCtx
 * param[in,out] resultTagsSize  As input argument, length of provided buffer, as output - retrieved data's length
 * return ECR_OK if retrieved successfully
 */
DLL_PUBLIC ecr_status ecr_readResultTags(EcrCtx* ecrCtx, uint8_t* resultTags, size_t* resultTagsSize);

// Reports functions

/**
 * Read batch status (tag TAG_BATCH_STATUS)
 *
 * param[in,out] ecrCtx          Pointer to EcrCtx, from which data will be retrieved
 * param[out]    batchStatus     Storage for batch status, values are listed in enumerations.h
 * return ECR_OK if retrieved successfully
 */
DLL_PUBLIC ecr_status ecr_readBatchStatus(EcrCtx* ecrCtx, ecr_batchStatus* batchStatus);

/**
 * Read report title
 *
 * param[in,out] ecrCtx          Pointer to EcrCtx, from which data will be retrieved
 * param[out]    reportTitle     Buffer for report title
 * param[in,out] reportTitleLen  As input argument, length of provided buffer, as output - retrieved data's length
 * return ECR_OK if retrieved successfully
 */
DLL_PUBLIC ecr_status ecr_readReportTitle(EcrCtx* ecrCtx,
                                          uint8_t* reportTitle, size_t* reportTitleLen);

/**
 * Read single entry in report
 *
 * param[in,out] ecrCtx            Pointer to EcrCtx, from which data will be retrieved
 * param[in]     entryId           Indicator which report entry is requested, starting from 1
 * param[out]    entryName         Buffer for entry name
 * param[in,out] entryNameLen      As input argument, length of provided buffer, as output - retrieved data's length
 * param[out]    transactionCount  Storage for transactions counter
 * param[out]    summaryAmount     Storage for summary amount
 * return ECR_OK if retrieved successfully
 */
DLL_PUBLIC ecr_status ecr_readReportEntry(EcrCtx* ecrCtx, size_t entryId,
                                          uint8_t* entryName, size_t* entryNameLen,
                                          uint32_t* transactionCount, int64_t* summaryAmount);
/**
 * Read single entry in report
 *
 * param[in,out] ecrCtx            Pointer to EcrCtx, from which data will be retrieved
 * param[in]     entryId           Indicator which report entry is requested, starting from 1
 * param[out]    entryName         Buffer for entry name
 * param[in,out] entryNameLen      As input argument, length of provided buffer, as output - retrieved data's length
 * param[out]    transactionCount  Storage for transactions counter
 * param[out]    summaryAmount     Storage for summary amount
 * param[out]    summaryAmountValid  Storage for information if summary amount is present for this transaction type (0/1)
 * return ECR_OK if retrieved successfully
 */
DLL_PUBLIC ecr_status ecr_readReportEntryValid(EcrCtx* ecrCtx, size_t entryId,
                                               uint8_t* entryName, size_t* entryNameLen,
                                               uint32_t* transactionCount, int64_t* summaryAmount,
                                               uint8_t* summaryAmountValid);

// Maintenance functions

/**
 * Read last known terminal status
 *
 * param[in,out] ecrCtx          Pointer to EcrCtx, from which data will be retrieved
 * param[out]    terminalStatus  Storage for terminal status, values are listed in enumerations.h
 * return ECR_OK if retrieved successfully
 */
DLL_PUBLIC ecr_status ecr_readTerminalStatus(EcrCtx* ecrCtx, ecr_terminalStatus* terminalStatus);

/**
 * Read Terminal ID (tag TAG_TID)
 *
 * param[in,out] ecrCtx     Pointer to EcrCtx, from which data will be retrieved
 * param[out]    tid        Buffer for TID
 * param[in,out] len        As input argument, length of provided buffer, as output - retrieved data's length
 * return ECR_OK if retrieved successfully
 */
DLL_PUBLIC ecr_status ecr_readTerminalId(EcrCtx* ecrCtx, uint8_t* tid, size_t* len);

/**
 * Read Merchant ID (tag TAG_MID)
 *
 * param[in,out] ecrCtx     Pointer to EcrCtx, from which data will be retrieved
 * param[out]    mid        Buffer for MID
 * param[in,out] len        As input argument, length of provided buffer, as output - retrieved data's length
 * return ECR_OK if retrieved successfully
 */
DLL_PUBLIC ecr_status ecr_readMerchantId(EcrCtx* ecrCtx, uint8_t* mid, size_t* len);

/**
 * Read Terminal Address (tags TAG_TERMINAL_ADDRESS_1, TAG_TERMINAL_ADDRESS_2, TAG_TERMINAL_ADDRESS_3)
 *
 * param[in,out] ecrCtx     Pointer to EcrCtx, from which data will be retrieved
 * param[out]    line1      Buffer for first line of address
 * param[in,out] line1Len   As input argument, length of provided buffer, as output - retrieved data's length
 * param[out]    line2      Buffer for second line of address
 * param[in,out] line2Len   As input argument, length of provided buffer, as output - retrieved data's length
 * param[out]    line3      Buffer for third line of address
 * param[in,out] line3Len   As input argument, length of provided buffer, as output - retrieved data's length
 * return ECR_OK if retrieved successfully
 */
DLL_PUBLIC ecr_status ecr_readTerminalAddress(EcrCtx* ecrCtx, uint8_t* line1, size_t* line1Len,
                                                              uint8_t* line2, size_t* line2Len,
                                                              uint8_t* line3, size_t* line3Len);


/**********************************************************************************************************
 *******************                    Communicate with terminal                       *******************
 **********************************************************************************************************/
// Transaction functions
/**
 * Order the terminal to initiate a transaction.
 *
 * note
 * Before this function is called, following tags should be set:
 * TAG_TRANSACTION_TYPE (mandatory)
 * TAG_AMOUNT (mandatory for financial transactions)
 * TAG_TRANSACTON_TITLE (optional for purchase transaction, assumed empty)
 * TAG_BLIK_REFERENCE_CODE (optional for purchase transaction, not sent if missing)
 * TAG_BLIK_ENTERED_CODE (optional for purchase transaction, not sent if missing)
 * TAG_CARD_TOKEN (optional for purchase transaction, not sent if missing)
 * TAG_TRANSACTION_TO_COMPLETE (mandatory for completion transaction)
 * TAG_TRANSACTION_TO_REVERSE (optional tag for reversal, not sent if missing)
 *
 * note
 * Execution result is indicated by returned ecr_status and return code
 * (which may be acquired by ecr_getLastReturnCode).
 * Upon successful execution, following data may be returned:
 * TAG_TRANSACTION_TYPE (mandatory, transaction type may change during transaction, for instance from purchase to cashback)
 * TAG_TRANSACTION_RETURN_CODE (mandatory)
 * TAG_TRANSACTION_NUMBER (mandatory)
 * TAG_AUTHORIZATION_CODE
 * TAG_SERVER_ERROR_MESSAGE
 * TAG_MID
 * TAG_MASKED_PAN (full PAN should never be sent to ECR)
 * TAG_TRANSACTION_DATE
 * TAG_TRANSACTION_TIME
 * TAG_APP_PREFERRED_NAME
 * TAG_USED_READER
 * TAG_TID
 * TAG_AUTHORIZATION_MESSAGE_NUMBER
 * TAG_AUTHORIZATION_TYPE
 * TAG_AMOUNT
 * TAG_AUTHORIZATION_METHOD
 * TAG_ATC
 * TAG_AC
 * TAG_AID
 * TAG_TRANSACTON_REFERENCE_NUMBER
 * TAG_TVR
 * TAG_TSI
 * TAG_TRANSACTON_TITLE
 * TAG_PRINTING_INDICATOR
 * TAG_TRANSACTION_CURRENCY (both currency code and currency label are available through ecr_read* functions)
 * TAG_TERMINAL_CURRENCY (both currency code and currency label are available through ecr_read* functions)
 * TAG_AMOUNT_IN_TERMINAL_CURRENCY
 * TAG_EXCHANGE_RATE
 * TAG_DCC_TEXT_1
 * TAG_DCC_TEXT_2
 * TAG_CASHBACK_AMOUNT
 * TAG_VLP_LIMIT (Visa Available Offline Spending Amount, should be printed on the customer receipt only,
 *                not on a merchant/control receipt)
 * TAG_CURRENCY_EXPONENT
 * TAG_BLIK_REFERENCE_CODE
 * TAG_BLIK_ENTERED_CODE
 * TAG_CARD_TOKEN
 * TAG_EMV_CRYPTOGRAM_TYPE
 * TAG_CARD_EXPIRY_DATE
 * TAG_ADDITIONAL_CARDSET_VALUE_1
 * TAG_ADDITIONAL_CARDSET_VALUE_2
 * TAG_ADDITIONAL_CARDSET_VALUE_3
 * TAG_ADDITIONAL_CARDSET_VALUE_4
 * TAG_ADDITIONAL_CARDSET_VALUE_5
 * TAG_ADDITIONAL_TRANSACTION_FLAG
 * TAG_ADDITIONAL_CUSTOM_PAN
 *
 * param[in,out] ecrCtx   All configuration and transaction data, transaction results
 * return ECR_OK if transaction started
*/
DLL_PUBLIC ecr_status ecr_startTransaction(EcrCtx* ecrCtx);

/**
 * Continue previously started transaction.
 *
 * note
 * Execution results are the same as in case of ecr_startTransaction
 *
 * param[in,out] ecrCtx   All configuration and transaction data, transaction results
 * return ECR_OK if transaction in progress
*/
DLL_PUBLIC ecr_status ecr_continueTransaction(EcrCtx* ecrCtx);

/**
* Interrupt transaction in progress.
*
* note Feature currently not supported.
*/
DLL_PUBLIC ecr_status ecr_cancelTransaction(EcrCtx* ecrCtx);

// Reports functions

/**
 * Retrieve transaction data of the last transaction.
 *
 * note
 * Execution results are the same as in case of ecr_startTransaction
 *
 * param[in,out] ecrCtx   All configuration and transaction data, transaction results
 * return ECR_OK if data acquired as requested
*/
DLL_PUBLIC ecr_status ecr_getLastTransactionData(EcrCtx* ecrCtx);

/**
 * Generate reports for all transactions.
 *
 * note Tag TAG_RESET_REPORT can be optionally set to reset reports after generation.
 *
 * note After reports are generated, tags TAG_SEQUENCE_NUMBER_FIRST_TRANSACTION
 * and TAG_SEQUENCE_NUMBER_LAST_TRANSACTION are set, indicating available transaction
 * sequence numbers
 *
 * param[in,out] ecrCtx   All configuration and transaction data, transaction results
 * return ECR_OK if data acquired as requested
*/
DLL_PUBLIC ecr_status ecr_generateReport(EcrCtx* ecrCtx);

/**
 * Get summary for a particular cardset.
 *
 * note Tag TAG_CARDSET_ID must be set to identify requested cardset
 *
 * note Use ecr_readReportTitle and ecr_readReportEntry functions to retrieve report data.
 * ecr_readReportEntry should be called with ascending entryId values starting from 1,
 * until error is returned.
 *
 * param[in,out] ecrCtx   All configuration and transaction data, transaction results
 * return ECR_OK if data acquired as requested
*/
DLL_PUBLIC ecr_status ecr_getReportCardsetSummary(EcrCtx* ecrCtx);

/**
 * Get summary for a all cardsets.
 *
 * note Use ecr_readReportTitle and ecr_readReportEntry functions to retrieve report data.
 * ecr_readReportEntry should be called with ascending entryId values starting from 1,
 * until error is returned.
 *
 * param[in,out] ecrCtx   All configuration and transaction data, transaction results
 * return ECR_OK if data acquired as requested
*/
DLL_PUBLIC ecr_status ecr_getReportTotalSummary(EcrCtx* ecrCtx);

/**
 * Generate transaction analysis grouped by currency.
 * Counters are reset after day closure.
 *
 * note Use ecr_readReportTitle and ecr_readReportEntry functions to retrieve report data.
 * ecr_readReportEntry should be called with ascending entryId values starting from 1,
 * until error is returned.
 *
 * param[in,out] ecrCtx   All configuration and transaction data, transaction results
 * return ECR_OK if data acquired as requested
*/
DLL_PUBLIC ecr_status ecr_generateDccAnalysis(EcrCtx* ecrCtx);

/**
 * Get transaction analysis for a particular currency.
 *
 * note Tag TAG_CURRENCY_ID must be set to identify required currency
 *
 * note Use ecr_readReportTitle and ecr_readReportEntry functions to retrieve report data.
 * ecr_readReportEntry should be called with ascending entryId values starting from 1,
 * until error is returned.
 *
 * param[in,out] ecrCtx   All configuration and transaction data, transaction results
 * return ECR_OK if data acquired as requested
*/
DLL_PUBLIC ecr_status ecr_getTransactionDccAnalysisCurrencySummary(EcrCtx* ecrCtx);

/**
 * Get summary of all currencies.
 *
 * note Use ecr_readReportTitle and ecr_readReportEntry functions to retrieve report data.
 * ecr_readReportEntry should be called with ascending entryId values starting from 1,
 * until error is returned.
 *
 * param[in,out] ecrCtx   All configuration and transaction data, transaction results
 * return ECR_OK if data acquired as requested
*/
DLL_PUBLIC ecr_status ecr_getTransactionDccAnalysisTotalSummary(EcrCtx* ecrCtx);

/**
 * Generate transaction analysis (details for each transaction).
 *
 * note After reports are generated, tags TAG_SEQUENCE_NUMBER_FIRST_TRANSACTION
 * and TAG_SEQUENCE_NUMBER_LAST_TRANSACTION are set, indicating available transaction
 * sequence numbers
 *
 * param[in,out] ecrCtx   All configuration and transaction data, transaction results
 * return ECR_OK if data acquired as requested
*/
DLL_PUBLIC ecr_status ecr_generateTransactionAnalysis(EcrCtx* ecrCtx);

/**
 * Get details of a single transaction from generated analysis.
 *
 * note Tag TAG_TRANSACTION_ID must be set to indicate which transaction's details are to be read
 *
 * note
 * Execution results are the same as in case of ecr_startTransaction
 *
 * param[in,out] ecrCtx   All configuration and transaction data, transaction results
 * return ECR_OK if data acquired as requested
*/
DLL_PUBLIC ecr_status ecr_getTransactionAnalysisDetails(EcrCtx* ecrCtx);

/**
 * Get details of all transactions from generated analysis.
 *
 * note Use ecr_readReportTitle and ecr_readReportEntry functions to retrieve report data.
 * ecr_readReportEntry should be called with ascending entryId values starting from 1,
 * until error is returned.
 *
 * param[in,out] ecrCtx   All configuration and transaction data, transaction results
 * return ECR_OK if data acquired as requested
*/
DLL_PUBLIC ecr_status ecr_getTransactionAnalysisSummary(EcrCtx* ecrCtx);

/**
 * Get all data sent in the last batch.
 *
 * note After successful execution, following data is set:
 * TAG_TOTAL_AMOUNT_SUM
 * TAG_BATCH_TRANSACTION_COUNT
 * TAG_BATCH_STATUS
 * TAG_ACQUIER_IDENTIFIER
 * TAG_BATCH_NUMBER
 * TAG_BATCH_DATE
 * TAG_BATCH_TIME
 * TAG_PRINTING_INDICATOR
 * TAG_TID
 * TAG_ACTIVATION_SEQUENCE_NUMBER
 * TAG_CASHIER_IDENTIFIER
 * TAG_EVOUCHER_INFO
 *
 * param[in,out] ecrCtx   All configuration and transaction data, transaction results
 * return ECR_OK if data acquired as requested
*/
DLL_PUBLIC ecr_status ecr_getBatchSummary(EcrCtx* ecrCtx);

/**
 * Get details of a single transaction sent in latest batch.
 *
 * note Tag TAG_TRANSACTION_ID must be set to indicate which transaction details should be retrieved
 *
 * note
 * Execution results are the same as in case of ecr_startTransaction
 *
 * param[in,out] ecrCtx   All configuration and transaction data, transaction results
 * return ECR_OK if data acquired as requested
*/
DLL_PUBLIC ecr_status ecr_getSingleTransactionFromBatch(EcrCtx* ecrCtx);

// Maintenance functions

/**
 * Retrieve current terminal status.
 *
 * note Use ecr_readTerminalStatus to retrieve terminal status from EcrCtx
 *
 * param[in,out] ecrCtx   All configuration and transaction data, transaction results
 * return ECR_OK if data acquired as requested
*/
DLL_PUBLIC ecr_status ecr_getTerminalStatus(EcrCtx* ecrCtx);

/**
 * Blocks until terminal status is changed.
 *
 * param[in,out] ecrCtx   All configuration and transaction data, transaction results
 * return ECR_OK if data acquired as requested
*/
DLL_PUBLIC ecr_status ecr_waitForStatusChange(EcrCtx* ecrCtx);

/**
 * Read terminal general information, like TID, MID or address.
 *
 * note Tag TAG_TERMINAL_INDEX must be set.
 *
 * note After successful execution, following data is set:
 * TAG_TID
 * TAG_MID
 * TAG_TERMINAL_ADDRESS_1
 * TAG_TERMINAL_ADDRESS_2
 * TAG_TERMINAL_ADDRESS_3
 *
 * param[in,out] ecrCtx   All configuration and transaction data, transaction results
 * return ECR_OK if data acquired as requested
*/
DLL_PUBLIC ecr_status ecr_readTerminalInformationData(EcrCtx* ecrCtx);

// Pass-through

/**
 * Pass through for raw ECR protocol commands.
 *
 * param[in,out] ecrCtx        All configuration and transaction data, transaction results
 * param[in]     request       Command to be sent, sans STX/ETX/LRC
 * param[in]     requestSize   Command length
 * param[out]    response      Response received, sans STX/EXT/LRC
 * param[in,out] responseSize  As input argument, length of provided buffer, as output - retrieved data's length
 * return ECR_OK if data exchanged
*/
DLL_PUBLIC ecr_status ecr_cmdExchange(EcrCtx* ecrCtx, const uint8_t* request, size_t requestSize, uint8_t* response, size_t* responseSize);

/**
 * Order the terminal to initiate a EV transaction.
 *
 * note
 * Before this function is called, following tags should be set:
 * TAG_EV_OPERATION_TYPE (mandatory)
 * Before this function is called, following tags may be set:
 * TAG_EV_EAN
 *
 * return ECR_OK if transaction started
*/
DLL_PUBLIC ecr_status ecr_startEvoucherTransaction(EcrCtx* ecrCtx);

/**
 * Set EV transaction operation type (tag TAG_EV_OPERATION_TYPE).
 *
 * param[in,out] ecrCtx  Pointer to EcrCtx, where data will be stored
 * param[in]     opType  operation type (0 - coupon order, 1 - coupon cancellation)
 * return ECR_OK if stored successfully
 */
DLL_PUBLIC ecr_status ecr_setEvoucherOperationType(EcrCtx* ecrCtx, const uint8_t opType);

/**
 * Set EV transaction EAN (tag TAG_EV_EAN).
 *
 * param[in,out] ecrCtx  Pointer to EcrCtx, where data will be stored
 * param[in]     ean     EAN number
 * return ECR_OK if stored successfully
 */
DLL_PUBLIC ecr_status ecr_setEvoucherEan(EcrCtx* ecrCtx, const char* ean);

/**
 * Get input from terminal.
 *
 * param[in,out] ecrCtx  Pointer to EcrCtx, where data will be stored
 * param[in]     type                  Input type
 * param[in]     maskingMode           Indicates whether the entered text should be masked
 * param[in]     textIndex             Index of text to be displayed on the terminal.
 * param[in]     minimumInputLength    Minimum input length
 * param[in]     maximumInputLength    Maximum input length
 * param[in]     inputTimeout          Timeout, in seconds
 * param[in]     preEnteredText        Pre-entered text
 * param[out]    input                 Buffer for input from terminal
 * param[in]     inputSize             As input argument, length of provided buffer, as output - retrieved data's length
 * return ECR_OK if stored successfully
 */
DLL_PUBLIC ecr_status ecr_guiExtensionGetInput(EcrCtx* ecrCtx,
                                               ecr_GuiExtensionInputType type,
                                               ecr_GuiExtensionInputMaskingMode maskingMode,
                                               ecr_GuiExtensionDisplayedTextIndex textIndex,
                                               uint16_t minimumInputLength,
                                               uint16_t maximumInputLength,
                                               uint16_t inputTimeout,
                                               const char* preEnteredText,
                                               char* input,
                                               size_t inputSize);

/**
 * Set output on terminal.
 *
 * param[in,out] ecrCtx  Pointer to EcrCtx, where data will be stored
 * param[in]     messageIndex          Index of message to be displayed on the terminal.
 * param[in]     messageType           Type of message to be displayed on terminal.
 * param[in]     outputTimeout         Timeout, in seconds.
 * param[in]     messageMode           Message displaying mode.
 * return ECR_OK if stored successfully
*/

DLL_PUBLIC ecr_status ecr_guiExtensionSetOutput(EcrCtx* ecrCtx,
                                                ecr_GuiExtensionDisplayedMessageIndex messageIndex,
                                                ecr_GuiExtensionMessageType messageType,
                                                uint16_t outputTimeout,
                                                ecr_GuiExtensionMessageMode messageMode);

/**
 * Get terminal applications versions.
 *
 * param[in,out] ecrCtx  Pointer to EcrCtx, where data will be stored
 * param[out]    versions                 Buffer for versions
 * param[in]     versionsSize             As input argument, length of provided buffer, as output - retrieved data's length
 * return ECR_OK if stored successfully
 */
DLL_PUBLIC ecr_status ecr_updaterExtensionGetApplicationsVersions(EcrCtx* ecrCtx,
                                                                  char* versions,
                                                                  size_t versionsSize);

/**
 * Get terminal OS version.
 *
 * param[in,out] ecrCtx  Pointer to EcrCtx, where data will be stored
 * param[out]    version                 Buffer for version
 * param[in]     versionSize             As input argument, length of provided buffer, as output - retrieved data's length
 * return ECR_OK if stored successfully
 */
DLL_PUBLIC ecr_status ecr_updaterExtensionGetOSVersion(EcrCtx* ecrCtx,
                                                       char* version,
                                                       size_t versionSize);

#ifdef __cplusplus
}
#endif

#endif

