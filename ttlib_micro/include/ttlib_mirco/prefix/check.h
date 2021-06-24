/*
 * @Copyright (C) 2019-2021, TTLIB
 * @file       check.h
 * @ingroup    prefix
 * @author     tango
 * @date       2020-11-19 
 * @brief      check.h file
 */

#ifndef _PREFIC_CHECK_H_
#define _PREFIC_CHECK_H_

/* //////////////////////////////////////////////////////////////////////////////////////
 * includes
 */
#include "abort.h"

__tt_extern_c_enter__

/* //////////////////////////////////////////////////////////////////////////////////////
* macros
*/

// check
#define tt_check_return(x)                              do { if (!(x)) return ; } while (0)
#define tt_check_return_val(x, v)                       do { if (!(x)) return (v); } while (0)
#define tt_check_goto(x, b)                             do { if (!(x)) goto b; } while (0)
#define tt_check_break(x)                               { if (!(x)) break ; }
#define tt_check_abort(x)                               do { if (!(x)) tt_abort(); } while (0)
#define tt_check_continue(x)                            { if (!(x)) continue ; }
#define tt_check_break_state(x, s, v)                   { if (!(x)) { (s) = (v); break ;} }

__tt_extern_c_leave__

#endif