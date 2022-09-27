// Copyright (C) 2017 by eService, Ltd.
//
// All rights reserved.  No part of this software may be reproduced,
// transmitted, transcribed, stored in a retrieval system, or translated
// into any language or computer language, in any form or by any means,
// electronic, mechanical, magnetic, optical, chemical, manual or otherwise,
// without the prior written permission of eService, Ltd.

/// file
/// author g.wachowicz
/// brief

#ifndef SRC_LIB_API_PRINTOUTSTRUCTURES_H_
#define SRC_LIB_API_PRINTOUTSTRUCTURES_H_

#include "enumerations.h"

#include <stdint.h>

// Buffer size for generated printout line.
#define MAX_LINE_LEN 64

/**
 * Structure describing single printout line
 */
typedef struct
{
    uint32_t lineNumber;           // Line number on non-fiscal printout or field ID on fiscal printout
    char text[MAX_LINE_LEN + 1];   // Text to print, padded with spaces for non-fiscal printout
    pr_Size size;                  // Font size
    pr_Background background;      // Standard background or inverted colors
    pr_LineType lineType;          // Textual or graphical line
    pr_PictureType picType;        // For graphical lines, picture ID
    pr_FontType fontType;          // Font formatting, default or bold
} pr_Line;

/**
 * Fiscal format field properties
 */
typedef struct
{
    uint32_t lineId;     // Format field ID
    uint32_t lineLen;    // Format field size
} pr_FiscalFormatLine;

#endif /* SRC_LIB_API_PRINTOUTSTRUCTURES_H_ */
