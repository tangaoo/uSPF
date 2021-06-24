/*!The TT Library
 *
 * @Copyright (C) 2019-2021, TTLIB
 *
 * @file       predicate.h
 * @ingroup    algorithm
 * @author     tango
 * @date       2020-12-11 
 * @brief      predicate.h file
 */

#ifndef TT_ALGORITHM_PREDICATE_H
#define TT_ALGORITHM_PREDICATE_H

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
 * types
 */

/*! the predicate ref type
 *
 * @param iterator      the iterator 
 * @param item          the item in container 
 * @param data          the data outside
 *
 * @return              tt_void_t
 */
typedef tt_bool_t       (*tt_predicate_func_t)(tt_iterator_ref_t iterator, tt_cpointer_t item, tt_cpointer_t data);

/* //////////////////////////////////////////////////////////////////////////////////////
 * interfaces
 */

/*! predicate item == data? 
 *
 * @param iterator      the iterator 
 * @param item          the item in container 
 * @param data          the data outside
 *
 * @return              tt_void_t
 */
tt_bool_t               tt_predicate_eq(tt_iterator_ref_t iterator, tt_cpointer_t item, tt_cpointer_t data);

/*! predicate item > data? 
 *
 * @param iterator      the iterator 
 * @param item          the item in container 
 * @param data          the data outside
 *
 * @return              tt_void_t
 */
tt_bool_t               tt_predicate_bq(tt_iterator_ref_t iterator, tt_cpointer_t item, tt_cpointer_t data);

/*! predicate item < data? 
 *
 * @param iterator      the iterator 
 * @param item          the item in container 
 * @param data          the data outside
 *
 * @return              tt_void_t
 */
tt_bool_t               tt_predicate_lq(tt_iterator_ref_t iterator, tt_cpointer_t item, tt_cpointer_t data);

/*! predicate item >= data? 
 *
 * @param iterator      the iterator 
 * @param item          the item in container 
 * @param data          the data outside
 *
 * @return              tt_void_t
 */
tt_bool_t               tt_predicate_beq(tt_iterator_ref_t iterator, tt_cpointer_t item, tt_cpointer_t data);

/*! predicate item <= data? 
 *
 * @param iterator      the iterator 
 * @param item          the item in container 
 * @param data          the data outside
 *
 * @return              tt_void_t
 */
tt_bool_t               tt_predicate_leq(tt_iterator_ref_t iterator, tt_cpointer_t item, tt_cpointer_t data);


/* //////////////////////////////////////////////////////////////////////////////////////
 * extern
 */
__tt_extern_c_leave__

#endif

