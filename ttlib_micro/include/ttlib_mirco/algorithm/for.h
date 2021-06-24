/*
 * @Copyright (C) 2019-2021, TTLIB
 * @file       for.h
 * @ingroup    algorithm
 * @author     tango
 * @date       2020-11-19 
 * @brief      for.h file
 */

#ifndef TT_ALGORITHM_FOR_H
#define TT_ALGORITHM_FOR_H

/* //////////////////////////////////////////////////////////////////////////////////////
 * includes
 */
#include "prefix.h"
#include "../container/container.h"

/* //////////////////////////////////////////////////////////////////////////////////////
* extern
*/
__tt_extern_c_enter__

#define tt_for(type, item, head, tail, iterator) \
			/*iterator*/ \
			tt_iterator_ref_t item##_iterator = (tt_iterator_ref_t)iterator; \
			tt_assert(item##_iterator && (tt_iterator_mode(item##_iterator) & (TT_ITERATOR_MODE_FORWARD | TT_ITERATOR_MODE_RACCESS))); \
			/*init*/ \
			type item; \
			tt_size_t item##_itor = head; \
			tt_size_t item##_head = head; \
			tt_size_t item##_tail = tail; \
			/*walk*/ \
			if( item##_iterator && item##_head != item##_tail) \
				for( ; \
			         item##_itor != item##_tail && (item = (type)tt_iterator_item(item##_iterator, item##_itor), 1); \
					 item##_itor = tt_iterator_next(item##_iterator, item##_itor))


/* eg.
 *
 * tt_for_all(tt_demo_single_list_entry_ref_t, item0, iterator)
 * {
 * tt_trace_d("%d", (tt_demo_single_list_entry_ref_t)item0->user_data);
 * }
*/
#define tt_for_all(type, item, iterator) \
	        tt_iterator_ref_t  item##_iterator_all = (tt_iterator_ref_t)iterator; \
			tt_for(type, item, tt_iterator_head(item##_iterator_all), tt_iterator_tail(item##_iterator_all), item##_iterator_all)


__tt_extern_c_leave__

#endif
