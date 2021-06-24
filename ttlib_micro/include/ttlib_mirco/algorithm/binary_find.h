/*!The TT Library
 *
 * @Copyright (C) 2019-2021, TTLIB
 *
 * @file       binary_find.h
 * @ingroup    algorithm
 * @author     tango
 * @date       2020-12-03 
 * @brief      binary_find.h file
 */

#ifndef TT_ALGORITHM_BINARY_FIND_H
#define TT_ALGORITHM_BINARY_FIND_H

/* //////////////////////////////////////////////////////////////////////////////////////
 * includes
 */
#include "prefix.h"
#include "../container/iterator.h"

/* //////////////////////////////////////////////////////////////////////////////////////
 * extern
 */
__tt_extern_c_enter__

/* //////////////////////////////////////////////////////////////////////////////////////
 * interfaces
 */

/*! the binary find
 *
 * @param iterator      the iterator 
 * @param head          the head 
 * @param tail          the tail 
 * @param item          the item 
 *
 * @return              tt_void_t
 */
tt_size_t               tt_binary_find(tt_iterator_ref_t iterator, tt_size_t head, tt_size_t tail, tt_cpointer_t item);

/*! the binary find all 
 *
 * @param iterator      the iterator
 * @param item          the item 
 *
 * @return              tt_void_t
 */
tt_size_t               tt_binary_find_all(tt_iterator_ref_t iterator, tt_cpointer_t item);

/* //////////////////////////////////////////////////////////////////////////////////////
 * extern
 */
__tt_extern_c_leave__

#endif