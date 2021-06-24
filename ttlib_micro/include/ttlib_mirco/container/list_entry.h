/*
 * @Copyright (C) 2019-2021, TTLIB
 * @file       list_entry.h
 * @ingroup    container
 * @author     tango
 * @date       2020-11-19 
 * @brief      list_entry.h file
 */

#ifndef TT_CONTAINER_LIST_ENTRY_H
#define TT_CONTAINER_LIST_ENTRY_H

/* //////////////////////////////////////////////////////////////////////////////////////
 * includes
 */
#include "prefix.h"
#include "iterator.h"

/// the list entry
#define tt_list_entry(head, entry)   ((((tt_byte_t*)(entry)) - (head)->eoffset))

/*! get the list entry with zero offset
*
* @code
*
// the xxxx entry type
typedef struct __tt_xxxx_entry_t
{
// the list entry (be placed in header with zero offset)
   tt_list_entry_t  entry;

// ..

}tt_xxxx_entry_t;
*
* @endcode
*/
#define tb_list_entry0(entry)        (entry)

/*! init the list entry
*
* @code
*
// the xxxx entry type
typedef struct __tt_xxxx_entry_t
{
// the list entry
tt_list_entry_t             entry;

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
tt_list_entry_head_t list;
tt_list_entry_init(&list, tt_xxxx_entry_t, entry, tt_xxxx_entry_copy);

* @endcode
*/
#define tt_list_entry_init(list, type, entry, copy)     tt_list_entry_init_(list, tt_offsetof(type, entry), sizeof(type), copy)


/* //////////////////////////////////////////////////////////////////////////////////////
* extern
*/
__tt_extern_c_enter__

/* //////////////////////////////////////////////////////////////////////////////////////
* types
*/

/*! the doubly-linked list entry type
*
* <pre>
*       tail
*        |
* list: list <-> head <-> ... <-> last
*        |                         |
*        <------------------------->
*
* </pre>
*/
typedef struct __tt_list_entry_t
{
	/// the next entry
	struct __tt_list_entry_t*                 next;
	/// the prev entry
	struct __tt_list_entry_t*                 prev;

}tt_list_entry_t, *tt_list_entry_ref_t;

/// the list head type
typedef struct __tt_list_entry_head_t
{
	/// the next entry
	struct __tt_list_entry_t*                 next;

	/// the prev entry
	struct __tt_list_entry_t*                 prev;

	/// the list node size
	tt_size_t                                 size;

	/// the list iterator
	tt_iterator_t                             itor;

	/// the entry offset
	tt_size_t                                 eoffset;

	/// the entry copy func
	tt_entry_copy_t                           copy;

}tt_list_entry_head_t, *tt_list_entry_head_ref_t;

/* //////////////////////////////////////////////////////////////////////////////////////
* interfaces
*/

/*! init list
*
* @param list                                  the list
* @param entry_offset                          the entry offset
* @param entry_size                            the entry size
* @param copy_func                             the copy func of the entry for algorithm, .e.g sort
*/
tt_void_t                                      tt_list_entry_init_(tt_list_entry_head_ref_t list, tt_size_t entry_offset, tt_size_t entry_size, tt_entry_copy_t copy_func);

/*! exit list
*
* @param list                                  the list
*/
tt_void_t                                      tt_list_entry_exit(tt_list_entry_head_ref_t list);

/*! get the list iterator
*
* @param list                                  the list
* @return iterator
*/
tt_iterator_ref_t                              tt_list_entry_iterator(tt_list_entry_head_ref_t list);


/*! list clear
*
* @param list                                  the list
*/
static __tt_inline__ tt_void_t                 tt_list_entry_clear(tt_list_entry_head_ref_t list)
{
	/// assert
	tt_assert(list);

	/// clear list
	list->next = (tt_list_entry_ref_t)list;
	list->prev = (tt_list_entry_ref_t)list;
	list->size = 0;

}

