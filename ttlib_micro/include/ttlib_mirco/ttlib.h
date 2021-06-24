/*
 * @Copyright (C) 2019-2021, TTLIB
 * @file       ttlib.h
 * @ingroup    ttlib
 * @author     tango
 * @date       2020-11-19 
 * @brief      ttlib.h file
 */

#ifndef _TT_TTLIB_
#define _TT_TTLIB_

/* //////////////////////////////////////////////////////////////////////////////////////
 * includes
 */
#include "prefix/prefix.h"
#include "buffer/buffer.h"
#include "container/container.h"
#include "container/iterator.h"
#include "algorithm/algorithm.h"
#include "utils/utils.h"

/* //////////////////////////////////////////////////////////////////////////////////////
 * extern
 */
__tt_extern_c_enter__

/*! the ttlib init, must do before use
 *
 * @param allocator             the memory allocator
 * @param priv                  the private data
 *
 * @return              tt_void
 */
tt_bool_t tt_lib_init(tt_handle_t priv);

/*! the ttlib exit
 */
tt_void_t tt_lib_exit(tt_void_t);

/* //////////////////////////////////////////////////////////////////////////////////////
 * extern
 */
__tt_extern_c_leave__

#endif