/* Copyright (C) 2017 by eService
 *
 * All rights reserved.  No part of this software may be reproduced,
 * transmitted, transcribed, stored in a retrieval system, or translated
 * into any language or computer language, in any form or by any means,
 * electronic, mechanical, magnetic, optical, chemical, manual or otherwise,
 * without the prior written permission of eService.
 */
/*
 * printouts.h
 *
 *  Created on: 1 mar 2017
 *      Author: przemyslaw.ogorzalek
 */

#ifndef SRC_LIB_API_PRINTOUTS_H_
#define SRC_LIB_API_PRINTOUTS_H_

#include "PrintoutStructures.h"
#include "dll_macro.h"
#include "ecrlib.h"

#ifdef __cplusplus
extern "C" {
#endif

// Definition of the structure is not provided, as it should not be modified by higher abstraction layers.
// Object will be dynamically created in pr_initPrintoutCtx and deleted in pr_cleanPrintoutCtx
struct PrintoutCtx_s;
typedef struct PrintoutCtx_s PrintoutCtx;

// Separator character for multiple entries in a single printout line.
// For example, for fiscal format "TID: ######## MID: ###############"
// entries will be provided as "12345678FISCAL_ENTRY_SEPARATOR123451234512345"
#define FISCAL_ENTRY_SEPARATOR 0x1E

/**
 * Create and initialize printout context.
 *
 * param[in, out]  ctx    Pointer to pointer to printout context. Printout context is dynamically allocated
 *                         and must be destroyed with pr_cleanPrintoutCtx function.
 * result  PRINTOUT_OK if creation was successful, error code otherwise.
 */
DLL_PUBLIC pr_Result pr_initPrintoutCtx(PrintoutCtx** ctx);

/**
 * Cleanup and delete printout context.
 *
 * param[in, out]  ctx  Pointer to pointer to printout context. Will be set to NULL after cleanup.
 */
DLL_PUBLIC void pr_cleanPrintoutCtx(PrintoutCtx** ctx);

/**
 * Change single phrase in library internal dictionary. Dictionary is independent from printout context,
 * calling pr_initPrintoutCtx or pr_cleanPrintoutCtx will not set it back to default. Please refer to
 * library documentation for translation tips regarding usage of each phrase, in order to ensure
 * positive user experience.
 *
 * param[in]  phrase  ID of modified phrase
 * param[in]  text    New dictionary entry
 */
DLL_PUBLIC void pr_setDictionaryPhrase(pr_Dictionary phrase, const char* text);

/**
 * Change multiple phrases in library internal dictionary. Dictionary is independent from printout context,
 * calling pr_initPrintoutCtx or pr_cleanPrintoutCtx will not set it back to default. Please refer to
 * library documentation for translation tips regarding usage of each phrase, in order to ensure
 * positive user experience.
 *
 * param[in]  phrases       List of IDs for modified phrases
 * param[in]  phrasesCount  Length of phrases list
 * param[in]  texts         New dictionary entries, must be in the same order as list of phrases
 * param[in]  textsCount    Length of texts list, must be the same as phrasesCount
 * return PRINTOUT_OK if both lists are of equal length, error code otherwise
 */
DLL_PUBLIC pr_Result pr_setupDictionary(pr_Dictionary* phrases, size_t phrasesCount,
                             const char** texts, size_t textsCount);

/**
 * Read phrases from file into library internal dictionary. Dictionary is independent from printout context,
 * calling pr_initPrintoutCtx or pr_cleanPrintoutCtx will not set it back to default. Please refer to
 * library documentation for translation tips regarding usage of each phrase, in order to ensure
 * positive user experience.
 *
 * param[in]  filename       Dictionary filename
 * return PRINTOUT_OK if reading from file was successfull
 */
DLL_PUBLIC pr_Result pr_setupDictionaryFromFile(const char* filename);

/**
 * Sets the path where the library looks for language files.
 *
 * param[in] path   Path to language files
 */
DLL_PUBLIC void pr_setLanguageFilesDefaultPath(const char* path);

/**
 * Change properties of fiscal format line. Please refer to pr_FiscalFormatLine in PrintoutStructures.h
 * to examine configurable properties.
 *
 * param[in] field   Fiscal format field ID
 * param[in] line    Fiscal format field properties
 */
DLL_PUBLIC void pr_setFiscalFormatLine(pr_FiscalFormatId field, pr_FiscalFormatLine line);

/**
 * Set line width for line printed in normal sized font.
 *
 * param[in,out]  ctx      Printout context where configuration is kept
 * param[in]      lineLen  Line width, must not exceed MAX_LINE_LEN value
 */
DLL_PUBLIC pr_Result pr_setNormalLineLen(PrintoutCtx* ctx, uint32_t lineLen);

/**
 * Set line width for line printed in normal sized font.
 *
 * param[in,out]  ctx      Printout context where configuration is kept
 * param[in]      lineLen  Line width, must not exceed MAX_LINE_LEN value
 */
DLL_PUBLIC pr_Result pr_setSmallLineLen(PrintoutCtx* ctx, uint32_t lineLen);

/**
 * Set line width for line printed in normal sized font.
 *
 * param[in,out]  ctx      Printout context where configuration is kept
 * param[in]      lineLen  Line width, must not exceed MAX_LINE_LEN value
 */
DLL_PUBLIC pr_Result pr_setBigLineLen(PrintoutCtx* ctx, uint32_t lineLen);

/**
 * Disable printing POS address.
 *
 * param[in]  True if POS address should not be printed, false otherwise (default)
 */
DLL_PUBLIC void pr_setHidingAddress(bool hideAddress);

/**
 * Enable using Signature Verified line
 *
 * param[in]  True if Signature Verified line should be printed, false otherwise (default)
 */
DLL_PUBLIC void pr_setUsingSignatureVerifiedLine(bool useSignatureVerifiedLine);

//////////////////////////////////////////

/**
 * Prepare post-transaction printout for non-fiscal printer. All transaction data will be extracted
 * form ecrCtx.
 *
 * param[in,out]  ctx          Printout context. As input it carries library configuration, as output
 *                              it contains generated lines. All data except library configuration
 *                              is cleared at the beginning, there is no need to cleanup it between printouts.
 * param[in]      ecrCtx       ECR context with transaction results and terminal data (result of
 *                              ecr_readTerminalInformationData function).
 * param[in]      customerCopy Information whether the printout is intended for the merchant or the customer
 * result PRINTOUT_OK if printout generation was completed without problems, error code otherwise
 */
DLL_PUBLIC pr_Result pr_prepareTransactionPrintout(PrintoutCtx* ctx, EcrCtx* ecrCtx,
                                                   bool customerCopy);

/**
 * Prepare Evoucher printout for non-fiscal printer. All transaction data will be extracted
 * form ecrCtx.
 *
 * param[in,out]  ctx          Printout context. As input it carries library configuration, as output
 *                              it contains generated lines. All data except library configuration
 *                              is cleared at the beginning, there is no need to cleanup it between printouts.
 * param[in]      ecrCtx       ECR context with transaction results and terminal data (result of
 *                              ecr_readTerminalInformationData function).
 * param[in]      customerCopy Information whether the printout is intended for the merchant or the customer
 * result PRINTOUT_OK if printout generation was completed without problems, error code otherwise
 */
DLL_PUBLIC pr_Result pr_prepareEvoucherPrintout(PrintoutCtx* ctx, EcrCtx* ecrCtx,
                                                bool customerCopy);

/**
 * Prepare printout with short summary report. All report data will be extracted
 * form ecrCtx.
 *
 * param[in,out]  ctx          Printout context. As input it carries library configuration, as output
 *                              it contains generated lines. All data except library configuration
 *                              is cleared at the beginning, there is no need to cleanup it between printouts.
 * param[in]      ecrCtx       ECR context with generated report and terminal data (result of
 *                              ecr_readTerminalInformationData function).
 * result PRINTOUT_OK if printout generation was completed without problems, error code otherwise
 */
DLL_PUBLIC pr_Result pr_prepareShortSummary(PrintoutCtx* ctx, EcrCtx* ecrCtx);

/**
 * Start printout with full summary report. Report data will be extracted
 * form ecrCtx. This function should be called before first report entry is retrieved from the terminal.
 *
 * param[in,out]  ctx          Printout context. As input it carries library configuration, as output
 *                              it contains generated lines. All data except library configuration
 *                              is cleared at the beginning, there is no need to cleanup it between printouts.
 * param[in]      ecrCtx       ECR context with terminal data (result of ecr_readTerminalInformationData function).
 * result PRINTOUT_OK if printout generation was completed without problems, error code otherwise
 */
DLL_PUBLIC pr_Result pr_startFullSummary(PrintoutCtx* ctx, EcrCtx* ecrCtx);

/**
 * Add report entry. Data will be extracted form ecrCtx.
 * This function should be called after each report entry is retrieved from the terminal.
 *
 * param[in,out]  ctx          Printout context. As input it carries library configuration, as output
 *                              it contains generated lines. Context should be previously set up with
 *                              pr_startFullSummary function
 * param[in]      ecrCtx       ECR context with report entry
 * result PRINTOUT_OK if printout generation was completed without problems, error code otherwise
 */
DLL_PUBLIC pr_Result pr_addFullSummaryEntry(PrintoutCtx* ctx, EcrCtx* ecrCtx);

/**
 * Finish printout with full summary report. Data will be extracted form ecrCtx.
 * This function should be called after last report entry is added with pr_addFullSummaryEntry.
 *
 * param[in,out]  ctx          Printout context. As input it carries library configuration, as output
 *                              it contains generated lines.
 * param[in]      ecrCtx       ECR context with data
 * result PRINTOUT_OK if printout generation was completed without problems, error code otherwise
 */
DLL_PUBLIC pr_Result pr_finishFullSummary(PrintoutCtx* ctx, EcrCtx* ecrCtx);

/**
 * Prepare printout with short transaction analysis report. All report data will be extracted
 * form ecrCtx.
 *
 * param[in,out]  ctx          Printout context. As input it carries library configuration, as output
 *                              it contains generated lines. All data except library configuration
 *                              is cleared at the beginning, there is no need to cleanup it between printouts.
 * param[in]      ecrCtx       ECR context with generated report and terminal data (result of
 *                              ecr_readTerminalInformationData function).
 * result PRINTOUT_OK if printout generation was completed without problems, error code otherwise
 */
DLL_PUBLIC pr_Result pr_prepareShortTransactionAnalysis(PrintoutCtx* ctx, EcrCtx* ecrCtx);

/**
 * Start printout with full transaction analysis report. Report data will be extracted
 * form ecrCtx. This function should be called before first report entry is retrieved from the terminal.
 *
 * param[in,out]  ctx          Printout context. As input it carries library configuration, as output
 *                              it contains generated lines. All data except library configuration
 *                              is cleared at the beginning, there is no need to cleanup it between printouts.
 * param[in]      ecrCtx       ECR context with terminal data (result of ecr_readTerminalInformationData function).
 * result PRINTOUT_OK if printout generation was completed without problems, error code otherwise
 */
DLL_PUBLIC pr_Result pr_startTransactionAnalysis(PrintoutCtx* ctx, EcrCtx* ecrCtx);

/**
 * Add report entry. Data will be extracted form ecrCtx.
 * This function should be called after each report entry is retrieved from the terminal.
 *
 * param[in,out]  ctx          Printout context. As input it carries library configuration, as output
 *                              it contains generated lines. Context should be previously set up with
 *                              pr_startTransactionAnalysis function
 * param[in]      ecrCtx       ECR context with report entry
 * result PRINTOUT_OK if printout generation was completed without problems, error code otherwise
 */
DLL_PUBLIC pr_Result pr_addFullTransactionAnalysisEntry(PrintoutCtx* ctx, EcrCtx* ecrCtx);

/**
 * Add report summary. Data will be extracted form ecrCtx.
 * This function should be called after report summary is retrieved from the terminal.
 *
 * param[in,out]  ctx          Printout context. As input it carries library configuration, as output
 *                              it contains generated lines. Context should be previously set up with
 *                              pr_startTransactionAnalysis function
 * param[in]      ecrCtx       ECR context with report summary
 * result PRINTOUT_OK if printout generation was completed without problems, error code otherwise
 */
DLL_PUBLIC pr_Result pr_addFullTransactionAnalysisSummary(PrintoutCtx* ctx, EcrCtx* ecrCtx);

/**
 * Finish printout with full transaction analysis report. Data will be extracted form ecrCtx.
 * This function should be called after transaction analysis summary is added with
 * pr_addFullTransactionAnalysisSummary.
 *
 * param[in,out]  ctx          Printout context. As input it carries library configuration, as output
 *                              it contains generated lines.
 * param[in]      ecrCtx       ECR context with data
 * result PRINTOUT_OK if printout generation was completed without problems, error code otherwise
 */
DLL_PUBLIC pr_Result pr_finishTransactionAnalysis(PrintoutCtx* ctx, EcrCtx* ecrCtx);

/**
 * Start printout with full DCC analysis report. Report data will be extracted
 * form ecrCtx. This function should be called before first report entry is retrieved from the terminal.
 *
 * param[in,out]  ctx          Printout context. As input it carries library configuration, as output
 *                              it contains generated lines. All data except library configuration
 *                              is cleared at the beginning, there is no need to cleanup it between printouts.
 * param[in]      ecrCtx       ECR context with terminal data (result of ecr_readTerminalInformationData function).
 * result PRINTOUT_OK if printout generation was completed without problems, error code otherwise
 */
DLL_PUBLIC pr_Result pr_startDccAnalysis(PrintoutCtx* ctx, EcrCtx* ecrCtx);

/**
 * Add report entry. Data will be extracted form ecrCtx.
 * This function should be called after each report entry is retrieved from the terminal.
 *
 * param[in,out]  ctx          Printout context. As input it carries library configuration, as output
 *                              it contains generated lines. Context should be previously set up with
 *                              pr_startDccAnalysis function
 * param[in]      ecrCtx       ECR context with report entry
 * result PRINTOUT_OK if printout generation was completed without problems, error code otherwise
 */
DLL_PUBLIC pr_Result pr_addDccAnalysisEntry(PrintoutCtx* ctx, EcrCtx* ecrCtx);

/**
 * Finish printout with DCC transaction analysis report. Data will be extracted form ecrCtx.
 * This function should be called after last report entry is added with pr_addDccAnalysisEntry.
 *
 * param[in,out]  ctx          Printout context. As input it carries library configuration, as output
 *                              it contains generated lines.
 * param[in]      ecrCtx       ECR context with data
 * result PRINTOUT_OK if printout generation was completed without problems, error code otherwise
 */
DLL_PUBLIC pr_Result pr_finishDccAnalysis(PrintoutCtx* ctx, EcrCtx* ecrCtx);

/**
 * Start printout with closing report. Report data will be extracted
 * form ecrCtx. This function should be called before first report entry is retrieved from the terminal.
 *
 * param[in,out]  ctx          Printout context. As input it carries library configuration, as output
 *                              it contains generated lines. All data except library configuration
 *                              is cleared at the beginning, there is no need to cleanup it between printouts.
 * param[in]      ecrCtx       ECR context with terminal data (result of ecr_readTerminalInformationData function).
 * result PRINTOUT_OK if printout generation was completed without problems, error code otherwise
 */
DLL_PUBLIC pr_Result pr_startClosingDay(PrintoutCtx* ctx, EcrCtx* ecrCtx);

/**
 * Add report entry. Data will be extracted form ecrCtx.
 * This function should be called after each report entry is retrieved from the terminal.
 *
 * param[in,out]  ctx          Printout context. As input it carries library configuration, as output
 *                              it contains generated lines. Context should be previously set up with
 *                              pr_startClosingDay function
 * param[in]      ecrCtx       ECR context with report entry
 * result PRINTOUT_OK if printout generation was completed without problems, error code otherwise
 */
DLL_PUBLIC pr_Result pr_addClosingDayTransaction(PrintoutCtx* ctx, EcrCtx* ecrCtx);

/**
 * Finish printout with closing day report. Data will be extracted form ecrCtx.
 * This function should be called after last report entry is added with pr_addClosingDayTransaction.
 *
 * param[in,out]  ctx          Printout context. As input it carries library configuration, as output
 *                              it contains generated lines.
 * param[in]      ecrCtx       ECR context with data
 * result PRINTOUT_OK if printout generation was completed without problems, error code otherwise
 */
DLL_PUBLIC pr_Result pr_finishClosingDay(PrintoutCtx* ctx, EcrCtx* ecrCtx);

//////////////////////////////////////////

/**
 * Prepare post-transaction printout for fiscal printer. All transaction data will be extracted
 * form ecrCtx.
 *
 * param[in,out]  ctx          Printout context. As input it carries library configuration, as output
 *                              it contains generated lines. All data except library configuration
 *                              is cleared at the beginning, there is no need to cleanup it between printouts.
 * param[in]      ecrCtx       ECR context with transaction results and terminal data (result of
 *                              ecr_readTerminalInformationData function).
 * param[in]      customerCopy Information whether the printout is intended for the merchant or the customer
 * result PRINTOUT_OK if printout generation was completed without problems, error code otherwise
 */
DLL_PUBLIC pr_Result pr_prepareTransactionFiscalPrintout(PrintoutCtx* ctx, EcrCtx* ecrCtx,
                                                         bool customerCopy);

/**
 * Prepare fiscal printout with short summary report. All report data will be extracted
 * form ecrCtx.
 *
 * param[in,out]  ctx          Printout context. As input it carries library configuration, as output
 *                              it contains generated lines. All data except library configuration
 *                              is cleared at the beginning, there is no need to cleanup it between printouts.
 * param[in]      ecrCtx       ECR context with generated report and terminal data (result of
 *                              ecr_readTerminalInformationData function).
 * result PRINTOUT_OK if printout generation was completed without problems, error code otherwise
 */
DLL_PUBLIC pr_Result pr_prepareFiscalShortSummary(PrintoutCtx* ctx, EcrCtx* ecrCtx);

/**
 * Start fiscal printout with full summary report. Report data will be extracted
 * form ecrCtx. This function should be called before first report entry is retrieved from the terminal.
 *
 * param[in,out]  ctx          Printout context. As input it carries library configuration, as output
 *                              it contains generated lines. All data except library configuration
 *                              is cleared at the beginning, there is no need to cleanup it between printouts.
 * param[in]      ecrCtx       ECR context with terminal data (result of ecr_readTerminalInformationData function).
 * result PRINTOUT_OK if printout generation was completed without problems, error code otherwise
 */
DLL_PUBLIC pr_Result pr_startFiscalFullSummary(PrintoutCtx* ctx, EcrCtx* ecrCtx);

/**
 * Add report entry. Data will be extracted form ecrCtx.
 * This function should be called after each report entry is retrieved from the terminal.
 *
 * param[in,out]  ctx          Printout context. As input it carries library configuration, as output
 *                              it contains generated lines. Context should be previously set up with
 *                              pr_startFiscalFullSummary function
 * param[in]      ecrCtx       ECR context with report entry
 * result PRINTOUT_OK if printout generation was completed without problems, error code otherwise
 */
DLL_PUBLIC pr_Result pr_addFiscalFullSummaryEntry(PrintoutCtx* ctx, EcrCtx* ecrCtx);

/**
 * Finish printout with full summary report. Data will be extracted form ecrCtx.
 * This function should be called after last report entry is added with pr_addFullSummaryEntry.
 *
 * param[in,out]  ctx          Printout context. As input it carries library configuration, as output
 *                              it contains generated lines.
 * param[in]      ecrCtx       ECR context with data
 * result PRINTOUT_OK if printout generation was completed without problems, error code otherwise
 */
DLL_PUBLIC pr_Result pr_finishFiscalFullSummary(PrintoutCtx* ctx, EcrCtx* ecrCtx);

/**
 * Prepare fiscal printout with short transaction analysis report. All report data will be extracted
 * form ecrCtx.
 *
 * param[in,out]  ctx          Printout context. As input it carries library configuration, as output
 *                              it contains generated lines. All data except library configuration
 *                              is cleared at the beginning, there is no need to cleanup it between printouts.
 * param[in]      ecrCtx       ECR context with generated report and terminal data (result of
 *                              ecr_readTerminalInformationData function).
 * result PRINTOUT_OK if printout generation was completed without problems, error code otherwise
 */
DLL_PUBLIC pr_Result pr_prepareFiscalShortTransactionAnalysis(PrintoutCtx* ctx, EcrCtx* ecrCtx);

/**
 * Start fiscal printout with full transaction analysis report. Report data will be extracted
 * form ecrCtx. This function should be called before first report entry is retrieved from the terminal.
 *
 * param[in,out]  ctx          Printout context. As input it carries library configuration, as output
 *                              it contains generated lines. All data except library configuration
 *                              is cleared at the beginning, there is no need to cleanup it between printouts.
 * param[in]      ecrCtx       ECR context with terminal data (result of ecr_readTerminalInformationData function).
 * result PRINTOUT_OK if printout generation was completed without problems, error code otherwise
 */
DLL_PUBLIC pr_Result pr_startFiscalTransactionAnalysis(PrintoutCtx* ctx, EcrCtx* ecrCtx);

/**
 * Add report entry. Data will be extracted form ecrCtx.
 * This function should be called after each report entry is retrieved from the terminal.
 *
 * param[in,out]  ctx          Printout context. As input it carries library configuration, as output
 *                              it contains generated lines. Context should be previously set up with
 *                              pr_startFiscalTransactionAnalysis function
 * param[in]      ecrCtx       ECR context with report entry
 * result PRINTOUT_OK if printout generation was completed without problems, error code otherwise
 */
DLL_PUBLIC pr_Result pr_addFiscalFullTransactionAnalysisEntry(PrintoutCtx* ctx, EcrCtx* ecrCtx);

/**
 * Add report summary. Data will be extracted form ecrCtx.
 * This function should be called after report summary is retrieved from the terminal.
 *
 * param[in,out]  ctx          Printout context. As input it carries library configuration, as output
 *                              it contains generated lines. Context should be previously set up with
 *                              pr_startFiscalTransactionAnalysis function
 * param[in]      ecrCtx       ECR context with report summary
 * result PRINTOUT_OK if printout generation was completed without problems, error code otherwise
 */
DLL_PUBLIC pr_Result pr_addFiscalFullTransactionAnalysisSummary(PrintoutCtx* ctx, EcrCtx* ecrCtx);

/**
 * Finish fiscal printout with full transaction analysis report. Data will be extracted form ecrCtx.
 * This function should be called after transaction analysis summary is added with
 * pr_addFiscalFullTransactionAnalysisSummary.
 *
 * param[in,out]  ctx          Printout context. As input it carries library configuration, as output
 *                              it contains generated lines.
 * param[in]      ecrCtx       ECR context with data
 * result PRINTOUT_OK if printout generation was completed without problems, error code otherwise
 */
DLL_PUBLIC pr_Result pr_finishFiscalTransactionAnalysis(PrintoutCtx* ctx, EcrCtx* ecrCtx);

/**
 * Start fiscal printout with full DCC analysis report. Report data will be extracted
 * form ecrCtx. This function should be called before first report entry is retrieved from the terminal.
 *
 * param[in,out]  ctx          Printout context. As input it carries library configuration, as output
 *                              it contains generated lines. All data except library configuration
 *                              is cleared at the beginning, there is no need to cleanup it between printouts.
 * param[in]      ecrCtx       ECR context with terminal data (result of ecr_readTerminalInformationData function).
 * result PRINTOUT_OK if printout generation was completed without problems, error code otherwise
 */
DLL_PUBLIC pr_Result pr_startFiscalDccAnalysis(PrintoutCtx* ctx, EcrCtx* ecrCtx);

/**
 * Add report entry. Data will be extracted form ecrCtx.
 * This function should be called after each report entry is retrieved from the terminal.
 *
 * param[in,out]  ctx          Printout context. As input it carries library configuration, as output
 *                              it contains generated lines. Context should be previously set up with
 *                              pr_startFiscalDccAnalysis function
 * param[in]      ecrCtx       ECR context with report entry
 * result PRINTOUT_OK if printout generation was completed without problems, error code otherwise
 */
DLL_PUBLIC pr_Result pr_addFiscalDccAnalysisEntry(PrintoutCtx* ctx, EcrCtx* ecrCtx);

/**
 * Finish fiscal printout with DCC transaction analysis report. Data will be extracted form ecrCtx.
 * This function should be called after last report entry is added with pr_addFiscalDccAnalysisEntry.
 *
 * param[in,out]  ctx          Printout context. As input it carries library configuration, as output
 *                              it contains generated lines.
 * param[in]      ecrCtx       ECR context with data
 * result PRINTOUT_OK if printout generation was completed without problems, error code otherwise
 */
DLL_PUBLIC pr_Result pr_finishFiscalDccAnalysis(PrintoutCtx* ctx, EcrCtx* ecrCtx);

/**
 * Start fiscal printout with closing report. Report data will be extracted
 * form ecrCtx. This function should be called before first report entry is retrieved from the terminal.
 *
 * param[in,out]  ctx          Printout context. As input it carries library configuration, as output
 *                              it contains generated lines. All data except library configuration
 *                              is cleared at the beginning, there is no need to cleanup it between printouts.
 * param[in]      ecrCtx       ECR context with terminal data (result of ecr_readTerminalInformationData function).
 * result PRINTOUT_OK if printout generation was completed without problems, error code otherwise
 */
DLL_PUBLIC pr_Result pr_startFiscalClosingDay(PrintoutCtx* ctx, EcrCtx* ecrCtx);

/**
 * Add report entry. Data will be extracted form ecrCtx.
 * This function should be called after each report entry is retrieved from the terminal.
 *
 * param[in,out]  ctx          Printout context. As input it carries library configuration, as output
 *                              it contains generated lines. Context should be previously set up with
 *                              pr_startFiscalClosingDay function
 * param[in]      ecrCtx       ECR context with report entry
 * result PRINTOUT_OK if printout generation was completed without problems, error code otherwise
 */
DLL_PUBLIC pr_Result pr_addFiscalClosingDayTransaction(PrintoutCtx* ctx, EcrCtx* ecrCtx);

/**
 * Finish fiscal printout with closing day report. Data will be extracted form ecrCtx.
 * This function should be called after last report entry is added with pr_addFiscalClosingDayTransaction.
 *
 * param[in,out]  ctx          Printout context. As input it carries library configuration, as output
 *                              it contains generated lines.
 * param[in]      ecrCtx       ECR context with data
 * result PRINTOUT_OK if printout generation was completed without problems, error code otherwise
 */
DLL_PUBLIC pr_Result pr_finishFiscalClosingDay(PrintoutCtx* ctx, EcrCtx* ecrCtx);
//////////////////////////////////////////

/**
 * Extract number of generated printout lines.
 *
 * param[in]   ctx    Printout context with generated lines.
 * result Number of generated lines
 */
DLL_PUBLIC uint32_t pr_getNumberOfLines(PrintoutCtx* ctx);

/**
 * Get next printout line, starting from top.
 *
 * param[in, out]   ctx    Printout context with generated lines and extracted lines counter
 * param[out]       line   Printout line with formatting indicators
 * result PRINTOUT_OK if line was extracted, PRINTOUT_NO_MORE_LINES if all lines were extracted, error code otherwise
 */
DLL_PUBLIC pr_Result pr_getNextLine(PrintoutCtx* ctx, pr_Line* line);

/**
 * Get eVoucher logo filename. Useful only for eVoucher printouts
 *
 * param[in, out]   ctx    Printout context with generated lines and extracted lines counter
 * param[out]       filename  buffer for eVoucher logo filename
 * param[out]       filenameSize  buffer size
 * result PRINTOUT_OK
 */
DLL_PUBLIC pr_Result pr_getEvoucherLogo(PrintoutCtx* ctx, char* filename, size_t filenameSize);

/**
 * Get eVoucher barcode. Useful only for eVoucher printouts
 *
 * param[in, out]   ctx    Printout context with generated lines and extracted lines counter
 * param[out]       barcode  buffer for eVoucher barcode
 * param[out]       barcodeSize  buffer size
 * result PRINTOUT_OK
 */
DLL_PUBLIC pr_Result pr_getEvoucherBarcode(PrintoutCtx* ctx, char* barcode, size_t barcodeSize);

/**
 * Get eVoucher QR code. Useful only for eVoucher printouts
 *
 * param[in, out]   ctx    Printout context with generated lines and extracted lines counter
 * param[out]       qrcode  buffer for eVoucher QR code
 * param[out]       qrcodeSize  buffer size
 * result PRINTOUT_OK
 */
DLL_PUBLIC pr_Result pr_getEvoucherQrcode(PrintoutCtx* ctx, char* qrcode, size_t qrcodeSize);

#ifdef __cplusplus
}
#endif

#endif /* SRC_LIB_API_PRINTOUTS_H_ */
