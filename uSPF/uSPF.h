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

#ifndef uSPF_H
#define uSPF_H

/* //////////////////////////////////////////////////////////////////////////////////////
 * includes
 */
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ttlib.h"

/* //////////////////////////////////////////////////////////////////////////////////////
 * macros
 */

// max number of subscrib to one msg 
#define USPF_LINK_NAME_MAX              16

/* //////////////////////////////////////////////////////////////////////////////////////
 * types
 */
typedef enum __uspf_sync_flag_t
{
    USPF_ASYNC      = 0,
    USPF_SYNC       = 1,

}uspf_sync_flag_t;

typedef struct __uspf_node_t
{
    // single list entry
    tt_single_list_entry_t entry;

    // flag
    volatile tt_int_t      renewal;

    // semaphore
    tt_semaphore_ref_t     event;

    // cb
    tt_void_t              (*cb)(tt_void_t* param);

}uspf_node_t, *uspf_node_ref_t;

typedef struct __uspf_hub_t
{
    const tt_char_t*       msg_name;
    const tt_size_t        msg_size;
    tt_void_t*             pdata;
    tt_bool_t              published;
    tt_int_t               (*echo)(tt_void_t* param);
    tt_uint64_t            last_pub_time;
    tt_f32_t               freq;
    uspf_node_ref_t        link_head;
    uspf_node_ref_t        link_tail;
    tt_size_t              link_num;

}uspf_hub_t, *uspf_hub_ref_t; 

typedef struct __uspf_hub_list_t
{
    tt_single_list_entry_t  entry;
    uspf_hub_ref_t          hub;

}uspf_hub_list_t, *uspf_hub_list_ref_t;

/* //////////////////////////////////////////////////////////////////////////////////////
 * helper macros
 */

// uspf msg id, used for Subscribe、Publish and so on
#define USPF_MSG_ID(name)         (&__uspf_##name)

// declare uspf msg 
#define USPF_MSG_DECLARE(name)    extern uspf_hub_t __uspf_##name    

// define uspf msg 
#define USPF_MSG_DEFINE(name, size)     \
    uspf_hub_t __uspf_##name = {        \
            .msg_name        = #name,   \
            .msg_size        = size,    \
            .pdata           = tt_null, \
            .published       = 0,       \
            .echo            = tt_null, \
            .last_pub_time   = 0,       \
            .freq            = 0.0f,    \
            .link_head       = tt_null, \
            .link_tail       = tt_null, \
            .link_num        = 0,       \
    }                                    

__tt_extern_c_enter__

/* //////////////////////////////////////////////////////////////////////////////////////
 * interfaces
 */

/*! init and register uspf msg hub
 *
 * @param hub           the msg hub
 * @param echo          the cb function when need print the msg
 *
 * @return              tt_true or tt_false
 */
tt_bool_t               uspf_register(uspf_hub_ref_t hub, tt_int_t (*echo)(tt_void_t* param));    

/*! subscribe uspf msg
 *
 * @param hub           the msg hub
 * @param event         the event used for sync; NULL for async
 * @param cb            the cb function, It will be call in publish
 *
 * @return              the uspf node, used for poll、coye msg... 
 */
uspf_node_ref_t         uspf_subscribe(uspf_hub_ref_t hub, uspf_sync_flag_t flag, tt_void_t (*cb)(tt_void_t* param));

/*! unsubscribe uspf msg
 *
 * @param hub           the msg hub
 * @param node          the uspf node
 *
 * @return              tt_true or tt_false
 */
tt_bool_t               uspf_unsubscribe(uspf_hub_ref_t hub, uspf_node_ref_t node);

/*! publish data 
 *
 * @param hub           the msg hub
 * @param data          the data
 *
 * @return              tt_true or tt_false
 */
tt_bool_t               uspf_publish(uspf_hub_ref_t hub, const tt_void_t* data);

/*! uspf poll async
 *
 * @param node          the node
 *
 * @return              tt_true or tt_false
 */
tt_bool_t               uspf_poll(uspf_node_ref_t node);

/*! uspf poll sync
 *
 * @param node          the node
 * @param timeout       the time out
 *
 * @return              tt_true or tt_false
 */
tt_bool_t               uspf_poll_sync(uspf_node_ref_t node, tt_uint32_t timeout);

/*! copy data
 *
 * @param hub           the hub
 * @param node          the node
 * @param buff [O]      the buff
 *
 * @return              tt_true or tt_false
 */
tt_bool_t               uspf_copy(uspf_hub_ref_t hub, uspf_node_ref_t node, tt_void_t* buff);

/*! copy data from hub
 *
 * @param hub           the hub
 * @param buff [O]      the buff
 *
 * @return              tt_true or tt_false
 */
tt_bool_t               uspf_copy_hub(uspf_hub_ref_t hub, tt_void_t* buff);

/*! clear node
 *
 * @param node          the node
 *
 * @return              tt_void_t
 */
tt_void_t               uspf_node_clear(uspf_node_ref_t node);    

__tt_extern_c_leave__

#endif