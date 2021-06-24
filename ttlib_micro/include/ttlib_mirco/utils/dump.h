/*
 * @Copyright (C) 2019-2021, TTLIB
 * @file       dump.h
 * @ingroup    utils
 * @author     tango
 * @date       2020-11 
 * @brief      dump.h file
 */

#ifndef TT_UTILS_DUMP_H
#define TT_UTILS_DUMP_H

/* //////////////////////////////////////////////////////////////////////////////////////
 * includes
 */
#include "prefix.h"

/* //////////////////////////////////////////////////////////////////////////////////////
 * extern
 */
__tt_extern_c_enter__

/* //////////////////////////////////////////////////////////////////////////////////////
 * interfaces
 */

/*! dump the memory
 *
 * @param ptr             the memory addr 
 *
 * @param byte_cnt        counts of bytes 
 * 
 * @return                tt_void
 */
extern tt_void_t          tt_memory_dump(tt_pointer_t ptr, tt_size_t byte_cnt);


/* //////////////////////////////////////////////////////////////////////////////////////
 * extern
 */
__tt_extern_c_leave__

#endif