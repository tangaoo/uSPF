/*!The TT Library
 *
 * @Copyright (C) 2019-2021, TTLIB
 *
 * @file       find_if.h
 * @ingroup    algorithm
 * @author     tango
 * @date       2020-12-11 
 * @brief      find_if.h file
 */

#ifndef TT_ALGORITHM_FIND_IF_H
#define TT_ALGORITHM_FIND_IF_H

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

/*! find the item if pred
 *
 * @param iterator     the iterator 
 * @param head         the head 
 * @param tail         the tail 
 * @param pred         the pred 
 * @param data         the data 
 *
 * @return             tt_true or tt_false
 */
tt_size_t              tt_find_if(tt_iterator_ref_t iterator, tt_size_t head, tt_size_t tail, tt_predicate_func_t pred, tt_cpointer_t data);


/*! find the all item if pred
 *
 * @param iterator     the iterator 
 * @param pred         the pred 
 * @param data         the data 
 *
 * @return             tt_true or tt_false
 */
tt_size_t              tt_find_all_if(tt_iterator_ref_t iterator, tt_predicate_func_t pred, tt_cpointer_t data);

/* //////////////////////////////////////////////////////////////////////////////////////
 * extern
 */
__tt_extern_c_leave__

#endif
