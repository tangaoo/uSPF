/*
 * @Copyright (C) 2019-2021, TTLIB
 * @file       mutex.h
 * @ingroup    platform
 * @author     tango
 * @date       2020-11-19 
 * @brief      mutex.h file
 */

#ifndef TT_PLATFORM_MUTEX_H
#define TT_PLATFORM_MUTEX_H

/* //////////////////////////////////////////////////////////////////////////////////////
 * includes
 */
#include "prefix.h"

#define  TT_POSIX             1
#define  TT_POSIX_NO          0

#if defined(TT_POSIX) && TT_POSIX
#   include "pthread.h"
typedef pthread_mutex_t    tt_mutex_t;
typedef pthread_mutex_t*   tt_mutex_ref_t;

#elif defined(TT_POSIX_NO) && TT_POSIX_NO
typedef tt_int32_t         tt_mutex_t;
typedef tt_int32_t*        tt_mutex_ref_t;

#endif

/* //////////////////////////////////////////////////////////////////////////////////////
 * extern
 */
__tt_extern_c_enter__

/* //////////////////////////////////////////////////////////////////////////////////////
 * interfaces
 */

/*! init mutex(alloc mutex outside)
 *
 * @param mutex             the mutex
 *
 * @return                  the mutex or tt_null
 */
tt_mutex_t*                 tt_mutex_init_impl(tt_mutex_t * mutex);

/*! exit mutex
 *
 * @param mutex             the mutex
 *
 * @return                  void
 */
tt_void_t                   tt_mutex_exit_impl(tt_mutex_t * mutex);

/*! int mutex(dynamic malloc inside)
 *
 * @return                  the mutex
 */
tt_mutex_ref_t              tt_mutex_init(tt_void_t);

/*! exit mutex
 *
 * @param mutex             the mutex
 *
 * @return                  void
 */
tt_void_t                   tt_mutex_exit(tt_mutex_ref_t mutex);

/*! entry mutex
 *
 * @param mutex             the mutex
 *
 * @return                  tt_true or tt_false
 */
tt_bool_t                   tt_mutex_entry(tt_mutex_ref_t mutex);

/*! try entry mutex
 *
 * @param mutex             the mutex
 *
 * @return                  tt_true or tt_false
 */
tt_bool_t                   tt_mutex_entry_try(tt_mutex_ref_t mutex);

/*! leave mutex
 *
 * @param mutex             the mutex
 *
 * @return                  tt_true or tt_false
 */
tt_bool_t                   tt_mutex_leave(tt_mutex_ref_t mutex);


/* //////////////////////////////////////////////////////////////////////////////////////
 * extern
 */
__tt_extern_c_leave__

#endif