/*
 * @Copyright (C) 2019-2021, TTLIB
 * @file       trace.h
 * @ingroup    utils
 * @author     tango
 * @date       2020-11-19 
 * @brief      trace.h file
 */

#ifndef _TT_UTILS_TRACE_H_
#define _TT_UTILS_TRACE_H_

/* //////////////////////////////////////////////////////////////////////////////////////
 * includes
 */
#include "prefix.h"

__tt_extern_c_enter__

/* //////////////////////////////////////////////////////////////////////////////////////
* types
*/

/// trace mode
typedef enum __tt_trace_mode_e
{
	TT_TRACE_MODE_NONE  = 0,
	TT_TRACE_MODE_FILE  = 1,
	TT_TRACE_MODE_BUFF  = 2,
	TT_TRACE_MODE_PRINT = 3,
	TT_TRACE_MODE_UART  = 4

}tt_trace_mode_e;

/* //////////////////////////////////////////////////////////////////////////////////////
* interfaces
*/
extern tt_void_t tt_trace_done(tt_char_t const* prefix, tt_char_t const* module, tt_char_t const* format, ...);
extern tt_bool_t tt_trace_init(tt_void_t);
extern tt_bool_t tt_trace_exit(tt_void_t);

__tt_extern_c_leave__

#endif