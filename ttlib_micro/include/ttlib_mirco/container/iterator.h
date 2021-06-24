/*
 * @Copyright (C) 2019-2021, TTLIB
 * @file       iterator.h
 * @ingroup    container
 * @author     tango
 * @date       2020-11-19 
 * @brief      iterator.h file
 */

#ifndef TT_CONTAINER_ITERATOR_H
#define TT_CONTAINER_ITERATOR_H

/* //////////////////////////////////////////////////////////////////////////////////////
* includes
*/
#include "prefix.h"

/* //////////////////////////////////////////////////////////////////////////////////////
* extern
*/
__tt_extern_c_enter__

/* //////////////////////////////////////////////////////////////////////////////////////
* types
*/

typedef enum __tt_iterator_mode_t
{
	TT_ITERATOR_MODE_FORWARD   = 1   // forward iterator
,   TT_ITERATOR_MODE_REVERSE   = 2   // reverse iterator
,   TT_ITERATOR_MODE_RACCESS   = 4   // random access iterator
,   TT_ITERATOR_MODE_MUTABLE   = 8   // mutable iterator, the item of iterator is mutable for removing or moving, .e.g vector, hash...
,   TT_ITERATOR_MODE_READONLY  = 16  // read only iterator
}tt_iterator_mode_t;

/// the iterator operation type
struct __tt_iterator_t;

typedef struct __tt_iterator_op_t
{
	/// the iterator size
	tt_size_t                (*size)(struct __tt_iterator_t *iterator);

	/// the iterator head
	tt_size_t                (*head)(struct __tt_iterator_t *iterator);

	/// the iterator last
	tt_size_t                (*last)(struct __tt_iterator_t *iterator);

	/// the iterator tail 
	tt_size_t                (*tail)(struct __tt_iterator_t *iterator);

	/// the iterator prev
	tt_size_t                (*prev)(struct __tt_iterator_t *iterator, tt_size_t itor);

	/// the iterator next
	tt_size_t                (*next)(struct __tt_iterator_t *iterator, tt_size_t itor);

	/// the iterator item
	tt_pointer_t             (*item)(struct __tt_iterator_t *iterator, tt_size_t itor);

	/// the iterator comp
	tt_int32_t               (*comp)(struct __tt_iterator_t *iterator, tt_cpointer_t litem, tt_cpointer_t ritem);

	/// the iterator copy
	tt_void_t                (*copy)(struct __tt_iterator_t *iterator, tt_size_t itor, tt_cpointer_t item);

	/// the iterator remove
	tt_void_t                (*remove)(struct __tt_iterator_t *iterator, tt_size_t itor);

	/// the iterator nremove
	tt_void_t                (*nremove)(struct __tt_iterator_t *iterator, tt_size_t prev, tt_size_t next, tt_size_t size);

}tt_iterator_op_t;

/// the iterator operation ref type
typedef tt_iterator_op_t const* tt_iterator_op_ref_t;

/// the iterator type
typedef struct __tt_iterator_t
{
	/// the iterator mode
	tt_iterator_mode_t        mode;

	/// the iterator step
	tt_size_t                 step;

	/// the iterator priv
	tt_pointer_t              priv;

	/// the iterator op
	tt_iterator_op_ref_t      op;

}tt_iterator_t, *tt_iterator_ref_t;

// the iterator comp func type
typedef tt_long_t             (*tt_iterator_comp_t)(tt_iterator_ref_t iterator, tt_cpointer_t litem, tt_cpointer_t ritem);

/* //////////////////////////////////////////////////////////////////////////////////////
 * interfaces
 */

/*! the iterator mode
*
* @param iterator  the iterator
*
* @return          the iterator mode
*/
tt_size_t           tt_iterator_mode(tt_iterator_ref_t iterator);

/*! the iterator step
*
* @param iterator  the iterator
*
* @return          the iterator step
*/
tt_size_t           tt_iterator_step(tt_iterator_ref_t iterator);


/*! the iterator size
*
* @param iterator  the iterator
*
* @return          the iterator size
*/
tt_size_t           tt_iterator_size(tt_iterator_ref_t iterator);

/*! the iterator head
*
* @param iterator  the iterator
*
* @return          the iterator head
*/
tt_size_t           tt_iterator_head(tt_iterator_ref_t iterator);

/*! the iterator last
*
* @param iterator  the iterator
*
* @return          the iterator last
*/
tt_size_t           tt_iterator_last(tt_iterator_ref_t iterator);

/*! the iterator tail
*
* @param iterator  the iterator
*
* @return          the iterator tail
*/
tt_size_t           tt_iterator_tail(tt_iterator_ref_t iterator);

/*! the iterator prev
*
* @param iterator  the iterator
* @param itor      the item itor
*
* @return          the iterator prev
*/
tt_size_t           tt_iterator_prev(tt_iterator_ref_t iterator, tt_size_t itor);

/*! the iterator next
*
* @param iterator  the iterator
* @param itor      the item itor
*
* @return          the iterator next
*/
tt_size_t           tt_iterator_next(tt_iterator_ref_t iterator, tt_size_t itor);

/*! the iterator item
*
* @param iterator  the iterator
* @param itor      the item itor
*
* @return          the iterator item
*/
tt_pointer_t        tt_iterator_item(tt_iterator_ref_t iterator, tt_size_t itor);

/*! compare the iterator item
*
* @param iterator  the iterator
* @param litem     the item
* @param ritem     the compared item
*
* @return          =: 0, >: 1, <: -1
*/
tt_long_t          tt_iterator_comp(tt_iterator_ref_t iterator, tt_cpointer_t litem, tt_cpointer_t ritem);

/*! copy the iterator item
*
* @param iterator  the iterator
* @param itor      the item itor
* @param item      the copied item
*/
tt_void_t           tt_iterator_copy(tt_iterator_ref_t iterator, tt_size_t itor, tt_cpointer_t item);

/*! remove the iterator item
*
* @param iterator  the iterator
* @param itor      the item itor
*/
tt_void_t           tt_iterator_remove(tt_iterator_ref_t iterator, tt_size_t itor);

/*! remove the iterator items from range(prev, next)
*
* @param iterator  the iterator
* @param prev      the prev item
* @param next      the next item
* @param size      the removed size
*/
tt_void_t           tt_iterator_nremove(tt_iterator_ref_t iterator, tt_size_t prev, tt_size_t next, tt_size_t size);



/* //////////////////////////////////////////////////////////////////////////////////////
* extern
*/
__tt_extern_c_leave__

#endif
