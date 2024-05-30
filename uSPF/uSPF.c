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

// uspf msg list header
// static tt_list_entry_head_t s_uspf.reg_msg_list; 
static uspf_t s_uspf;

// static spinlock
static tt_spinlock_t   s_lock = TT_SPINLOCK_INITIALIZER;

/* //////////////////////////////////////////////////////////////////////////////////////
 * implementation
 */
tt_bool_t uspf_init(tt_void_t)
{
    tt_trace_d("uspf init");

    // init register message list 
    tt_list_entry_init(&s_uspf.reg_msg_list, uspf_msg_t, entry, tt_null);
    tt_list_entry_init(&s_uspf.pub_msg_list, uspf_msg_t, entry, tt_null);

    s_uspf.enable = tt_true;
    s_uspf.running = tt_false;

    s_uspf.have_init = tt_true;

    return tt_true;
}

tt_void_t uspf_start(tt_void_t)
{
    s_uspf.enable = tt_true;
}

// TODO
tt_void_t uspf_exit(tt_void_t)
{
    tt_trace_d("uspf exit");

    tt_iterator_ref_t iterator_msg = tt_list_entry_iterator(&s_uspf.reg_msg_list);
    // tt_trace_d("iterator_msg, %p", iterator_msg);
    // walk msg list
    tt_for_all(uspf_msg_ref_t, item_msg, iterator_msg)
    {
        tt_trace_d("msg, %p", item_msg->msg_name);
        tt_trace_d("free msg pdata, %p", item_msg->pdata);
        // free pdata
        if(item_msg->pdata) 
        {
            // tt_free(item_msg->pdata);
            item_msg->pdata = tt_null;
        }

        tt_iterator_ref_t iterator_node = tt_list_entry_iterator(&item_msg->subscribe_list);

        /// walk uspf_node
        tt_size_t itor = tt_iterator_head(iterator_node);

        while (itor != tt_iterator_tail(iterator_node))
        {
            // save next before remove
            tt_size_t next = tt_iterator_next(iterator_node, itor);

            // // item
            // uspf_node_ref_t item = tt_iterator_item(iterator_node, itor);

            // // remove
            // tt_iterator_remove(iterator_node, itor);

            // tt_trace_d("free node, %p", item);
            // if(item) tt_free(item);

            // size
            item_msg->node_num--;

            itor = next;
        }
    }
}

tt_void_t uspf_run(tt_void_t)
{
    tt_assert_and_check_return(s_uspf.have_init == tt_true);

    // running 
    while (s_uspf.enable)
    {
        s_uspf.running = tt_true;

        tt_iterator_ref_t msg_iterator = tt_list_entry_iterator(&s_uspf.reg_msg_list);

        tt_spinlock_enter(&s_lock);
        tt_trace_d("msg size %d", tt_list_entry_size(&s_uspf.reg_msg_list));
        tt_for_all(uspf_msg_ref_t, msg1, msg_iterator)
        {
            if(msg1->published == tt_true)
            {
                tt_iterator_ref_t actor_iterator = tt_list_entry_iterator(&msg1->subscribe_list);
                tt_for_all(uspf_actor_node_ref_t, actor_node, actor_iterator)
                {
                    uspf_reactor_node_ref_t reactor_node = (uspf_reactor_node_ref_t)actor_node;
                    tt_trace_d("reactor_node,%x, reactor,%x, handle,%x, %d", reactor_node, reactor_node->reactor, reactor_node->reactor->msg_handler, reactor_node->debug);
                    // if(actor_node->actor->renewal == tt_true)
                    {
                        if (reactor_node->reactor->msg_handler != NULL)
                        {
                            reactor_node->reactor->msg_handler(reactor_node->reactor, msg1);
                        }
                        // actor_node->actor->renewal = tt_false;
                    }
                }
                msg1->published = tt_false;

            }
        }

        tt_spinlock_leave(&s_lock);
    }
    
    s_uspf.running = tt_false;
    
}

