/* Copyright (C) 2017 by eService
 *
 * All rights reserved.  No part of this software may be reproduced,
 * transmitted, transcribed, stored in a retrieval system, or translated
 * into any language or computer language, in any form or by any means,
 * electronic, mechanical, magnetic, optical, chemical, manual or otherwise,
 * without the prior written permission of eService.
 */
/*
 * enumerations.h
 *
 *  Created on: 4 sty 2017
 *      Author: g.wachowicz
 */

#ifndef ENUMERATIONS_H_
#define ENUMERATIONS_H_

/**
    return codes for all functions
*/
typedef enum
{
    ECR_OK,               // Function execution successful
    ECR_FAIL,             // An error occurred, please consult logs for further details
    ECR_CANCEL,           // Processing interrupted by the user
    ECR_TIMEOUT,          // Unable to get response from terminal, device is busy or disconnected
    ECR_ARGUMENT_INVALID, // Provided argument would prevent successful execution
    ECR_DATA_MISSING,     // ECR context does not have all required data, call additional setters
    ECR_UNINITIALIZED,    // ECR context has not been properly initialized
    ECR_UNSUPPORTED,      // Unsupported feature under current configuration
    ECR_LOGGING_FAIL,     // Library logger failed
    ECR_NO_TERMINAL_DATA  // Terminal doesn't have data ECR requested
} ecr_status;

/**
 * Available protocols
 */
typedef enum
{
    PROTOCOL_ESERVICE = 0,
    PROTOCOL_MCX = 0, // for backward compatibility
} ecr_communicationProtocol;

/**
    available transaction types
*/
/**
 * Should be the same values in:
 * enumerations.h ecr_transactionType
 * Enumerations.cs ecr_transactionType
 * EcrTransactionType.java EcrTransactionType
*/
typedef enum
{
    TRANS_SALE = 0,
    TRANS_CASHBACK = 1,
    TRANS_PREAUTH = 2,
    TRANS_COMPLETION = 3,
    TRANS_REFUND = 4,
    TRANS_REVERSAL = 5,
    TRANS_GIFT_ACTIVATION = 6,
    TRANS_GIFT_BALANCE = 7,
    TRANS_RECONCILE = 8,
    TRANS_TEST_CONNECTION = 9,
    TRANS_TMS = 10,
    TRANS_GIFT_TOPUP = 11,
    TRANS_EV_SALE = 12,
    TRANS_PREAUTH_TOPUP = 13,
    TRANS_PREAUTH_CANCEL = 14,
    TRANS_UNKNOWN = 15
} ecr_transactionType;

/**
    Possible transaction results
*/
typedef enum
{
    RESULT_TRANS_ACCEPTED = 0,
    RESULT_TRANS_REFUSED = 1,
    RESULT_NO_CONNECTION = 2,
    RESULT_TRANS_INTERRUPTED_BY_USER = 7
} ecr_transactionResult;

/**
    Possible terminal states
*/
typedef enum
{
    STATUS_READY_FOR_NEW_TRAN,
    STATUS_WAITING_FOR_CARD,
    STATUS_WAITING_FOR_PIN,
    STATUS_WAITING_FOR_EMV_CHOICE,
    STATUS_WAITING_FOR_HOST,
    STATUS_WAITING_FOR_SINGATURE,
    STATUS_WAITING_FOR_TRAN_END,
    STATUS_WAITING_FOR_CARD_REMOVAL,
    STATUS_BUSY,
    STATUS_IN_PROGRESS,
    STATUS_WAITING_FOR_COPY,
    STATUS_WAITING_FOR_AUTH_CODE,
    STATUS_WAITING_FOR_USER_ACTION,
    STATUS_BATCH_COMPLETED,
    STATUS_SELECTING_CURRENCY,
    STATUS_WAITING_FOR_CASHBACK,
    STATUS_TRAN_ACCEPTED,
    STATUS_WAITING_FOR_AMOUNT,
    STATUS_WAITING_FOR_SELECTION,
    STATUS_APP_ERROR,
    STATUS_RECON_NEEDED,
    STATUS_UNKNOWN
} ecr_terminalStatus;

