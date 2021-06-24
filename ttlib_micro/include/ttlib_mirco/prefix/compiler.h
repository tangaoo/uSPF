/*!The TT Library
 *
 * @Copyright (C) 2019-2021, TTLIB
 *
 * @file       complier.h
 * @ingroup    prefix
 * @author     tango
 * @date       2020-12-17 
 * @brief      complier.h file
 */

#ifndef TT_PREFIX_COMPLIER_H
#define TT_PREFIX_COMPLIER_H


// gnu c/c++
#if defined(__GNUC__)
#   define TT_COMPILER_IS_GCC
// clang
#elif defined(__clang__)
#   define TT_COMPILER_IS_CLANG
// visual c++
#elif defined(_MSC_VER)
#   define TT_COMPILER_IS_MSVC
// c6000 dsp
#elif defined(_TMS320C6X) 
#   define TT_COMPILER_IS_DSP
// unkonwn
#else
#   define TT_COMPILER_IS_UNKONWN
#endif


#endif
