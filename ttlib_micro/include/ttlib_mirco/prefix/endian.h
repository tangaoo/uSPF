/*!The TT Library
 *
 * @Copyright (C) 2019-2021, TTLIB
 *
 * @file       endian.h
 * @ingroup    prefix
 * @author     tango
 * @date       2021-03-02 
 * @brief      endian.h file
 */

#ifndef TT_PREFIX_ENDIAN_H
#define TT_PREFIX_ENDIAN_H

/* //////////////////////////////////////////////////////////////////////////////////////
 * includes
 */
#include "config.h"

/* //////////////////////////////////////////////////////////////////////////////////////
 * macros
 */

// words endian
#ifdef __BYTE_ORDER__
#   if __BYTE_ORDER__ != __ORDER_LITTLE_ENDIAN__
#       define TT_WORDS_BIGENDIAN
#   endif
#endif
#if defined(MIPSEB) || defined(_MIPSEB) || defined(__MIPSEB__)
#   define TT_WORDS_BIGENDIAN
#endif

// float endian
#ifdef __FLOAT_WORD_ORDER__
#   if __FLOAT_WORD_ORDER__ != __ORDER_LITTLE_ENDIAN__
#       define TT_FLOAT_BIGENDIAN
#   endif
#endif


#endif