/**
    Possible card readers
*/
typedef enum
{
    READER_CTLS,
    READER_MANUAL,
    READER_MAGSTRIPE,
    READER_ICC,
    READER_UNKNOWN
} CardReaderType;

/**
    Possible authorization types
*/
typedef enum
{
    AUTH_UNKNOWN,
    AUTH_ONLINE,
    AUTH_OFFLINE,
    AUTH_REFERRAL
} AuthorizationType;

/**
    Possible authorization methods
*/
typedef enum
{
    AUTH_METHOD_UNKNOWN,
    AUTH_METHOD_PIN,
    AUTH_METHOD_SIGN,
    AUTH_METHOD_PIN_SIGN,
    AUTH_METHOD_NO_CVM,
    AUTH_METHOD_NO_CVM_SIGNATURE_ON_FILE,
    AUTH_METHOD_CDCVM
} AuthorizationMethod;

/**
    Possible EMV Cryptogram types
*/
typedef enum
{
    CRYPT_AAC,
    CRYPT_TC,
    CRYPT_ARQC,
    CRYPT_UNKNOWN
} EmvCryptogramType;

/**
    Possible batch states
*/
typedef enum
{
    BATCH_SUCCESS,
    BATCH_SUCCESS_INCOMPLETED_PREAUTH,
    BATCH_SUCCESS_CONNECT_TO_TMS,
    BATCH_ERROR,
    BATCH_UNKNOWN
} ecr_batchStatus;

/**
    Possible handling terminal requests mode
*/
typedef enum
{
    REQUESTS_HANDLE_ALL,
    REQUESTS_HANDLE_NONE,
    REQUESTS_HANDLE_CHOSEN_BY_TERMINAL
} ecr_HandlingTerminalRequestsMode;

/**
    Possible serial baudrates
*/
typedef enum
{
    SERIAL_COM_BR_9600,
    SERIAL_COM_BR_19200,
    SERIAL_COM_BR_38400,
    SERIAL_COM_BR_56000,
    SERIAL_COM_BR_57600,
    SERIAL_COM_BR_115200
} comm_SerialBaudrate;

/**
    Possible serial data transfer modes
*/
typedef enum
{
    SERIAL_COM_8N1,
    SERIAL_COM_7E1,
    SERIAL_COM_7O1,
    SERIAL_COM_7N1
} comm_SerialDataMode;

/**
 * Printout generation status codes
 */
typedef enum
{
    PRINTOUT_OK,
    PRINTOUT_CTX_NOT_INITIALIZED,
    PRINTOUT_INSUFFICIENT_MEMORY,
    PRINTOUT_INVALID_ARGUMENT,
    PRINTOUT_INVALID_DATA,
    PRINTOUT_NO_MORE_LINES
} pr_Result;

/**
 * Printout font sizes
 */
typedef enum
{
    SIZE_NORMAL = 0,  // Default font size
    SIZE_SMALL,       // Smaller font size, if not supported, normal font should be used
    SIZE_BIG          // Bigger font size, if not supported, normal font should be used
} pr_Size;

/**
 * Printout backgrounds
 */
typedef enum
{
    BG_NONE = 0,       // Default color scheme
    BG_NEGATIVE        // Inverted color scheme
} pr_Background;

/**
 * Types of printout lines
 */
typedef enum
{
    LINE_TEXT = 0,     // Line contains text
    LINE_PIC_OR_TEXT,  // Picture should be printed, text if pictures are not supported
    LINE_PIC           // Picture should be printed if possible, omit if unsupported
} pr_LineType;

/**
 * Picture types for printout lines LINE_PIC or LINE_PIC_OR_TEXT
 */
