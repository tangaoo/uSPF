/*
 * @Copyright (C) 2019-2021, TTLIB
 * @file       single_list_entry.h
 * @ingroup    container
 * @author     tango
 * @date       2020-11-19 
 * @brief      single_list_entry.h file
 */

#ifndef TT_CONTAINER_SINGLE_LIST_ENTRY_H
#define TT_CONTAINER_SINGLE_LIST_ENTRY_H

/* //////////////////////////////////////////////////////////////////////////////////////
 * includes
 */
#include "prefix.h"
#include "iterator.h"

/* //////////////////////////////////////////////////////////////////////////////////////
* extern
*/
__tt_extern_c_enter__

/// the entry of list item
#define tt_single_list_entry(head, entry)   ((((tt_byte_t*)(entry)) - (head)->eoffset))

/*! get the list entry with zero offset
*
* @code
*
// the xxxx entry type
typedef struct __tt_xxxx_entry_t
{
// the list entry (be placed in header with zero offset)
tt_single_list_entry_t  entry;

// ..

}tt_xxxx_entry_t;
*
* @endcode
*/
#define tb_single_list_entry0(entry)        (entry)

/*! init the list entry
*
* @code
*
// the xxxx entry type
typedef struct __tt_xxxx_entry_t
{
// the list entry
tt_single_list_entry_t      entry;

// the data
tt_size_t                   data;

}tt_xxxx_entry_t;

// the xxxx entry copy func
static tb_void_t tt_xxxx_entry_copy(tt_pointer_t litem, tt_pointer_t ritem)
{
// check
//tt_assert(litem && ritem);

// copy it
((tt_xxxx_entry_t*)litem)->data = ((tt_xxxx_entry_t*)ritem)->data;
}


// init the list
tt_single_list_entry_head_t list;
tt_single_list_entry_init(&list, tt_xxxx_entry_t, entry, tt_xxxx_entry_copy);

* @endcode
*/
#define tt_single_list_entry_init(list, type, entry, copy)     tt_single_list_entry_init_(list, tt_offsetof(type, entry), sizeof(type), copy)

/* //////////////////////////////////////////////////////////////////////////////////////
 * types
 */

/* single list entry type
 *
 *                list->next        list->last           
 *                   |                  |
 * list: head -> entry[first]... -> entry[last] -> NULL
 */
typedef struct __tt_single_list_entry_t
{
	/// the next entry
	struct __tt_single_list_entry_t*         next;

}tt_single_list_entry_t, *tt_single_list_entry_ref_t;

/// the single list head type
typedef struct __tt_single_list_entry_head_t
{
	/// the next entry
	struct __tt_single_list_entry_t*         next;

	/// the last entry
	struct __tt_single_list_entry_t*         last;

	/// the list node size
	tt_size_t                                size;

	/// the list iterator
	tt_iterator_t                            itor;

	/// the entry offset
	tt_size_t                                eoffset;

	/// the entry copy func
	tt_entry_copy_t                          copy;

}tt_single_list_entry_head_t, *tt_single_list_entry_head_ref_t;

/* //////////////////////////////////////////////////////////////////////////////////////
 * interfaces
 */

/*! init list
 *
 * @param list                     the list
 * @param entry_offset             the entry offset
 * @param entry_size               the item size
 * @param copy_func                the copy func of the entry for algorithm, .e.g sort
 */
tt_void_t                          tt_single_list_entry_init_(tt_single_list_entry_head_ref_t list, tt_size_t entry_offset, tt_size_t entry_size, tt_entry_copy_t copy_func);

/*! exit list
 *
 * @param list                     the list
 */
tt_void_t                          tt_single_list_entry_exit(tt_single_list_entry_head_ref_t list);

/*! get the list iterator
 *
 * @param list                     the list
 * @return iterator
 */
tt_iterator_ref_t                  tt_single_list_entry_iterator(tt_single_list_entry_head_ref_t list);


/* //////////////////////////////////////////////////////////////////////////////////////
 * static implementation
 */
/*! list clear
 *
 * @param list                     the list
 */
static __tt_inline__ tt_void_t     tt_single_list_entry_clear(tt_single_list_entry_head_ref_t list)
{
	/// assert
	tt_assert(list);

	/// clear list
	list->next = tt_null;
	list->last = tt_null;
	list->size = 0;

}

/*! get list size
 *
 * @param list                     the list
 * @return                         the entry count of list
 */
static __tt_inline__ tt_size_t     tt_single_list_entry_size(tt_single_list_entry_head_ref_t list)
{
	/// assert
	tt_assert(list);

	/// done
	return list->size;
}

/*! get entry next entry
*
* @param entry                     entry of list
* @return                          next entry
*/
static __tt_inline__ tt_single_list_entry_ref_t   tt_single_list_entry_next(tt_single_list_entry_ref_t entry)
{
	/// assert
	tt_assert(entry);

	/// done
	return entry->next;
}

/*! the list head
*
* @param list                      the list
* @return                          head entry
*/
static __tt_inline__ tt_single_list_entry_ref_t    tt_single_list_entry_head(tt_single_list_entry_head_ref_t list)
{
	/// assert
	tt_assert(list);

	/// done
	return list->next;
}

