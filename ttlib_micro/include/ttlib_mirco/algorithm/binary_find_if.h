/*!The TT Library
 *
 * @Copyright (C) 2019-2021, TTLIB
 *
 * @file       binary_find_if.h
 * @ingroup    algorithm
 * @author     tango
 * @date       2020-11-27 
 * @brief      binary_find_if.h file
 */

#ifndef TT_BINARY_FIND_IF_H
#define TT_BINARY_FIND_IF_H

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

/*!binary find item if !comp(item, priv), the items have beed sorted. 
 *
 * @param iterator          the iterator
 * @param head              the iterator head
 * @param tail              the iterator tail
 * @param comp              the iterator func
 * @param priv              the iterator data
 *
 * @return                  the iterator itor, return tt_iterator_tail(iterator) if not found
 */
tt_size_t                   tt_binary_find_if(tt_iterator_ref_t iterator, tt_size_t head, tt_size_t tail, tt_iterator_comp_t comp, tt_cpointer_t priv);

/*!binary find item if !comp(item, priv), the items have beed sorted. 
 *
 * @param iterator          the iterator
 * @param comp              the iterator func
 * @param priv              the iterator data
 *
 * @return                  the iterator itor, return tt_iterator_tail(iterator) if not found
 */
tt_size_t                   tt_binary_find_all_if(tt_iterator_ref_t iterator, tt_iterator_comp_t comp, tt_cpointer_t priv);

/* //////////////////////////////////////////////////////////////////////////////////////
 * extern
 */
__tt_extern_c_leave__

#endif