typedef enum
{
    PIC_NONE = 0,         // No picture
    PIC_LOGO_SMALL,       // Vendor's logo (small picture)
    PIC_LOGO_NORMAL,      // Vendor's logo (medium-sized picture)
    PIC_LOGO_BIG,         // Vendor's logo (big picture)
    PIC_MASTERCARD_CTLS,  // MasterCard contactless indicator
    PIC_MAESTRO_CTLS,     // Maestro contactless indicator
    PIC_VISA_CTLS,        // VISA contactless indicator
    PIC_LINE,             // Signature line
    PIC_EV_LOGO,          // eVoucher logo
    PIC_EV_QRCODE,        // eVoucher QR code
    PIC_EV_BARCODE        // eVoucher barcode
} pr_PictureType;

/**
 * Printout font type
 */
typedef enum
{
    FONT_NORMAL = 0,     // Normal font
    FONT_BOLD            // Thicker font, use normal if not supported
} pr_FontType;

/**
 * Dictionary entries used in printout generation
 */
typedef enum
{
    DICT_UNKNOWN,                           // Printout generation error
    DICT_MERCHANT_COPY,                     // Merchant's copy of transaction receipt
    DICT_CUSTOMER_COPY,                     // Customer's copy of transaction receipt
    DICT_TID,                               // POS ID
    DICT_MID,                               // Merchant ID
    DICT_AID,                               // EMV application ID
    DICT_TC,                                // TC EMV cryptogram
    DICT_ARQC,                              // ARQC EMV cryptogram
    DICT_AAC,                               // AAC EMV cryptogram
    DICT_REFERENCE_CODE,                    // BLIK reference code
    DICT_BLIK_OPERATOR,                     // BLIK operator
    DICT_PASSWORD_CORRECT,                  // Password correct
    DICT_DATE,                              // Transaction or report date
    DICT_TIME,                              // Transaction or report hour
    DICT_DEFAULT_CURRENCY,                  // Default transaction currency, used if not provided by POS
    DICT_DEFAULT_EXPONENT,                  // Default currency exponent, used if not provided by POS, numeric
    DICT_RECEIPT_NUMBER,                    // Slip number
    DICT_VOID_FOR_RECEIPT_NUMBER,           // Slip number of voided transaction
    DICT_AUTH_CODE,                         // Authentication code
    DICT_EXPIRES,                           // Card expiry date
    DICT_SALE,                              // Sale transaction title
    DICT_CASHBACK,                          // Cashback transaction
    DICT_PREAUTH,                           // Preauthorization transaction
    DICT_COMPLETION,                        // Completion transaction
    DICT_REFUND,                            // Refund transaction
    DICT_REVERSAL,                          // Reversal Transaction
    DICT_AOSA,                              // Authorized Offline Spending Amount
    DICT_GIFT_ACTIVATION,                   // Gift activation transaction
    DICT_GIFT_BALANCE,                      // Gift balance transaction
    DICT_RECONCILE,                         // Reconciliation transaction
    DICT_CONNECTION_TEST,                   // Connection test transaction
    DICT_TMS,                               // Update transaction
    DICT_CTLS,                              // Contactless interface
    DICT_ICC,                               // ICC interface
    DICT_MAGSTRIPE,                         // Magstripe interface
    DICT_MANUAL,                            // Manual PAN entry
    DICT_PAYPASS,                           // PayPass transaction
    DICT_PAYWAVE,                           // PayWave transaction
    DICT_AMOUNT,                            // Transaction amount
    DICT_AMOUNT_CASHBACK,                   // Cashback amount
    DICT_AMOUNT_OF_TIP,                     // Amount of tip
    DICT_AMOUNT_FULL,                       // Total amount
    DICT_DECIMAL_MARK,                      // Decimal point to separate major and minor currency units
    DICT_CHARGE_ME,                         // Request to charge customer's account
    DICT_REFUND_ME,                         // Request to refund customer's account
    DICT_SIGNATURE_HERE,                    // Signature request
    DICT_SIGNATURE_NOT_REQUIRED,            // Declaration, that signature is not required
    DICT_SIGNATURE_VERIFIED,                // Signature verified
    DICT_PIN_VERIFIED,                      // PIN verified
    DICT_VOICE_AUTHORIZATION,               // Voice authorization performed
    DICT_ONLINE,                            // Transaction was processed online
    DICT_OFFLINE,                           // Transaction was processed offline
    DICT_REFERRAL,                          // Transaction was processed by phone
    DICT_DECLINE,                           // Transaction was declined
    DICT_NO_CONNECTION,                     // No connection to host during transaction
    DICT_VOIDED,                            // Transaction was voided
    DICT_TRANSACTION_TITLE,                 // Transaction title
    DICT_SUMMARY,                           // Summary report
    DICT_ANALYSIS,                          // Transaction analysis
    DICT_DCC_ANALYSIS,                      // DCC transaction analysis
    DICT_CLOSE_DAY,                         // Closing day report
    DICT_VOIDS_INCLUDED,                    // Voided transactions included in the report
    DICT_SHORT_VERSION,                     // Short version of the report
    DICT_LONG_VERSION,                      // Long version of the report
    DICT_FIRST_SLIP,                        // First slip number included in the report
    DICT_LAST_SLIP,                         // Last slip included in the report
    DICT_KEEP_RECEIPT,                      // Request to keep the receipt
    DICT_KEEP_BILL,                         // Request to keep the bill
    DICT_THANK_YOU_FOR_PAYMENT,             // Courtesy line for the customer
    DICT_CARD_SUPPORTS_ESERVICE_PAYMENTS,   // eService payments information
    DICT_SENDING_OK,                        // Daily report sent successfully
    DICT_SENDING_FAILED,                    // Unable to sent daily report
    DICT_BALANCE_OK,                        // Daily report balance OK
    DICT_BALANCE_FAILED,                    // Daily report balance not OK
    DICT_NO_TRANSACTIONS,                   // No transactions on batch report
    DICT_POS_READY,                         // All transactions settled, terminal ready
    DICT_SALE_REPORT,                       // Sales report
    DICT_VOIDED_SALE_REPORT,                // Voided sales report
    DICT_REFUND_REPORT,                     // Refunds report
    DICT_VOIDED_REFUND_REPORT,              // Voided refunds report
    DICT_COMPLETION_REPORT,                 // Completions report
    DICT_VOIDED_COMPLETION_REPORT,          // Voided completions report
    DICT_PREAUTH_REPORT,                    // Preauthorizations report
    DICT_VOIDED_PREAUTH_REPORT,             // Voided preauthorizations report
    DICT_CASHBACK_REPORT,                   // Cashbacks report
    DICT_TOTAL_REPORT,                      // All transactions report
    DICT_SUMMARY_REPORT,                    // Summary report
    DICT_NUMBER,                            // Number of performed transactions
    DICT_MERCHANT_COPY_DCC,                 // DCC version of DICT_MERCHANT_COPY
    DICT_CUSTOMER_COPY_DCC,                 // DCC version of DICT_CUSTOMER_COPY
    DICT_REFERENCE_CODE_DCC,                // DCC version of DICT_REFERENCE_CODE
    DICT_BLIK_OPERATOR_DCC,                 // DCC version of DICT_BLIK_OPERATOR
    DICT_PASSWORD_CORRECT_DCC,              // DCC version of DICT_PASSWORD_CORRECT
    DICT_DATE_DCC,                          // DCC version of DICT_DATE
    DICT_TIME_DCC,                          // DCC version of DICT_TIME
    DICT_RECEIPT_NUMBER_DCC,                // DCC version of DICT_RECEIPT_NUMBER
    DICT_VOID_FOR_RECEIPT_NUMBER_DCC,       // DCC version of DICT_VOID_FOR_RECEIPT_NUMBER
    DICT_AUTH_CODE_DCC,                     // DCC version of DICT_AUTH_CODE
    DICT_EXPIRES_DCC,                       // DCC version of DICT_EXPIRES
    DICT_SALE_DCC,                          // DCC version of DICT_SALE
    DICT_CASHBACK_DCC,                      // DCC version of DICT_CASHBACK
    DICT_PREAUTH_DCC,                       // DCC version of DICT_PREAUTH
    DICT_COMPLETION_DCC,                    // DCC version of DICT_COMPLETION
    DICT_REFUND_DCC,                        // DCC version of DICT_REFUND
    DICT_REVERSAL_DCC,                      // DCC version of DICT_REVERSAL
    DICT_AOSA_DCC,                          // DCC version of DICT_AOSA
    DICT_GIFT_ACTIVATION_DCC,               // DCC version of DICT_GIFT_ACTIVATION
    DICT_GIFT_BALANCE_DCC,                  // DCC version of DICT_GIFT_BALANCE
    DICT_RECONCILE_DCC,                     // DCC version of DICT_RECONCILE
    DICT_CONNECTION_TEST_DCC,               // DCC version of DICT_CONNECTION_TEST
    DICT_TMS_DCC,                           // DCC version of DICT_TMS
    DICT_AMOUNT_DCC,                        // DCC version of DICT_AMOUNT
    DICT_AMOUNT_CASHBACK_DCC,               // DCC version of DICT_AMOUNT_CASHBACK
    DICT_AMOUNT_OF_TIP_DCC,                 // DCC version of DICT_AMOUNT_OF_TIP
    DICT_AMOUNT_FULL_DCC,                   // DCC version of DICT_AMOUNT_FULL
    DICT_CHARGE_ME_DCC,                     // DCC version of DICT_CHARGE_ME
    DICT_REFUND_ME_DCC,                     // DCC version of DICT_REFUND_ME
    DICT_SIGNATURE_HERE_DCC,                // DCC version of DICT_SIGNATURE_HERE
    DICT_SIGNATURE_VERIFIED_DCC,            // DCC version of DICT_SIGNATURE_VERIFIED
    DICT_PIN_VERIFIED_DCC,                  // DCC version of DICT_PIN_VERIFIED
    DICT_VOICE_AUTHORIZATION_DCC,           // DCC version of DICT_VOICE_AUTHORIZATION
    DICT_DECLINE_DCC,                       // DCC version of DICT_DECLINE
    DICT_NO_CONNECTION_DCC,                 // DCC version of DICT_NO_CONNECTION_DCC
    DICT_VOIDED_DCC,                        // DCC version of DICT_VOIDED
    DICT_TRANSACTION_TITLE_DCC,             // DCC version of DICT_TRANSACTION_TITLE
    DICT_AMOUNT_IN_MERCHANT_CURRENCY_DCC,   // Amount of DCC transaction before conversion
    DICT_EXCHANGE_RATE_DCC,                 // DCC exchange rate
    DICT_FEE_MAKUP_DCC,                     // Default DCC fee/mark-up text if none is provided by the terminal
    DICT_DEFAULT_FEE_MAKUP_DCC,             // Default DCC fee/mark-up value if none is provided by the terminal
    DICT_RATE_EXCHANGE_RATE_BASED_ON_DCC,   // Exchange rate source
    DICT_PROVIDER_DCC,                      // Default exchange rate source
    DICT_RATE_AT_DATE_DCC,                  // DCC exchange time
    DICT_THANK_YOU_FOR_PAYMENT_DCC,         // Courtesy line for the customer
    DICT_GIFT_TOPUP,                        // Gift topup
    DICT_GIFT_TOPUP_DCC,                    // Gift topup, dcc version
    DICT_SIGNATURE_ON_FILE,                 // Signature on file
    DICT_SIGNATURE_ON_FILE_DCC,             // Signature on file, dcc version
    DICT_VERIFIED_BY_DEVICE,                // Verified by device
    DICT_VERIFIED_BY_DEVICE_DCC,            // Verified by device, dcc version
    DICT_SIGNATURE_NOT_REQUIRED_DCC,        // Signature not required, dcc version
    DICT_FLEET_CARD_VEHICLE_NUMBER,         // Fleet card vehicle number
    DICT_FLEET_CARD_DRIVER_NUMBER,          // Fleet card driver number
    DICT_FLEET_CARD_MILEAGE,                // Fleet card mileage
    DICT_FLEET_CARD_CAR_REGISTRATION_NR,    // Fleet card car registration number
    DICT_FLEET_CARD_UNIT_NUMBER,            // Fleet card unit number
    DICT_FLEET_CARD_ADDITIONAL_DATA,        // Fleet card additional data
    DICT_FLEET_CARD_CAR_REPLACE_INDICATOR,  // Fleet card car replacement indicator
    DICT_FLEET_CARD_DRIVER_CODE,            // Fleet card driver code
    DICT_FLEET_CARD_CASHIER_SIGN,           // Fleet card cashier for sign
    DICT_FLEET_CARD_CLIENT_SIGN,            // Fleet card client on sign
    DICT_PREAUTH_TOPUP,                     // Preauthorization topup transaction
    DICT_PREAUTH_TOPUP_DCC,                 // DCC version of DICT_PREAUTH_TOPUP
    DICT_PREAUTH_CANCEL,                    // Preauthorization cancel transaction
    DICT_PREAUTH_CANCEL_DCC,                // DCC version of DICT_PREAUTH_CANCEL
    DICT_PREAUTH_TOPUP_REPORT,              // Preauthorizations' topups report
    DICT_PREAUTH_CANCEL_REPORT,             // Preauthorizations' cancels report
    DICT_DECIMAL_SEPARATOR_DCC,             // DCC decimal separator for markup and exchange rate
    DICT_VARIABLE_SYMBOL,                   // Transaction variable symbol
    DICT_VARIABLE_SYMBOL_DCC,               // DCC version of DICT_VARIABLE_SYMBOL
    DICT_SPECIFIC_SYMBOL,                   // Transaction specific symbol
    DICT_SPECIFIC_SYMBOL_DCC,               // DCC version of DICT_SPECIFIC_SYMBOL
    DICT_MSP_AMOUNT_INCLUDING,              // MultiSplit Payment amount including
    DICT_MSP_AMOUNT_INCLUDING_DCC,          // DCC version of DICT_MSP_AMOUNT_INCLUDING
    DICT_EV_SALE,                           // eVoucher Sale transaction title
    DICT_AMOUNT_WITHOUT_TIP_DCC             // Amount label for DCC with TIP printouts
} pr_Dictionary;

