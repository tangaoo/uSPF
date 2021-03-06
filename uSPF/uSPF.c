/*!The uSPF
 *
 * @Copyright (C) 2019-2021, uSPF
 *
 * @file       uSPF.c
 * @ingroup    uspf
 * @author     tango
 * @date       2021-06-16 
 * @brief      uSPF.c file
 */

#define TT_TRACE_MODULE_NAME    "uspf_lib"
#define TT_TRACE_MODULE_DEBUG   0

/* //////////////////////////////////////////////////////////////////////////////////////
 * includes
 */
#include "uSPF.h"

/* //////////////////////////////////////////////////////////////////////////////////////
 * globals
 */

// uspf hub list header
static tt_list_entry_head_t s_uspf_hub_list; 

// static spinlock
static tt_spinlock_t   s_lock = TT_SPINLOCK_INITIALIZER;

/* //////////////////////////////////////////////////////////////////////////////////////
 * implementation
 */
tt_bool_t uspf_init(tt_void_t)
{
    tt_trace_d("uspf init");

    // init list header
    tt_list_entry_init(&s_uspf_hub_list, uspf_hub_list_t, entry, tt_null);

    return tt_true;
}

tt_void_t uspf_exit(tt_void_t)
{
    tt_trace_d("uspf exit");

    tt_iterator_ref_t iterator_hub = tt_list_entry_iterator(&s_uspf_hub_list);
    // tt_trace_d("iterator_hub, %p", iterator_hub);
    // walk hub list
    tt_for_all(uspf_hub_list_ref_t, item_hub, iterator_hub)
    {
        tt_trace_d("hub, %p", item_hub->hub);
        tt_trace_d("free hub pdata, %p", item_hub->hub->pdata);
        // free pdata
        if(item_hub->hub->pdata) 
        {
            tt_free(item_hub->hub->pdata);
            item_hub->hub->pdata = tt_null;
        }

        tt_iterator_ref_t iterator_node = tt_list_entry_iterator(&item_hub->hub->node_list);

        /// walk uspf_node
        tt_size_t itor = tt_iterator_head(iterator_node);

        while (itor != tt_iterator_tail(iterator_node))
        {
            // save next before remove
            tt_size_t next = tt_iterator_next(iterator_node, itor);

            // item
            uspf_node_ref_t item = tt_iterator_item(iterator_node, itor);

            // remove
            tt_iterator_remove(iterator_node, itor);

            tt_trace_d("free node, %p", item);
            if(item) tt_free(item);

            // size
            item_hub->hub->node_num--;

            itor = next;
        }
    }
}

tt_bool_t uspf_register(uspf_hub_ref_t hub, tt_int_t (*echo)(tt_void_t* param))
{
    tt_assert_and_check_abort(hub);
    tt_bool_t ok = tt_false;

    // check if have been registered
    tt_check_return_val(hub->pdata == tt_null, tt_false);

    // init hub and append to hub list
    do
    {
        // create data
        hub->pdata = tt_malloc0(hub->msg_size);
        tt_trace_d("register, hub->pdata, %p", hub->pdata);
        hub->echo = echo;
        tt_check_break(hub->pdata != tt_null);

        // init node_list
        tt_list_entry_init(&hub->node_list, uspf_node_t, entry, tt_null);

        // lock
        tt_spinlock_enter(&s_lock);

        uspf_hub_list_ref_t node = (uspf_hub_list_ref_t)tt_malloc(sizeof(uspf_hub_list_t));
        node->hub = hub;
        tt_trace_d("hub, %p", node->hub);
        tt_list_entry_insert_tail(&s_uspf_hub_list, &node->entry);

        // unlock
        tt_spinlock_leave(&s_lock);

        ok = tt_true;

    } while (0);
    
    return ok;
}