tt_bool_t uspf_register(uspf_msg_ref_t msg, tt_int_t (*echo)(tt_void_t* param))
{
    tt_assert_and_check_abort(msg);
    tt_bool_t ok = tt_false;

    // check if msg must be static memory allocation
    tt_check_return_val(msg->pdata != tt_null, tt_false);

    // check if msg register again
    tt_check_return_val(msg->enable == tt_false, tt_false);

    // init msg and append to msg list
    do
    {
        tt_trace_d("register, msg, %x", msg);
        msg->echo = echo;

        // init subscribe_list
        tt_list_entry_init(&msg->subscribe_list, uspf_actor_node_t, entry, tt_null);

        // lock
        tt_spinlock_enter(&s_lock);

        tt_size_t size = tt_list_entry_size(&s_uspf.reg_msg_list);
        tt_trace_d("size, %d", size);
        if(size >= 2)
        {
            uspf_msg_ref_t msg1 = tt_null;
            uspf_msg_ref_t msg2 = tt_null;
            tt_list_entry_ref_t node_tail = tt_list_entry_tail(&s_uspf.reg_msg_list);
            tt_list_entry_ref_t node_head = tt_list_entry_head(&s_uspf.reg_msg_list);

            tt_iterator_ref_t iterator = tt_list_entry_iterator(&s_uspf.reg_msg_list);

            if(msg->priority >= ((uspf_msg_ref_t)node_tail)->priority)
            {
                tt_list_entry_insert_tail(&s_uspf.reg_msg_list, &msg->entry);
            }
            else if(msg->priority < ((uspf_msg_ref_t)node_head)->priority)
            {
                tt_list_entry_insert_head(&s_uspf.reg_msg_list, &msg->entry);
            }
            else
            {
                // walk list
                tt_size_t entry = tt_iterator_head(iterator);
                while (entry != tt_iterator_tail(iterator))
                {
                    msg1 = (uspf_msg_ref_t)tt_iterator_item(iterator, entry);
                    entry = tt_iterator_next(iterator, entry);
                    msg2 = (uspf_msg_ref_t)tt_iterator_item(iterator, entry);
                    if (entry != tt_iterator_tail(iterator))
                    {
                        if (msg->priority >= msg1->priority && msg->priority < msg2->priority)
                            tt_list_entry_insert(&s_uspf.reg_msg_list, &msg1->entry, &msg->entry);
                    }
                }
            }

        }
        else if(size == 1)
        {
            tt_list_entry_ref_t node_head = tt_list_entry_head(&s_uspf.reg_msg_list);
            if(((uspf_msg_ref_t)node_head)->priority < msg->priority)
                tt_list_entry_insert_tail(&s_uspf.reg_msg_list, &msg->entry);
            else
                tt_list_entry_insert_head(&s_uspf.reg_msg_list, &msg->entry);
        }
        else if(size == 0)
        {
            tt_list_entry_insert_tail(&s_uspf.reg_msg_list, &msg->entry);
        }
        else
        {
            tt_trace_w("uspf msg size %d", size);
        }

        msg->enable = tt_true;
        // unlock
        tt_spinlock_leave(&s_lock);

        ok = tt_true;

    } while (0);
    
    return ok;
}


tt_int_t uspf_subscribe(uspf_msg_ref_t msg, uspf_actor_node_ref_t actor_node, tt_uint8_t priority, void const *const param)
{
    tt_assert_and_check_abort(msg != tt_null); 
    tt_check_return_val(msg->node_num < USPF_LINK_NAME_MAX, -1);
    tt_assert_and_check_return_val(priority >= 0 && priority < 256, -1);

    tt_check_return_val(actor_node != tt_null, -1);
    // aviod the same actor_node subscribe again 
    // tt_check_return_val(actor_node->enable != tt_true, -1);

    // update actor_node
    actor_node->actor->priority = priority;
    actor_node->actor->renewal = tt_false;
    actor_node->actor->enable = tt_true;
    actor_node->actor->name = param;

    tt_spinlock_enter(&s_lock);
    tt_list_entry_insert_tail(&msg->subscribe_list, &actor_node->entry);
    tt_spinlock_exit(&s_lock);

    tt_trace_d("subscribe, msg,%x, actor_node,%x, actor,%x, handler,%x", msg, actor_node, actor_node->actor, ((uspf_reactor_node_ref_t)actor_node)->reactor->msg_handler);

    // update 
    // msg->priority = actor->priority;
    msg->node_num++;

    return 0;
}

tt_bool_t uspf_unsubscribe(uspf_msg_ref_t msg, uspf_actor_node_ref_t actor_node)
{
    tt_assert_and_check_abort(msg); 

    tt_check_return_val(actor_node != tt_null, -1);
    tt_check_return_val(msg->node_num > 0, -2);

    tt_spinlock_enter(&s_lock);

    tt_list_entry_remove(&msg->subscribe_list, &actor_node->entry);
    msg->node_num--;

    tt_spinlock_exit(&s_lock);

    return 0;
}

tt_bool_t uspf_reactor_init(uspf_msg_ref_t msg, void *reactor_node, tt_uint8_t priority, void const *const param)
{
    tt_assert_and_check_return_val(reactor_node != NULL, tt_false);

    uspf_actor_node_ref_t actor_node = (uspf_actor_node_ref_t)reactor_node;

    uspf_subscribe(msg, actor_node, priority, param);

    return tt_true;
}




tt_bool_t uspf_publish(uspf_msg_ref_t msg, const void* data)
{
    // check
    tt_assert_and_check_return_val(msg && data, tt_false);

    // check the msg have register
    tt_check_return_val(msg->pdata != tt_null, tt_false);

    // iterator
    tt_iterator_ref_t iterator = tt_list_entry_iterator(&msg->subscribe_list);

    // lock
    tt_spinlock_enter(&s_lock);

    // copy data
    memcpy(msg->pdata, data, msg->msg_size);


    // update all subscribe actors
    tt_for_all(uspf_actor_node_ref_t, actor_node, iterator)
    {
        // update flag
        actor_node->actor->renewal = tt_true;
        // if(node1->event) tt_semaphore_post(node1->event, 1); 
        tt_trace_d("publish, actor, %p", actor_node);
    }

    // unlock
    tt_spinlock_leave(&s_lock);

    // walk subscribe_list, can't be reentrant, also can't put it in lock area
    // tt_for_all(uspf_node_ref_t, node2, iterator)
    // {
    //     if(node2->cb != tt_null) node2->cb(msg->pdata);
    // }

    msg->published = tt_true;

    return tt_true;    
}