/*! the list last
*
* @param list                      the list
* @return                          last entry
*/
static __tt_inline__ tt_single_list_entry_ref_t     tt_single_list_entry_last(tt_single_list_entry_head_ref_t list)
{
	/// assert
	tt_assert(list);

	///done
	return list->last;
}

/*! the list tail
*
* @param list                      the list
* @return                          tail
*/
static __tt_inline__ tt_single_list_entry_ref_t      tt_single_list_entry_tail(tt_single_list_entry_head_ref_t list)
{
	/// assert
	tt_assert(list);

	///done
	return tt_null;
}

/*! the list is null?
*
* @param list                      the list
* @return                          is null?
*/
static __tt_inline__ tt_bool_t     tt_single_list_entry_is_null(tt_single_list_entry_head_ref_t list)
{
	/// assert
	tt_assert(list);

	return !list->size;
}

/*! the entry is head?
*
* @param list                      the list
* @return                          is head?
*/
static __tt_inline__ tt_bool_t     tt_single_list_entry_is_head(tt_single_list_entry_head_ref_t list, tt_single_list_entry_ref_t entry)
{
	/// assert
	tt_assert(list && entry);

	return list->next == entry;
}

/*! the entry is last?
*
* @param list                      the list
* @return                          is last?
*/
static __tt_inline__ tt_bool_t     tt_single_list_entry_is_last(tt_single_list_entry_head_ref_t list, tt_single_list_entry_ref_t entry)
{
	/// assert
	tt_assert(list && entry);

	return list->last == entry;
}

/*! insert entry after node
*
* @param list                      the list
* @param node                      node of the list
* @param entry                     need to be inserted
*/
static __tt_inline__ tt_void_t     tt_single_list_entry_insert_next(tt_single_list_entry_head_ref_t list, tt_single_list_entry_ref_t node, tt_single_list_entry_ref_t entry)
{
	/// assert
	tt_assert(list && node && entry);

	/// update list if node is last or list is null
	if (node == list->last || !list->next) list->last = entry;

	/// insert entry after node
	entry->next = node->next;
	node->next = entry;

	/// add list size
	list->size++;
}

/*! insert list head
*
* @param list                      the list
* @param entry                     need to be inserted
*/
static __tt_inline__ tt_void_t     tt_single_list_entry_insert_head(tt_single_list_entry_head_ref_t list, tt_single_list_entry_ref_t entry)
{
	/// assert
	tt_assert(list && entry);

	/// insert entry
	tt_single_list_entry_insert_next(list, (tt_single_list_entry_ref_t)list, entry);
}

/*! insert list last
*
* @param list                      the list
* @param entry                     need to be inserted
*/
static __tt_inline__ tt_void_t     tt_single_list_entry_insert_tail(tt_single_list_entry_head_ref_t list, tt_single_list_entry_ref_t entry)
{
	/// assert
	tt_assert(list && entry);

	/// insert 
	if (list->last) tt_single_list_entry_insert_next(list, list->last, entry);
	else tt_single_list_entry_insert_head(list, entry);
}

/*! replace entry after node
*
* @param list                      the list
* @param node                      node of the list
* @param entry                     will to replace
*/
static __tt_inline__ tt_void_t     tt_single_list_entry_replace_next(tt_single_list_entry_head_ref_t list, tt_single_list_entry_ref_t node, tt_single_list_entry_ref_t entry)
{
	/// assert
	tt_assert(node && node->next);
	tt_assert(entry);

	/// update list last enty 
	if (node->next == list->last) list->last = entry;

	/// replace it
	entry->next = node->next->next;
	node->next = entry;
}

/*! replace the list head node
*
* @param list                      the list
* @param entry                     will to replace
*/
static __tt_inline__ tt_void_t     tt_single_list_entry_replace_head(tt_single_list_entry_head_ref_t list, tt_single_list_entry_ref_t entry)
{
	/// assert
	tt_assert(list && entry);

	/// done
	tt_single_list_entry_replace_next(list, (tt_single_list_entry_ref_t)list, entry);
}

/*! remove one node(just for inside!)
*
* @param list                      the list
* @param prev                      prev
* @param next                      next
*/
static __tt_inline__ tt_void_t     tt_single_list_entry_remove_(tt_single_list_entry_head_ref_t list, tt_single_list_entry_ref_t prev, tt_single_list_entry_ref_t next)
{
	/// assert
	tt_assert(list && prev && list->size);

	/// update list last, when prev = entry[last-1]
	if (prev->next == list->last) list->last = prev;

	/// remove done
	prev->next = next;
	list->size--;
}

/*! remove next node
*
* @param list                      the list
* @param prev                      prev
*/
static __tt_inline__ tt_void_t     tt_single_list_entry_remove_next(tt_single_list_entry_head_ref_t list, tt_single_list_entry_ref_t prev)
{
	/// assert
	tt_assert(list && prev && prev->next);

	tt_single_list_entry_remove_(list, prev, prev->next->next);
}

/*! remove list head node
*
* @param list                      the list
*/
static __tt_inline__ tt_void_t     tt_single_list_entry_remove_head(tt_single_list_entry_head_ref_t list)
{
	/// assert
	tt_assert(list->next);

	/// done
	tt_single_list_entry_remove_(list, (tt_single_list_entry_ref_t)list, (tt_single_list_entry_ref_t)list->next->next);
}

/* //////////////////////////////////////////////////////////////////////////////////////
* extern
*/
__tt_extern_c_leave__


#endif
