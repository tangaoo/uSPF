/*
 * @Copyright (C) 2019-2021, TTLIB
 *
 * @file       iterator_array.h
 * @ingroup    container
 * @author     tango
 * @date       2020-11-23 
 * @brief      iterator_array.h file
 */

#ifndef TT_CONTAINER_ITERATOR_ARRAY_H
#define TT_CONTAINER_ITERATOR_ARRAY_H

/* //////////////////////////////////////////////////////////////////////////////////////
 * includes
 */
#include "iterator.h"

__tt_extern_c_enter__

/* //////////////////////////////////////////////////////////////////////////////////////
 * types
 */

/// the array iterator
typedef  struct __tt_iterator_array_t
{
    /// the iterator base
    tt_iterator_t       base;

    /// the items
    tt_pointer_t        items;

    /// the items count        
    tt_size_t           count;

}tt_iterator_array_t, *tt_iterator_array_ref_t;

/* //////////////////////////////////////////////////////////////////////////////////////
 * interfaces
 */

/*! init the pointer type array iterator 
 *
 * @param itor          the array iterator 
 * @param items         the items
 * @param count         the count
 *
 * @return              tt_void
 */
tt_iterator_ref_t       tt_iterator_array_init_ptr(tt_iterator_array_ref_t itor, tt_pointer_t* items, tt_size_t count);


__tt_extern_c_leave__

#endif
