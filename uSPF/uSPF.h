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

#define USPF_ACTOR_CAST(cast)           ((uspf_actor_node_ref_t)(cast))
#define USPF_REACTOR_CAST(cast)         ((uspf_reactor_node_ref_t)(cast))

/* //////////////////////////////////////////////////////////////////////////////////////
 * types
 */
typedef enum __uspf_sync_flag_t
{
    USPF_ASYNC      = 0,
    USPF_SYNC       = 1,

}uspf_sync_flag_t;

typedef struct __uspf_msg_t
{
    tt_list_entry_t        entry;

    const tt_char_t*       msg_name;
    const tt_size_t        msg_size;
    tt_void_t*             pdata;
    tt_bool_t              published;
    tt_int_t               (*echo)(tt_void_t* param);
    tt_uint64_t            last_pub_time;
    tt_f32_t               freq;
    tt_uint32_t            priority;      // 
    tt_bool_t              enable;       
    tt_size_t              node_num;

    // list header of subscribe 
    tt_list_entry_head_t   subscribe_list; 

}uspf_msg_t, *uspf_msg_ref_t; 

typedef struct __uspf_actor_t
{
    const tt_char_t*       name;
    tt_uint32_t            priority;
    tt_uint32_t            mode;
    tt_bool_t              enable;
    volatile tt_bool_t     renewal;
}uspf_actor_t, *uspf_actor_ref_t;

typedef struct __uspf_actor_node_t
{
    tt_list_entry_t        entry;
    uspf_actor_ref_t       actor;
}uspf_actor_node_t, *uspf_actor_node_ref_t;

struct __uspf_reactor_t;
typedef void (* uspf_msg_handler)(struct __uspf_reactor_t *const reactor, uspf_msg_t const * const msg);
typedef struct __uspf_reactor_t
{
    uspf_actor_t           actor;
    uspf_msg_handler       msg_handler;
}uspf_reactor_t, *uspf_reactor_ref_t;

typedef struct __uspf_reactor_node_t
{
    tt_list_entry_t        entry;
    uspf_reactor_ref_t     reactor;
    tt_uint_t              debug;

}uspf_reactor_node_t, *uspf_reactor_node_ref_t;

typedef struct __uspf_t
{
    tt_bool_t              enable;
    tt_bool_t              running;              
    tt_bool_t              have_init;              

    tt_list_entry_head_t   reg_msg_list;     // message list have register to uspf
    tt_list_entry_head_t   pub_msg_list;     // message list have publish

}uspf_t, *uspf_ref_t;

/* //////////////////////////////////////////////////////////////////////////////////////
 * helper macros
 */

// uspf msg id, used for Subscribe、Publish and so on
#define USPF_MSG_ID(name)         (&__uspf_##name)

// declare uspf msg 
#define USPF_MSG_DECLARE(name)    extern uspf_msg_t __uspf_##name    

// define uspf msg 
#define USPF_MSG_DEFINE(name, size, prior)     \
    tt_uint8_t __uspf_data_##name[size];\
    uspf_msg_t __uspf_##name = {        \
            .msg_name        = #name,   \
            .msg_size        = size,    \
            .pdata           =  __uspf_data_##name, \
            .published       = 0,       \
            .echo            = tt_null, \
            .last_pub_time   = 0,       \
            .freq            = 0.0f,    \
            .node_num        = 0,       \
            .priority        = prior,\
            .enable          = tt_false\
    }                                    

__tt_extern_c_enter__

/* //////////////////////////////////////////////////////////////////////////////////////
 * interfaces
 */

/*! uspf init 
 *
 * @return              tt_true or tt_false
 */
tt_bool_t               uspf_init(tt_void_t);

/*! uspf exit 
 *
 * @return              tt_void_t
 */
tt_void_t               uspf_exit(tt_void_t);

/*! uspf run 
 *
 * @return              tt_void_t
 */
tt_void_t               uspf_run(tt_void_t);

/*! uspf start 
 *
 * @return              tt_void_t
 */
tt_void_t               uspf_start(tt_void_t);

/*! reactor init
 *
 * @param reactor       the reactor
 * @param priority      the reactor's priority
 * @param param         the parameter
 *
 * @return              tt_true or tt_false
 */
tt_bool_t               uspf_reactor_init(uspf_msg_ref_t msg, void *reactor_node, tt_uint8_t priority, void const *const param);

/*! init and register uspf msg msg
 *
 * @param msg           the msg msg
 * @param echo          the cb function when need print the msg
 *
 * @return              tt_true or tt_false
 */
tt_bool_t               uspf_register(uspf_msg_ref_t msg, tt_int_t (*echo)(tt_void_t* param));    


/*! unsubscribe uspf msg
 *
 * @param msg           the msg msg
 * @param actor         the uspf actor
 *
 * @return              tt_true or tt_false
 */
tt_bool_t               uspf_unsubscribe(uspf_msg_ref_t msg, uspf_actor_node_ref_t actor);

/*! publish data 
 *
 * @param msg           the msg msg
 * @param data          the data
 *
 * @return              tt_true or tt_false
 */
tt_bool_t               uspf_publish(uspf_msg_ref_t msg, const tt_void_t* data);


__tt_extern_c_leave__

#endif
