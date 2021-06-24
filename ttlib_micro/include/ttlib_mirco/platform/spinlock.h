/*
 * @Copyright (C) 2019-2021, TTLIB
 * @file       spinlock.h
 * @ingroup    platform
 * @author     tango
 * @date       2020-11-19 
 * @brief      spinlock.h file
 */

#ifndef TT_PLATFORM_SPINLOCK_H
#define TT_PLATFORM_SPINLOCK_H

/* //////////////////////////////////////////////////////////////////////////////////////
 * includes
 */
#include "prefix.h"
#include "mutex.h"

/* //////////////////////////////////////////////////////////////////////////////////////
 * type
 */
typedef tt_mutex_t             tt_spinlock_t;
typedef tt_mutex_ref_t         tt_spinlock_ref_t;

/* //////////////////////////////////////////////////////////////////////////////////////
 * extern
 */
__tt_extern_c_enter__

/*! init spinlock(alloc spinlock outside)
 *
 * @param  spinlock            the spinlock ref
 *
 * @return                     spinlock            
 */
tt_spinlock_t*                 tt_spinlock_init_impl(tt_spinlock_t * spinlock);

/*! exit spinlock
 *
 * @param spinlock             the spinlock             
 *
 * @return                     tt_void
 */
tt_void_t                      tt_spinlock_exit_impl(tt_spinlock_t * spinlock);

/*! init spinlock(dynamic malloc inside)
 *
 * @param spinlock             the spinlock
 *
 * @return                     the spinlock
 */
tt_spinlock_ref_t              tt_spinlock_init(tt_void_t);

/*! exit spinlock
 *
 * @param spinlock             the spinlock
 *
 * @return                     tt_void
 */
tt_void_t                      tt_spinlock_exit(tt_spinlock_ref_t spinlock);

/*! entry spinlock
 *
 * @param spinloc              the spinlock
 *
 * @return                     tt_true or tt_false
 */
tt_bool_t                      tt_spinlock_entry(tt_spinlock_ref_t spinlock);

/*! entry spinlock try
 *
 * @param spinloc              the spinlock
 *
 * @return                     tt_true or tt_false
 */
tt_bool_t                      tt_spinlock_entry_try(tt_spinlock_ref_t spinlock);

/*! leave spinlock
 *
 * @param spinloc              the spinlock
 *
 * @return                     tt_true or tt_false
 */
tt_bool_t                      tt_spinlock_leave(tt_spinlock_ref_t spinlock);


/* //////////////////////////////////////////////////////////////////////////////////////
 * extern
 */
__tt_extern_c_leave__

#endif