/**
 * Format field IDs for fiscal printout
 */
typedef enum
{
    FFI_SLIP_NUMBER,                        // Receipt number
    FFI_TRANSACTION_NUMBER,                 // Transaction number
    FFI_TID_MID,                            // POS ID and merchand ID separated by FISCAL_ENTRY_SEPARATOR
    FFI_CARD_DATA,                          // PAN and expiry date separated by FISCAL_ENTRY_SEPARATOR
    FFI_CARD_LABEL,                         // Card mnemonic identifier
    FFI_AMOUNT_SALE,                        // Amount for sale transaction
    FFI_AMOUNT_REFUND,                      // Amount for refund transaction
    FFI_AMOUNT_PREAUTH,                     // Amount for preauthorization transaction
    FFI_AMOUNT_CASHBACK,                    // Amount for cashback transaction
    FFI_AMOUNT_OF_TIP,                      // Amount of tip
    FFI_AMOUNT_TOTAL,                       // Full transaction amount
    FFI_AUTH_CODE,                          // Authorization code
    FFI_AOSA,                               // Authorized offline spending amount
    FFI_CHARGE_MY_ACCOUNT,                  // Request to charge customer's account
    FFI_REFUND_MY_ACCOUNT,                  // Request to refund customer's account
    FFI_TRANSACTION_VOIDED,                 // Transaction voided status
    FFI_PIN_OK,                             // Confirmation of correct PIN
    FFI_SIG_LINE,                           // Signature line
    FFI_SIG_HERE,                           // Signature request
    FFI_MERCHANT_COPY,                      // Merchant copy
    FFI_CUSTOMER_COPY,                      // Customer copy
    FFI_AID,                                // EMV application ID
    FFI_TC,                                 // TC cryptogram
    FFI_AAC,                                // AAC cryptogram
    FFI_ARQC,                               // ARQC cryptogram
    FFI_TRANSACION_DECLINED,                // Transaction declined
    FFI_HOST_MESSAGE,                       // Message incoming from host
    FFI_TRANSACTION_NUMBER_DCC,             // Transaction number for DCC transaction
    FFI_CARD_DATA_DCC,                      // PAN and expiry date for DCC transaction separated by FISCAL_ENTRY_SEPARATOR
    FFI_CARD_LABEL_DCC,                     // Card mnemonic identifier for DCC transaction
    FFI_AMOUNT_SALE_DCC,                    // Amount for sale transaction in foreign currency
    FFI_AMOUNT_REFUND_DCC,                  // Amount for refund transaction in foreign currency
    FFI_AMOUNT_PREAUTH_DCC,                 // Amount for preauthorization transaction in foreign currency
    FFI_AMOUNT_CASHBACK_DCC,                // Amount for cashback transaction in foreign currency
    FFI_AMOUNT_OF_TIP_DCC,                  // Amount of tip in foreign currency
    FFI_AMOUNT_TOTAL_DCC,                   // Full transaction amount in foreign currency
    FFI_AUTH_CODE_DCC,                      // Authorization code for DCC transaction
    FFI_AOSA_DCC,                           // Authorized offline spending amount for DCC transaction
    FFI_PIN_OK_DCC,                         // PIN confirmation for DCC transaction
    FFI_SIG_HERE_DCC,                       // Signature request for DCC transaction
    FFI_HOST_MESSAGE_DCC,                   // Message incoming from host for DCC transaction
    FFI_PROVIDER_DCC,                       // DCC service provider
    FFI_CUSTOM                              // Custom line, no format
} pr_FiscalFormatId;

