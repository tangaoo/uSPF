/*!The TT Library
 *
 * @Copyright (C) 2019-2021, TTLIB
 *
 * @file       semaphore.h
 * @ingroup    platform
 * @author     tango
 * @date       2021-03-03 
 * @brief      semaphore.h file
 */

#ifndef TT_PLATFORM_SEMAPHORE_H
#define TT_PLATFORM_SEMAPHORE_H

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

/*! init the semaphore
 *
 * @param value         the initial semaphore value 
 *
 * @return              the semaphore
 */
tt_semaphore_ref_t      tt_semaphore_init(tt_size_t value);

/*! exit the semaphore
 *
 * @param semaphore     the semaphore
 *
 * @return              tt_void
 */
tt_void_t               tt_semaphore_exit(tt_semaphore_ref_t semaphore);

/*! post the semaphore
 *
 * @param semaphore     the semaphore
 * @param post          the post semaphore value
 *
 * @return              tt_true or tt_false
 */
tt_bool_t               tt_semaphore_post(tt_semaphore_ref_t semaphore, tt_size_t post);

/*! get the semaphore value
 *
 * @param semaphore     the semaphore
 *
 * @return              >= 0: the semaphore value; -1: failed
 */
tt_size_t               tt_semaphore_value(tt_semaphore_ref_t semaphore);

#if 0
/*! wait the semaphore
 *
 * @param semaphore     the semaphore
 * @param timeout       the timeout (ms)
 *
 * @return              ok: 1; timeout or interrupted: 0, failed: -1
 */
tt_long_t               tt_semaphore_wait(tt_semaphore_ref_t semaphore, tt_long_t timeout);
#endif

/*! wait the semaphore
 *
 * @param semaphore     the semaphore
 *
 * @return              ok: 1; interrupted: 0, failed: -1
 */
tt_long_t               tt_semaphore_wait(tt_semaphore_ref_t semaphore);

/* //////////////////////////////////////////////////////////////////////////////////////
 * extern
 */
__tt_extern_c_leave__

#endif