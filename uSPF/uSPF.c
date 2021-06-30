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

/* //////////////////////////////////////////////////////////////////////////////////////
 * includes
 */

#include "uSPF.h"

/* //////////////////////////////////////////////////////////////////////////////////////
 * globals
 */

// uspf hub list header
static tt_single_list_entry_head_t s_uspf_hub_list; 

// static spinlock
static tt_spinlock_t   lock = TT_SPINLOCK_INITIALIZER;

/* //////////////////////////////////////////////////////////////////////////////////////
 * implementation
 */
tt_bool_t uspf_init(tt_void_t)
{
    // init list header
    tt_single_list_entry_init(&s_uspf_hub_list, uspf_hub_list_t, entry, NULL);

    return tt_true;
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
        hub->echo = echo;
        tt_check_break(hub->pdata != tt_null);

        // init node_list
        tt_single_list_entry_init(&hub->node_list, uspf_node_t, entry, tt_null);

        // lock
        tt_spinlock_enter(&lock);

        uspf_hub_list_ref_t node = (uspf_hub_list_ref_t)tt_malloc(sizeof(uspf_hub_list_t));
        node->hub = hub;
        tt_single_list_entry_insert_tail(&s_uspf_hub_list, &node->entry);

        // unlock
        tt_spinlock_leave(&lock);

        ok = tt_true;

    } while (0);
    
    return ok;
}

uspf_node_ref_t uspf_subscribe(uspf_hub_ref_t hub, uspf_sync_flag_t flag, tt_void_t (*cb)(tt_void_t* param))
{
    tt_assert_and_check_abort(hub); 
    tt_check_return_val(hub->link_num <= USPF_LINK_NAME_MAX, tt_null);
    
    // create node
    uspf_node_ref_t node = (uspf_node_ref_t)tt_malloc(sizeof(uspf_node_t));
    tt_check_return_val(node != tt_null, tt_null);

    // init node
    node->renewal = 0;
    node->event   = event;
    node->cb      = cb;
    node->next    = tt_null;

    // lock
    tt_spinlock_enter(&lock);

    // add node to node_list
    tt_single_list_entry_insert_tail(&hub->node_list, node);
    hub->link_num++;

    // unlock
    tt_spinlock_leave(&lock);

    return node;
}

tt_bool_t uspf_unsubscribe(uspf_hub_ref_t hub, uspf_node_ref_t node)
{
    tt_assert_and_check_return_val(hub && node, tt_false);

    uspf_node_ref_t cur_node = hub->link_head;
    uspf_node_ref_t pre_node = hub->link_head;

    // walk list, find node
    while(cur_node != NULL)
    {
        // find it
        if(cur_node == node) break;

        pre_node = node;
        node = node->next;
    }

    // check if find the node
    if(cur_node == NULL) return USPF_FAILED;

    // delect node in list
    if(cur_node == hub->link_head)    
        hub->link_head = cur_node->next;
    if(cur_node == hub->link_tail)
    {
        if(pre_node) pre_node->next = NULL;
        hub->link_tail = pre_node;
    }
    else
    {
        pre_node->next = cur_node->next;
    }

    // free cur_node
    uspf_free(cur_node);
    hub->link_num++;

    // unlock
    uspf_mutex_unlock(&s_uspf_mutex);

    return USPF_OK;
}

uspf_err_t uspf_publish(uspf_hub_ref_t hub, const void* data)
{
    // check
    uspf_check_abort(hub && data);

    // check hub pdata
    if(hub->pdata == NULL) return USPF_FAILED;

    // lock
    uspf_mutex_lock(&s_uspf_mutex);

    // copy data
    memcpy(hub->pdata, data, hub->msg_size);

    uspf_node_ref_t node = hub->link_head;
    while (node != NULL)
    {
        // updata node flag
        node->renewal = 1;
        if(node->event) uspf_event_send(&node->event);

        node = node->next;
    }
    
    hub->published = 1;

    // unlock
    uspf_mutex_unlock(&s_uspf_mutex);

    node = hub->link_head;
    while (node != NULL)
    {
        if(node->cb != NULL) node->cb(hub->pdata);
        node = node->next;
    }

    return USPF_OK;    
}

uspf_bool_t uspf_poll(uspf_node_ref_t node)
{
    uspf_check_abort(node);
    uspf_bool_t renewal = USPF_FLASE;

    uspf_mutex_lock(&s_uspf_mutex);
    renewal = node->renewal;
    uspf_mutex_unlock(&s_uspf_mutex);

    return renewal;
}

uspf_bool_t uspf_poll_sync(uspf_node_ref_t node, unsigned int timeout)
{
    uspf_check_abort(node && node->event);

    uspf_event_wait(&node->event);

    return USPF_TRUE;
}

uspf_err_t uspf_copy(uspf_hub_ref_t hub, uspf_node_ref_t node, void* buff)
{
    uspf_check_abort(hub && node && buff);

    // check
    if(hub->pdata == NULL) return USPF_FAILED;

    // check if publish
    if(!hub->published) return USPF_FAILED;

    uspf_mutex_lock(&s_uspf_mutex);

    memcpy(buff, hub->pdata, hub->msg_size);
    node->renewal = 0;

    uspf_mutex_unlock(&s_uspf_mutex);

    return USPF_OK;
}

uspf_err_t uspf_copy_hub(uspf_hub_ref_t hub, void* buff)
{
    uspf_check_abort(hub && buff);

    // check
    if(hub->pdata == NULL) return USPF_FAILED;

    // check if publish
    if(!hub->published) return USPF_FAILED;

    uspf_mutex_lock(&s_uspf_mutex);
    memcpy(buff, hub->pdata, hub->msg_size);
    uspf_mutex_unlock(&s_uspf_mutex);

    return USPF_OK;

}

void uspf_node_clear_msg(uspf_node_ref_t node)
{
    uspf_check_abort(node);

    uspf_mutex_lock(&s_uspf_mutex);
    node->renewal = 0;
    uspf_mutex_unlock(&s_uspf_mutex);
}