typedef enum
{
    TEXT_INDEX_ENTER_PIN_FOR_LOYALITY_CARD = 1,
    TEXT_INDEX_AUTHORIZATION_CODE_FOR_PARCEL = 2,
    TEXT_INDEX_UNKNOWN
} ecr_GuiExtensionDisplayedTextIndex;

typedef enum
{
    MESSAGE_INDEX_INVALID_CODE = 0,
    MESSAGE_INDEX_CODE_OK = 1,
    MESSAGE_INDEX_UNKNOWN
} ecr_GuiExtensionDisplayedMessageIndex;

typedef enum
{
    INPUT_TYPE_TEXT_NUMERIC = 1,
    INPUT_TYPE_UNKNOWN
} ecr_GuiExtensionInputType;

typedef enum
{
    INPUT_MASKING_MODE_OVERT = 0,
    INPUT_MASKING_MODE_MASKED = 1,
    INPUT_MASKING_MODE_UNKNOWN
} ecr_GuiExtensionInputMaskingMode;

typedef enum
{
    MESSAGE_TYPE_REFUSE = 0,
    MESSAGE_TYPE_ACCEPT = 1,
    MESSAGE_TYPE_UNKNOWN
} ecr_GuiExtensionMessageType;

typedef enum
{
    MESSAGE_MODE_SPECIFIED_TIME = 0,
    MESSAGE_MODE_SHORTENABLE_BY_BUTTON = 1,
    MESSAGE_MODE_UNKNOWN
} ecr_GuiExtensionMessageMode;

#endif /* ENUMERATIONS_H_ */
