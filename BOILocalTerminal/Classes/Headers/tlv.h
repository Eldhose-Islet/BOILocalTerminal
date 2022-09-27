/* Copyright (C) 2017 by eService
 *
 * All rights reserved.  No part of this software may be reproduced,
 * transmitted, transcribed, stored in a retrieval system, or translated
 * into any language or computer language, in any form or by any means,
 * electronic, mechanical, magnetic, optical, chemical, manual or otherwise,
 * without the prior written permission of eService.
 */
/*
 * tlv.h
 *
 *  Created on: 5 sty 2017
 *      Author: przemyslaw.ogorzalek
 */

#ifndef TLV_H_
#define TLV_H_

#include "tags.h"
#include "dll_macro.h"

#define __STDC_FORMAT_MACROS
#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum
{
    TLV_RESULT_OK,
    TLV_RESULT_INVALID,
    TLV_RESULT_MISSING,
    TLV_RESULT_ALREADY_PRESENT,
    TLV_RESULT_CORRUPTED,
    TLV_RESULT_BUFFER_OVERFLOW
} TlvResult;

struct TlvStore_s;
typedef struct TlvStore_s TlvStore;

/**
 * Initialize TLV store.
 */
DLL_PUBLIC void tlv_init(TlvStore** store);

/**
 * Release all resources and delete TLV store.
 */
DLL_PUBLIC void tlv_clean(TlvStore** store);

/**
 * Add tag to store. If present, error "TLV_RESULT_ALREADY_PRESENT" shall be returned,
 * and value will not be overwritten
 */
DLL_PUBLIC TlvResult addTag(TlvStore* store, TlvTag tag, const uint8_t* value, size_t len);

/**
 * Add string tag to store. If present, error "TLV_RESULT_ALREADY_PRESENT" shall be returned,
 * and value will not be overwritten
 */
DLL_PUBLIC TlvResult addTagStr(TlvStore* store, TlvTag tag, const char* value);

/**
 * Add tag to store. If present, value will be overwritten
 */
DLL_PUBLIC TlvResult forceAddTag(TlvStore* store, TlvTag tag, const uint8_t* value, size_t len);

/**
 * Overwrite tag's value. If not present, "TLV_RESULT_MISSING" will be returned and tag will not be added
 */
DLL_PUBLIC TlvResult replaceTag(TlvStore* store, TlvTag tag, const uint8_t* value, size_t len);

/**
 * Get tag value. If not present, "TLV_RESULT_MISSING" will be returned
 */
DLL_PUBLIC TlvResult readTag(TlvStore* store, TlvTag tag, uint8_t* value, size_t* len);

/**
 * Get string tag value. If not present, "TLV_RESULT_MISSING" will be returned
 */
DLL_PUBLIC TlvResult readTagStr(TlvStore* store, TlvTag tag, char* value, size_t value_size);

/**
 * Remove tag from the store. If missing, "TLV_RESULT_OK" will be returned anyway,
 * since in the end the end the tag is not in store either way
 */
DLL_PUBLIC TlvResult removeTag(TlvStore* store, TlvTag tag);

/**
 * Check if tag is present in store. "TLV_RESULT_OK" if found, "TLV_RESULT_MISSING" otherwise
 */
DLL_PUBLIC TlvResult findTag(TlvStore* store, TlvTag tag);

/**
 * Clear the store and set new TLV buffer
 */
DLL_PUBLIC TlvResult setBuffer(TlvStore* store, const uint8_t* buffer, size_t len);

/**
 * Add whole list of TLVs to the store, existing tags will not be overwritten
 */
DLL_PUBLIC TlvResult addBuffer(TlvStore* store, const uint8_t* buffer, size_t len);

/**
 * Add whole list of TLVs to the store, existing tags will be overwritten
 */
DLL_PUBLIC TlvResult forceAddBuffer(TlvStore* store, const uint8_t* buffer, size_t len);

/**
 * Get all TLVs from the store
 */
DLL_PUBLIC TlvResult readBuffer(TlvStore* store, uint8_t* buffer, size_t* len);

/**
 * Remove all tags from the store
 */
DLL_PUBLIC TlvResult clearStore(TlvStore* store);

#ifdef __cplusplus
}
#endif
#endif /* TLV_H_ */
