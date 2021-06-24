/*
 * @Copyright (C) 2019-2021, TTLIB
 * @file       circular_buffer.h
 * @ingroup    buffer
 * @author     tango
 * @date       2020-11-19 
 * @brief      circular_buffer.h file
 */

#ifndef TT_BUFFER_CIRCULAR_BUFFER_H
#define TT_BUFFER_CIRCULAR_BUFFER_H

/*//////////////////////////////////////////////////////////////////////////////////////
 * includes
 */
#include "prefix.h"

/* //////////////////////////////////////////////////////////////////////////////////////
 * extern
 */
__tt_extern_c_enter__

/* //////////////////////////////////////////////////////////////////////////////////////
 * type
 */
typedef struct __tt_circular_buffer_t
{
	tt_uint64_t r_idx;
	tt_uint64_t w_idx;
	tt_size_t   size;
	tt_byte_t   *data;

}tt_circular_buffer_t, *tt_circular_buffer_ref_t;

/* //////////////////////////////////////////////////////////////////////////////////////
 * interfaces
 */

/*! circular buffer init
 *
 * @param buffer
 * @param data,      user real buffer start addr
 * @param size,      real buffer size
 */
tt_bool_t            tt_circular_buffer_init(tt_circular_buffer_ref_t buff, tt_byte_t *data, tt_size_t size);

/*! circular buffer exit
 *
 * @param buffer
 */
tt_bool_t            tt_circular_buffer_exit(tt_circular_buffer_ref_t buff);

/*! circular buffer read
 *
 * @param buffer
 * @param out,       user real buff for read
 * @param size,      size of user real buff
 * @return           size of user have read
 */
tt_uint64_t          tt_circular_buffer_read(tt_circular_buffer_ref_t buff, tt_byte_t *out, tt_size_t size);

/*! circular buffer writ, not cover if full
*
* @param buffer
* @param in,         user real buff for write
* @param size,       size of user write buff
* @return            size of user have write
*/
tt_uint64_t          tt_circular_buffer_writ(tt_circular_buffer_ref_t buff, tt_byte_t *in, tt_size_t size);

/*! circular buffer writ, covered if full
*
* @param buffer
* @param in,         user real buff for write
* @param size,       size of user write buff
* @return            size of user have write
*/
tt_uint64_t          tt_circular_buffer_writ_cover(tt_circular_buffer_ref_t buff, tt_byte_t *in, tt_size_t size);

/* //////////////////////////////////////////////////////////////////////////////////////
 * extern
 */
__tt_extern_c_leave__

#endif