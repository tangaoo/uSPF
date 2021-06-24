/*
 * @Copyright (C) 2019-2021, TTLIB
 * @file       keyword.h
 * @ingroup    prefix
 * @author     tango
 * @date       2020-11-19 
 * @brief      keyword.h file
 */

#ifndef TT_PREFIX_KEYWORD_H
#define TT_PREFIX_KEYWORD_H

/*//////////////////////////////////////////////////////////////////////////////////////
* includes 
*/
#include "config.h"

//extern c
#ifdef __cplusplus
#   define __tt_extern_c__                            extern "C"
#	define __tt_extern_c_enter__                      extern "C" {
#	define __tt_extern_c_leave__                      }
#else
#   define __tt_extern_c__
#	define __tt_extern_c_enter__                        
#	define __tt_extern_c_leave__
#endif

#define __tt_volatile__	                              volatile
#define __tt_func__                                   __FUNCTION__
#define __tt_file__                                   __FILE__
#define __tt_line__                                   __LINE__
#define __tt_new_line__                               "\n"

#if __tt_debug__
#	define __tt_debug_decl__                          , tt_char_t const* func_, tt_uint32_t line_, tt_char_t const* file_
#	define __tt_debug_args__                          , func_, line_, file_
#	define __tt_debug_val__                           , __tt_func__, __tt_line__, __tt_file__
#else
#	define __tt_debug_decl__                          
#	define __tt_debug_args__                          
#	define __tt_debug_val__ 
#endif

#if defined(TT_COMPILER_IS_GCC)
#   define __tt_inline__                        __inline__
#   define __tt_aligned__(a)                    __attribute__((aligned(a)))
#elif defined(TT_COMPILER_IS_MSVC)
#   define __tt_inline__                        __inline
#   define __tt_aligned__(a)                    __declspec(align(a))
#endif

/// dummy typdef
#define __tt_typeref__(object)          struct __tt_##object##_dummy_t{tt_int_t dummy;} const* tt_##object##_ref_t

#endif