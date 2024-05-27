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
    tt_list_entry_init(&s_uspf.reg_actor_list, uspf_actor_t, entry, tt_null);

    s_uspf.enable = tt_true;
    s_uspf.running = tt_false;

    s_uspf.have_init = tt_true;

    return tt_true;
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
        tt_trace_d("msg, %p", item_msg->msg);
        tt_trace_d("free msg pdata, %p", item_msg->msg->pdata);
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

        tt_for_all(uspf_msg_ref_t, msg1, msg_iterator)
        {
            tt_iterator_ref_t actor_iterator = tt_list_entry_iterator(&msg1->subscribe_list);
            tt_for_all(uspf_actor_ref_t, actor1, actor_iterator)
            {
                uspf_reactor_ref_t reactor = (uspf_reactor_ref_t)actor1;
                if(actor1->renewal == tt_true)
                {
                    if(reactor->msg_handler)
                        reactor->msg_handler(reactor, msg1);
                    // tt_trace_i("actor do: [msg],%s, [atctor],%s", msg1->msg_name, actor1->name);
                    actor1->renewal = tt_false;
                }
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

    // init msg and append to msg list
    do
    {
        // create data
        // msg->pdata = tt_malloc0(msg->msg_size);
        tt_trace_d("register, msg->pdata, %p", msg->pdata);
        msg->echo = echo;
        tt_check_break(msg->pdata != tt_null);

        // init subscribe_list
        tt_list_entry_init(&msg->subscribe_list, uspf_actor_t, entry, tt_null); // TODO uspf_actor_t have a little problem

        // lock
        tt_spinlock_enter(&s_lock);
        tt_list_entry_insert_tail(&s_uspf.reg_msg_list, &msg->entry);

        // unlock
        tt_spinlock_leave(&s_lock);

        ok = tt_true;

    } while (0);
    
    return ok;
}

tt_int_t uspf_subscribe(uspf_msg_ref_t msg, uspf_actor_ref_t actor, tt_uint8_t priority, void const *const param)
{
    tt_assert_and_check_abort(msg != tt_null); 
    tt_check_return_val(msg->node_num < USPF_LINK_NAME_MAX, -1);
    tt_assert_and_check_return_val(priority >= 0 && priority < 256, -1);

    tt_check_return_val(actor != tt_null, -1);
    // aviod the same actor subscribe again 
    tt_check_return_val(actor->enable != tt_true, -1);

    // update actor
    actor->priority = priority;
    actor->renewal = tt_false;
    actor->mode = 0; //TODO
    actor->enable = tt_true;
    actor->name = param;

    tt_spinlock_enter(&s_lock);
    tt_list_entry_insert_tail(&msg->subscribe_list, &actor->entry);
    
    tt_spinlock_exit(&s_lock);

    // update 
    msg->priority = actor->priority;
    msg->node_num++;

    return 0;
}

tt_bool_t uspf_reactor_init(uspf_msg_ref_t msg, void *reactor, tt_uint8_t priority, void const *const param)
{
    tt_assert_and_check_return_val(reactor != NULL, tt_false);

    uspf_reactor_ref_t reactor_inst = (uspf_reactor_ref_t)reactor;
    uspf_actor_ref_t actor = &reactor_inst->actor;
    uspf_subscribe(msg, actor, priority, param);

    return tt_true;
}

#if 0
uspf_node_ref_t uspf_subscribe(uspf_msg_ref_t msg, uspf_sync_flag_t flag, tt_void_t (*cb)(tt_void_t* param))
{
    tt_assert_and_check_abort(msg); 
    tt_check_return_val(msg->node_num <= USPF_LINK_NAME_MAX, tt_null);
    
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

    // add node to subscribe_list
    tt_list_entry_insert_tail(&msg->subscribe_list, &node->entry);
    msg->node_num++;

    // unlock
    tt_spinlock_leave(&s_lock);

    return node;
}
#endif

tt_bool_t uspf_unsubscribe(uspf_msg_ref_t msg, uspf_actor_ref_t actor)
{
    tt_assert_and_check_abort(msg); 

    tt_check_return_val(actor != tt_null, -1);
    tt_check_return_val(msg->node_num > 0, -2);

    tt_spinlock_enter(&s_lock);
    tt_list_entry_remove(&msg->subscribe_list, &actor->entry);
    uspf_actor_ref_t actor_head = (uspf_actor_ref_t)tt_list_entry_head(&msg->subscribe_list);
    msg->priority = actor_head->priority;
    msg->node_num--;
    tt_spinlock_exit(&s_lock);

    return 0;
}

#if 0
tt_bool_t uspf_unsubscribe(uspf_msg_ref_t msg, uspf_node_ref_t node)
{
    tt_assert_and_check_return_val(msg && node, tt_false);

    // TODO check if node in list?

    tt_spinlock_enter(&s_lock);

    tt_list_entry_remove(&msg->subscribe_list, &node->entry);

    tt_spinlock_leave(&s_lock);

    tt_trace_d("unsubscribe, free node, %p", node);
    // free node
    if(node) tt_free(node);
    msg->node_num--;

    return tt_true;
}
#endif

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

    msg->published = 1;

    // walk subscribe_list
    tt_for_all(uspf_actor_ref_t, node1, iterator)
    {
        // update flag
        node1->renewal = tt_true;
        // if(node1->event) tt_semaphore_post(node1->event, 1); 
        tt_trace_d("publish, node, %p", node1);
    }

    // unlock
    tt_spinlock_leave(&s_lock);

    // walk subscribe_list, can't be reentrant, also can't put it in lock area
    // tt_for_all(uspf_node_ref_t, node2, iterator)
    // {
    //     if(node2->cb != tt_null) node2->cb(msg->pdata);
    // }

    return tt_true;    
}

#if 0
tt_bool_t uspf_poll(uspf_node_ref_t node)
{
    tt_assert_and_check_return_val(node, tt_false);

    return node->renewal;
}

tt_bool_t uspf_poll_sync(uspf_node_ref_t node, unsigned int timeout)
{
    tt_assert_and_check_return_val(node, tt_false);

    // tt_semaphore_wait(node->event);

    return tt_true;
}

tt_bool_t uspf_copy(uspf_msg_ref_t msg, uspf_node_ref_t node, void* buff)
{
    tt_assert_and_check_return_val(msg && node && buff, tt_false);

    // check msg pdata
    tt_check_return_val(msg->pdata != tt_null, tt_false);
    // check if publish
    tt_check_return_val(msg->published, tt_false);

    tt_spinlock_enter(&s_lock);

    tt_trace_d("copy, msg->pdata, %p", msg->pdata);
    memcpy(buff, msg->pdata, msg->msg_size);
    node->renewal = tt_false;

    tt_spinlock_leave(&s_lock);

    return tt_true;
}
#endif

tt_bool_t uspf_copy_hub(uspf_msg_ref_t msg, tt_void_t* buff)
{
    tt_assert_and_check_return_val(msg && buff, tt_false);

    // check msg pdata
    tt_check_return_val(msg->pdata != tt_null, tt_false);
    // check if publish
    tt_check_return_val(msg->published, tt_false);

    tt_spinlock_enter(&s_lock);
    memcpy(buff, msg->pdata, msg->msg_size);
    tt_spinlock_leave(&s_lock);

    return tt_true;
}

tt_bool_t uspf_node_clear(uspf_actor_ref_t node)
{
    tt_assert_and_check_return_val(node, tt_false);

    tt_spinlock_enter(&s_lock);
    node->renewal = tt_false;
    tt_spinlock_leave(&s_lock);

    return tt_true;
}