/*! get list size
*
* @param list                                  the list
* @return                                      the entry count of list
*/
static __tt_inline__ tt_size_t                 tt_list_entry_size(tt_list_entry_head_ref_t list)
{
	/// assert
	tt_assert(list);

	/// done
	return list->size;
}

/*! get entry next entry
*
* @param entry                                 entry of list
* @return                                      next entry
*/
static __tt_inline__ tt_list_entry_ref_t       tt_list_entry_next(tt_list_entry_ref_t entry)
{
	/// assert
	tt_assert(entry);

	/// done
	return entry->next;
}

/*! get entry prev entry
*
* @param entry                                 entry of list
* @return                                      prev entry
*/
static __tt_inline__ tt_list_entry_ref_t       tt_list_entry_prev(tt_list_entry_ref_t entry)
{
	/// assert
	tt_assert(entry);

	/// done
	return entry->prev;
}

/*! the list head
*
* @param list                                  the list
* @return                                      head entry
*/
static __tt_inline__ tt_list_entry_ref_t       tt_list_entry_head(tt_list_entry_head_ref_t list)
{
	/// assert 
	tt_assert(list);

	/// done
	return list->next;
}

/*! the list last
*
* @param list                                  the list
* @return                                      last entry
*/
static __tt_inline__ tt_list_entry_ref_t       tt_list_entry_last(tt_list_entry_head_ref_t list)
{
	/// assert
	tt_assert(list);

	/// done
	return list->prev;
}

/*! the list tail
*
* @param list                                  the list
* @return                                      tail
*/
static __tt_inline__ tt_list_entry_ref_t       tt_list_entry_tail(tt_list_entry_head_ref_t list)
{
	/// assert
	tt_assert(list);

	/// done
	return (tt_list_entry_ref_t)list;
}

/*! the list is null?
*
* @param list                                  the list
* @return                                      is null?
*/
static __tt_inline__ tt_bool_t                 tt_list_entry_is_null(tt_list_entry_head_ref_t list)
{
	/// assert 
	tt_assert(list);

	/// done
	return !list->size;
}

/*! the list is head?
*
* @param list                                  the list
* @return                                      is head?
*/
static __tt_inline__ tt_bool_t                 tt_list_entry_is_head(tt_list_entry_head_ref_t list, tt_list_entry_ref_t entry)
{
	/// assert
	tt_assert(entry && list);

	/// done
	return entry == list->next;
}

/*! the list is last?
*
* @param list                                  the list
* @return                                      is last?
*/
static __tt_inline__ tt_bool_t                 tt_list_entry_is_last(tt_list_entry_head_ref_t list, tt_list_entry_ref_t entry)
{
	/// assert 
	tt_assert(entry && list);

	/// done
	return entry == list->prev;
}

/*! the list is valid?
*
* @param list                                  the list
* @return                                      tt_true or tt_false?
*/
static __tt_inline__ tt_bool_t                 tt_list_entry_is_valid(tt_list_entry_head_ref_t list)
{
	/// assert
	tt_assert(list);

	/// done
	return (list->next && list->next->prev == (tt_list_entry_ref_t)list) && (list->prev && list->prev->next == (tt_list_entry_ref_t)list);
}

/*! splice the spliced_list to list[prev, next]
*
* @param list                                  the list
* @param prev                                  the prev
* @param next                                  the next
* @param spliced_list                          the spliced list
*/
static __tt_inline__ tt_void_t                 tt_list_entry_spliced(tt_list_entry_head_ref_t list, tt_list_entry_ref_t prev, tt_list_entry_ref_t next, tt_list_entry_head_ref_t spliced_list)
{
	/// assert
	tt_assert(list && prev && next);
	tt_assert(spliced_list && spliced_list->next && spliced_list->prev);

	/// valid
	tt_assert(tt_list_entry_is_valid(list));
	tt_assert(tt_list_entry_is_valid(spliced_list));

	tt_check_return(!tt_list_entry_is_null(spliced_list));

	/// done
	spliced_list->next->prev  = prev;
	prev->next                = spliced_list->next;
	spliced_list->prev->next  = next;
	next->prev                = spliced_list->prev;

	/// update size
	list->size += spliced_list->size;

	/// clear spliced_list
	tt_list_entry_clear(spliced_list);
}

