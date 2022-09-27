/* Copyright (C) 2017 by eService
 *
 * All rights reserved.  No part of this software may be reproduced,
 * transmitted, transcribed, stored in a retrieval system, or translated
 * into any language or computer language, in any form or by any means,
 * electronic, mechanical, magnetic, optical, chemical, manual or otherwise,
 * without the prior written permission of eService.
 */
/*
 * dll_macro.h
 *
 *  Created on: 4 sty 2017
 *      Author: g.wachowicz
 */

#ifndef DLL_MACRO_H_
#define DLL_MACRO_H_

#ifdef STATIC
    #define DLL_PUBLIC
#else
  #if defined _WIN32 || defined __CYGWIN__
    #ifdef BUILDING_DLL
      #ifdef __GNUC__
        #define DLL_PUBLIC __attribute__ ((dllexport))
      #else
        #define DLL_PUBLIC __declspec(dllexport)
      #endif
    #else
      #ifdef __GNUC__
        #define DLL_PUBLIC __attribute__ ((dllimport))
      #else
        #define DLL_PUBLIC __declspec(dllimport)
      #endif
    #endif
    #define DLL_LOCAL
  #else
    #if __GNUC__ >= 4
      #define DLL_PUBLIC __attribute__ ((visibility ("default")))
      #define DLL_LOCAL  __attribute__ ((visibility ("hidden")))
    #else
      #define DLL_PUBLIC
      #define DLL_LOCAL
    #endif
  #endif
#endif

#endif /* DLL_MACRO_H_ */
