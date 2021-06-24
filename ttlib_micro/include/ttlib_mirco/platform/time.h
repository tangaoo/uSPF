/*!The TT Library
 *
 * @Copyright (C) 2019-2021, TTLIB
 *
 * @file       time.h
 * @ingroup    platform
 * @author     tango
 * @date       2021-03-03 
 * @brief      time.h file
 */

#ifndef TT_PLATFORM_TIME_H
#define TT_PLATFORM_TIME_H

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

/*! usleep
 *
 * @param us            the microsecond time
 *
 * @return              tt_void
 */
tt_void_t               tt_usleep(tt_size_t us);

/*! msleep
 *
 * @param ms            the millisecond time
 *
 * @return              tt_void
 */
tt_void_t               tt_msleep(tt_size_t ms);

/*! sleep
 *
 * @param s             the second time
 *
 * @return              tt_void
 */
tt_void_t               tt_sleep(tt_size_t s);

/*! clock time, us
 *
 * @return              the clock time (us)
 */
tt_hong_t               tt_uclock(tt_void_t);

/*! clock time, ms
 *
 * @return              the clock time (ms)
 */
tt_hong_t               tt_mclock(tt_void_t);

/*! get time from 1970-01-01 00:00:00:000
 *
 * @param tv            the timeval
 * @param tz            the timezone
 *
 * @return              tt_true or tt_false 
 */
tt_bool_t               tt_gettimeofday(tt_timeval_t* tv, tt_timezone_t* tz);


/* //////////////////////////////////////////////////////////////////////////////////////
 * extern
 */
__tt_extern_c_leave__

#endif