/*! splice the spliced_list at the list head
*
* @param list                              the list
* @param spliced_list                      the spliced list
*/
static __tt_inline__ tt_void_t              tt_list_entry_splice_head(tt_list_entry_head_ref_t list, tt_list_entry_head_ref_t spliced_list)
{
	// check
	tt_assert(list);

	// done
	tt_list_entry_spliced(list, (tt_list_entry_ref_t)list, list->next, spliced_list);
}

/*! splice the spliced_list at the list tail
*
* @param list                              the list
* @param spliced_list                      the spliced list
*/
static __tt_inline__ tt_void_t              tt_list_entry_splice_tail(tt_list_entry_head_ref_t list, tt_list_entry_head_ref_t spliced_list)
{
	// check
	tt_assert(list);

	// done
	tt_list_entry_spliced(list, list->prev, (tt_list_entry_ref_t)list, spliced_list);
}

/*! insert entry to the next
*
* @param list                              the list
* @param node                              the list node
* @param entry                             the inserted list entry
*/
static __tt_inline__ tt_void_t              tt_list_entry_insert(tt_list_entry_head_ref_t list, tt_list_entry_ref_t node, tt_list_entry_ref_t entry)
{
	/// assert
	tt_assert(list && node && entry);
	tt_assert(node != entry);

	/// valid
	tt_list_entry_is_valid(list);

	/// done
	node->next->prev  = entry;
	entry->next       = node->next;
	entry->prev       = node;
	node->next        = entry;

	/// update size
	list->size++;

}

/*! insert entry to the prev
*
* @param list                              the list
* @param node                              the list node
* @param entry                             the inserted list entry
*/
static __tt_inline__ tt_void_t              tt_list_entry_insert_prev(tt_list_entry_head_ref_t list, tt_list_entry_ref_t node, tt_list_entry_ref_t entry)
{
	/// assert
	tt_assert(list && node);

	tt_list_entry_insert(list, node->prev, entry);
}

/*! insert entry to the head
*
* @param list                              the list
* @param entry                             the inserted list entry
*/
static __tt_inline__ tt_void_t              tt_list_entry_insert_head(tt_list_entry_head_ref_t list, tt_list_entry_ref_t entry)
{
	/// assert
	tt_assert(list);
	tt_list_entry_insert(list, (tt_list_entry_ref_t)list, entry);
}

/*! insert entry to the tail
*
* @param list                              the list
* @param entry                             the inserted list entry
*/
static __tt_inline__ tt_void_t              tt_list_entry_insert_tail(tt_list_entry_head_ref_t list, tt_list_entry_ref_t entry)
{
	/// assert
	tt_assert(list);
	tt_list_entry_insert(list, list->prev, entry);
}

/*! replace the entry
*
* @param list                              the list
* @param node                              the replaced list node
* @param entry                             the new list entry
*/
static __tt_inline__ tt_void_t              tt_list_entry_replace(tt_list_entry_head_ref_t list, tt_list_entry_ref_t node, tt_list_entry_ref_t entry)
{
	/// assert
	tt_assert(list && node && entry);
	tt_assert(node != entry);
	
	// replace it
	entry->next = node->next;
	entry->next->prev = entry;
	entry->prev = node->prev;
	entry->prev->next = entry;

}

/*! replace the next entry
*
* @param list                              the list
* @param node                              the list node
* @param entry                             the new list entry
*/
static __tt_inline__ tt_void_t              tt_list_entry_replace_next(tt_list_entry_head_ref_t list, tt_list_entry_ref_t node, tt_list_entry_ref_t entry)
{
	/// assert
	tt_assert(node && entry);

	/// replace it
	tt_list_entry_replace(list, node->next, entry);
}

