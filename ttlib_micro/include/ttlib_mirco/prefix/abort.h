/*
 * @Copyright (C) 2019-2021, TTLIB
 * @file       abort.h
 * @ingroup    prefix
 * @author     tango
 * @date       2020-11-19 
 * @brief      abort.h file
 */

#ifndef _PREFIX_ABORT_H_
#define _PREFIX_ABORT_H_

/* //////////////////////////////////////////////////////////////////////////////////////
 * includes
 */
#include "keyword.h"
#include "type.h"
#include "trace.h"

__tt_extern_c_enter__

/* //////////////////////////////////////////////////////////////////////////////////////
 * macros
 */
#ifndef tt_abort_done
#	define tt_abort_done()                 do{ *((__tt_volatile__ tt_uint32_t*)0) = 0; }while(0)
#endif

#define tt_abort()                         do{ tt_trace_a("abort");tt_abort_done(); }while(0)

__tt_extern_c_leave__

#endif