uspf_node_ref_t uspf_subscribe(uspf_hub_ref_t hub, uspf_sync_flag_t flag, tt_void_t (*cb)(tt_void_t* param))
{
    tt_assert_and_check_abort(hub); 
    tt_check_return_val(hub->node_num <= USPF_LINK_NAME_MAX, tt_null);
    
    // create node
    uspf_node_ref_t node = (uspf_node_ref_t)tt_malloc(sizeof(uspf_node_t));
    tt_check_return_val(node != tt_null, tt_null);

    tt_trace_d("subscribe, new node, %p", node);
    // init node
    node->renewal = tt_false;
    node->cb      = cb;
    if(flag == USPF_SYNC) 
    {
        node->event = tt_semaphore_init(0);
        tt_trace_d("node->event, %p", node->event);
    }

    // lock
    tt_spinlock_enter(&s_lock);

    // add node to node_list
    tt_list_entry_insert_tail(&hub->node_list, &node->entry);
    hub->node_num++;

    // unlock
    tt_spinlock_leave(&s_lock);

    return node;
}

tt_bool_t uspf_unsubscribe(uspf_hub_ref_t hub, uspf_node_ref_t node)
{
    tt_assert_and_check_return_val(hub && node, tt_false);

    // TODO check if node in list?

    tt_spinlock_enter(&s_lock);

    tt_list_entry_remove(&hub->node_list, &node->entry);

    tt_spinlock_leave(&s_lock);

    tt_trace_d("unsubscribe, free node, %p", node);
    // free node
    if(node) tt_free(node);
    hub->node_num--;

    return tt_true;
}

tt_bool_t uspf_publish(uspf_hub_ref_t hub, const void* data)
{
    // check
    tt_assert_and_check_return_val(hub && data, tt_false);

    // check the hub have register
    tt_check_return_val(hub->pdata != tt_null, tt_false);

    // iterator
    tt_iterator_ref_t iterator = tt_list_entry_iterator(&hub->node_list);

    // lock
    tt_spinlock_enter(&s_lock);

    // copy data
    memcpy(hub->pdata, data, hub->msg_size);

    hub->published = 1;

    // walk node_list
    tt_for_all(uspf_node_ref_t, node1, iterator)
    {
        // update flag
        node1->renewal = tt_true;
        if(node1->event) tt_semaphore_post(node1->event, 1); 
        tt_trace_d("publish, node, %p", node1);
    }

    // unlock
    tt_spinlock_leave(&s_lock);

    // walk node_list, can't be reentrant, also can't put it in lock area
    tt_for_all(uspf_node_ref_t, node2, iterator)
    {
        if(node2->cb != tt_null) node2->cb(hub->pdata);
    }

    return tt_true;    
}

tt_bool_t uspf_poll(uspf_node_ref_t node)
{
    tt_assert_and_check_return_val(node, tt_false);

    return node->renewal;
}

tt_bool_t uspf_poll_sync(uspf_node_ref_t node, unsigned int timeout)
{
    tt_assert_and_check_return_val(node, tt_false);

    tt_semaphore_wait(node->event);

    return tt_true;
}

tt_bool_t uspf_copy(uspf_hub_ref_t hub, uspf_node_ref_t node, void* buff)
{
    tt_assert_and_check_return_val(hub && node && buff, tt_false);

    // check hub pdata
    tt_check_return_val(hub->pdata != tt_null, tt_false);
    // check if publish
    tt_check_return_val(hub->published, tt_false);

    tt_spinlock_enter(&s_lock);

    tt_trace_d("copy, hub->pdata, %p", hub->pdata);
    memcpy(buff, hub->pdata, hub->msg_size);
    node->renewal = tt_false;

    tt_spinlock_leave(&s_lock);

    return tt_true;
}

tt_bool_t uspf_copy_hub(uspf_hub_ref_t hub, tt_void_t* buff)
{
    tt_assert_and_check_return_val(hub && buff, tt_false);

    // check hub pdata
    tt_check_return_val(hub->pdata != tt_null, tt_false);
    // check if publish
    tt_check_return_val(hub->published, tt_false);

    tt_spinlock_enter(&s_lock);
    memcpy(buff, hub->pdata, hub->msg_size);
    tt_spinlock_leave(&s_lock);

    return tt_true;
}

tt_bool_t uspf_node_clear(uspf_node_ref_t node)
{
    tt_assert_and_check_return_val(node, tt_false);

    tt_spinlock_enter(&s_lock);
    node->renewal = tt_false;
    tt_spinlock_leave(&s_lock);

    return tt_true;
}

