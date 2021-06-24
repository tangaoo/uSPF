/*!The TT Library
 *
 * @Copyright (C) 2019-2021, TTLIB
 *
 * @file       find.h
 * @ingroup    algorithm
 * @author     tango
 * @date       2020-12-13 
 * @brief      find.h file
 */

#ifndef TT_ALGORITHM_FIND_H
#define TT_ALGORITHM_FIND_H

/* //////////////////////////////////////////////////////////////////////////////////////
 * includes
 */
#include "prefix.h"
#include "predicate.h"
#include "../container/iterator.h"

/* //////////////////////////////////////////////////////////////////////////////////////
 * extern
 */
__tt_extern_c_enter__

/* //////////////////////////////////////////////////////////////////////////////////////
 * interfaces
 */


/*! find the item
 *
 * @param iterator   the iterator
 * @param head       the head of container
 * @param tail       the tail of container
 * @param data       the data to find 
 *
 * @return           the itor of data, if not find return tail 
 */
tt_size_t            tt_find(tt_iterator_ref_t iterator, tt_size_t head, tt_size_t tail, tt_cpointer_t data);

/*! find the item all
 *
 * @param iterator   the iterator
 * @param data       the data to find 
 *
 * @return           the itor of data, if not find return tail 
 */
tt_size_t            tt_find_all(tt_iterator_ref_t iterator, tt_cpointer_t data);

/* //////////////////////////////////////////////////////////////////////////////////////
 * extern
 */
__tt_extern_c_leave__

#endif