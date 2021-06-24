/*
 * @Copyright (C) 2019-2021, TTLIB
 * @file       native_memcpy.h
 * @ingroup    platform
 * @author     tango
 * @date       2020-11-19 
 * @brief      native_memcpy.h file
 */

#ifndef TT_NATIVE_MEMCPY_H
#define TT_NATIVE_MEMCPY_H

/* //////////////////////////////////////////////////////////////////////////////////////
 * includes
 */
#include "prefix.h"

/* //////////////////////////////////////////////////////////////////////////////////////
 * extern
 */
__tt_extern_c_enter__

/*! memcpy
 */
tt_void_t                 tt_memcpy(tt_pointer_t dst, tt_cpointer_t src, tt_size_t size);

/*! memcpy safe then dst buffer and src buffer overlay
 */
tt_void_t                 tt_memmov(tt_pointer_t dst, tt_pointer_t src, tt_size_t size);

/*! memset
 */
tt_void_t                 tt_memset(tt_pointer_t dst, tt_int32_t ch, tt_size_t size);


/* //////////////////////////////////////////////////////////////////////////////////////
 * extern
 */
__tt_extern_c_leave__

#endif