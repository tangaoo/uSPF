/*!The TT Library
 *
 * @Copyright (C) 2019-2021, TTLIB
 *
 * @file       thread.h
 * @ingroup    platform
 * @author     tango
 * @date       2021-03-20 
 * @brief      thread.h file
 */

/* //////////////////////////////////////////////////////////////////////////////////////
 * includes
 */
#include "prefix.h"

/* //////////////////////////////////////////////////////////////////////////////////////
 * extern
 */
__tt_extern_c_enter__

/* //////////////////////////////////////////////////////////////////////////////////////
 * types
 */

/*! the thread function type
 *
 * @param priv          the private data
 *
 * @return              return the value
 */
typedef tt_int_t        (*tt_thread_func_t)(tt_cpointer_t priv);

/* //////////////////////////////////////////////////////////////////////////////////////
 * interfaces
 */

/*! init thread
 *
 * @param name          thread name, may be null
 * @param func          thread function
 * @param priv          thread priv data
 * @param stack         thread priv stack, using the fault size if be zero
 *
 * @return              the thread handle
 */
tt_thread_ref_t         tt_thread_init(tt_char_t const* name, tt_thread_func_t func, tt_cpointer_t priv, tt_size_t stack);

/*! exit thread
 *
 * @param thread        the thread handle
 *
 * @return              tt_void_t
 */
tt_void_t               tt_thread_exit(tt_thread_ref_t thread);

/*! wait thread
 *
 * @param thread        the thread handle
 * @param timeout       the timeout
 * @param retval        the return value point of thread (optional)
 *
 * @return              1, ok;  0, timeout, -1, error
 */
tt_long_t               tt_thread_wait(tt_thread_ref_t thread, tt_long_t timeout, tt_int_t* retval);

/*! suspend thread
 *
 * @param thread        the thread
 *
 * @return              tt_true of tt_false
 */
tt_bool_t               tt_thread_suspend(tt_thread_ref_t thread);

/*! resume thread
 *
 * @param thread        the thread
 *
 * @return              tt_true or tt_false
 */
tt_bool_t               tt_thread_resume(tt_thread_ref_t thread);

/*! the self thread idtentifier
 *
 * @return              the self thread idtentifier
 */
tt_size_t               tt_thread_self(tt_void_t);

/*! return the thread value
 *
 * @param value         the value thread return
 *
 * @return              tt_void_t
 */
tt_void_t               tt_thread_return(tt_int_t value);



/* //////////////////////////////////////////////////////////////////////////////////////
 * extern
 */
__tt_extern_c_leave__