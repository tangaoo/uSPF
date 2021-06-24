/*
 * @Copyright (C) 2019-2021, TTLIB
 * @file       assert.h
 * @ingroup    prefix
 * @author     tango
 * @date       2020-11-19 
 * @brief      assert.h file
 */

#ifndef _TT_ASSERT_H_
#define _TT_ASSERT_H_

/* //////////////////////////////////////////////////////////////////////////////////////
 * includes
 */
#include "abort.h"
#include "config.h"
#include "trace.h"

__tt_extern_c_enter__

/* //////////////////////////////////////////////////////////////////////////////////////
 * macros
 */
#if defined(__tt_debug__)
#	define tt_assert(x)                                               do { if(!(!!(x))) {tt_trace_d("expr [%s], %s(), %d, %s", #x __tt_debug_val__); tt_abort_done();} }while(0)
#   define tt_assert_and_check_abort(x)                               do {tt_assert(x); tt_check_abort(x); } while(0)
#   define tt_assert_and_check_return(x)                              do {tt_assert(x); tt_check_return(x); } while(0)
#   define tt_assert_and_check_return_val(x, v)                       do {tt_assert(x); tt_check_return_val(x, v); } while(0)
#   define tt_assert_and_check_goto(x, b)                             do {tt_assert(x); tt_check_goto(x, b); } while(0)
#   define tt_assert_and_check_break(x)                               do {tt_assert(x); tt_check_break(x); } while(0)
#   define tt_assert_and_check_continue(x)                            do {tt_assert(x); tt_check_continue(x); } while(0)
#   define tt_assert_and_check_break_state(x, s, v)                   do {tt_assert(x); tt_check_break_state(x, s, v); } while(0)
#else
#	define tt_assert(x)
#   define tt_assert_and_check_abort(x)                               tt_check_abort(x)
#   define tt_assert_and_check_return(x)                              tt_check_return(x)
#   define tt_assert_and_check_return_val(x, v)                       tt_check_return_val(x, v)
#   define tt_assert_and_check_goto(x, b)                             tt_check_goto(x, b)
#   define tt_assert_and_check_break(x)                               tt_check_break(x)
#   define tt_assert_and_check_continue(x)                            tt_check_continue(x)
#   define tt_assert_and_check_break_state(x, s, v)                   tt_check_break_state(x, s, v)
#endif

#if defined(__tt_debug__)
#   define tt_assertf(x, fmt, ...)                                    do { if (!(x)) { tt_tracef_d("expr [%s], %s(), %d, %s: " fmt, #x __tt_debug_val__, __VA_ARGS__); tt_abort_done(); } } while(0) 
#   define tt_assertf_and_check_return(x, fmt, ...)                   do {tt_assertf(x, fmt, __VA_ARGS__); tt_check_return(x);} while(0)
#   define tt_assertf_and_check_return_val(x, v, fmt, ...)            do {tt_assertf(x, fmt, __VA_ARGS__); tt_check_return_val(x, v);} while(0)
#   define tt_assertf_and_check_goto(x, b, fmt, ...)                  do {tt_assertf(x, fmt, __VA_ARGS__); tt_check_goto(x, b);} while(0)
#   define tt_assertf_and_check_break(x, fmt, ...)                    do {tt_assertf(x, fmt, __VA_ARGS__); tt_check_break(x);} while(0)
#   define tt_assertf_and_check_continue(x, fmt, ...)                 do {tt_assertf(x, fmt, __VA_ARGS__); tt_check_continue(x);} while(0)
#else
#   define tb_assertf(x, fmt, ...)                                      
#   define tb_assertf_and_check_return(x, fmt, ...)                   tt_check_return(x)  
#   define tb_assertf_and_check_return_val(x, v, fmt, ...)            tt_check_return_val(x, v)  
#   define tb_assertf_and_check_goto(x, b, fmt, ...)                  tt_check_goto(x, b)  
#   define tb_assertf_and_check_break(x, fmt, ...)                    tt_check_break(x)  
#   define tb_assertf_and_check_continue(x, fmt, ...)                 tt_check_continue(x)            
#endif


__tt_extern_c_leave__

#endif