/*! replace the prev entry
*
* @param list                              the list
* @param node                              the list node
* @param entry                             the new list entry
*/
static __tt_inline__ tt_void_t              tt_list_entry_replace_prev(tt_list_entry_head_ref_t list, tt_list_entry_ref_t node, tt_list_entry_ref_t entry)
{
	/// assert
	tt_assert(node);

	/// replace it
	tt_list_entry_replace(list, node->prev, entry);
}

/*! replace the head entry
*
* @param list                              the list
* @param entry                             the new list entry
*/
static __tt_inline__ tt_void_t              tt_list_entry_replace_head(tt_list_entry_head_ref_t list, tt_list_entry_ref_t entry)
{
	/// assert
	tt_assert(entry);

	/// replace it
	tt_list_entry_replace(list, list->next, entry);
}

/*! replace the last entry
*
* @param list                              the list
* @param entry                             the new list entry
*/
static __tt_inline__ tt_void_t              tt_list_entry_replace_last(tt_list_entry_head_ref_t list, tt_list_entry_ref_t entry)
{
	/// assert
	tt_assert(entry);

	/// replace it
	tt_list_entry_replace(list, list->prev, entry);
}

/*! remove the entry (private interface)
*
* @param list                              the list
* @param prev                              the prev entry
* @param next                              the next entry
*/
static __tt_inline__ tt_void_t              tt_list_entry_remove_(tt_list_entry_head_ref_t list, tt_list_entry_ref_t prev, tt_list_entry_ref_t next)
{
	// check
	tt_assert(list && list->size && prev && next);

	// valid?
	tt_assert(tt_list_entry_is_valid(list));

	// remove entries
	prev->next = next;
	next->prev = prev;

	// update size
	list->size--;
}

/*! remove the entry
*
* @param list                              the list
* @param entry                             the removed list entry
*/
static __tt_inline__ tt_void_t              tt_list_entry_remove(tt_list_entry_head_ref_t list, tt_list_entry_ref_t entry)
{
	/// assert 
	tt_assert(entry);
	
	/// done
	tt_list_entry_remove_(list, entry->prev, entry->next);
}

/*! remove the next entry
*
* @param list                              the list
* @param prev                              the prev entry
*/
static __tt_inline__ tt_void_t              tt_list_entry_remove_next(tt_list_entry_head_ref_t list, tt_list_entry_ref_t entry)
{
	/// assert
	tt_assert(entry);

	/// done
	tt_list_entry_remove_(list, entry, entry->next->next);
}

/*! remove the prev entry
*
* @param list                              the list
* @param next                              the next entry
*/
static __tt_inline__ tt_void_t              tt_list_entry_remove_prev(tt_list_entry_head_ref_t list, tt_list_entry_ref_t entry)
{
	/// assert
	tt_assert(entry);

	/// done
	tt_list_entry_remove_(list, entry->prev->prev, entry);
}

/*! remove the head entry
*
* @param list                              the list
*/
static __tt_inline__ tt_void_t              tt_list_entry_remove_head(tt_list_entry_head_ref_t list)
{
	/// assert
	tt_assert(list);

	/// done
	tt_list_entry_remove_(list, (tt_list_entry_ref_t)list, list->next->next);
}

/*! remove the last entry
*
* @param list                              the list
*/
static __tt_inline__ tt_void_t             tt_list_entry_remove_last(tt_list_entry_head_ref_t list)
{
	/// assert
	tt_assert(list);

	/// done
	tt_list_entry_remove_(list, list->prev->prev, (tt_list_entry_ref_t)list);
}


/* //////////////////////////////////////////////////////////////////////////////////////
* extern
*/
__tt_extern_c_leave__

#endif