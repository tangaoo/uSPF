/*!The uSPF
 *
 * @Copyright (C) 2019-2021, uSPF
 *
 * @file       main.c
 * @ingroup    uspf
 * @author     tango
 * @date       2021-06-16 
 * @brief      main.c file
 */

#define TT_TRACE_MODULE_NAME    "uspf_example"
#define TT_TRACE_DEBUG          1

/* //////////////////////////////////////////////////////////////////////////////////////
 * includes
 */
#include "ttlib.h"
#include "../uSPF/uSPF.h"

/* //////////////////////////////////////////////////////////////////////////////////////
 * types
 */
typedef struct __demo_data_t
{
    const tt_char_t* name;
    tt_int_t a;
}demo_data_t, *demo_data_ref_t;

/* //////////////////////////////////////////////////////////////////////////////////////
 * globals
 */
USPF_MSG_DEFINE(demo_topic, sizeof(demo_data_t));

/* //////////////////////////////////////////////////////////////////////////////////////
 * declaration
 */
tt_void_t* demo_publish_thread(tt_void_t* arg);
tt_void_t* demo_subscribe_sync_thread(tt_void_t* arg);
tt_void_t* demo_subscribe_async_thread(tt_void_t* arg);

tt_int_t main(tt_void_t)
{
    pthread_t t1, t2, t3;


    // init ttlib
    tt_lib_init(tt_null);

    // init uspf
    uspf_init();

    // register topic
    uspf_register(USPF_MSG_ID(demo_topic), tt_null);    

    pthread_create(&t2, tt_null, demo_subscribe_sync_thread, tt_null);
    pthread_create(&t3, tt_null, demo_subscribe_async_thread, tt_null);
    sleep(1);
    pthread_create(&t1, tt_null, demo_publish_thread, tt_null);

    // join the thread
    pthread_join(t1, tt_null);
    pthread_join(t2, tt_null);
    pthread_join(t3, tt_null);

    // exit uspf
    uspf_exit(); 

    return 0;
}

tt_void_t* demo_publish_thread(tt_void_t* arg)
{
    tt_trace_d("publish thread");

    // get msg data
    demo_data_t data = {"demo data", 8};
    uspf_publish(USPF_MSG_ID(demo_topic), &data);

    return tt_null;
}

tt_void_t* demo_subscribe_async_thread(tt_void_t* arg)
{
    tt_trace_d("async subscribe thread");
    tt_bool_t ok = tt_false;
    // subsrcibe topic
    uspf_node_ref_t node = uspf_subscribe(USPF_MSG_ID(demo_topic), USPF_ASYNC, tt_null);

    do
    {
        ok = uspf_poll(node);
    } while (!ok);

    demo_data_t data;
    if(uspf_copy(USPF_MSG_ID(demo_topic), node, &data))
        tt_trace_d("async, data, %s, %d", data.name, data.a);

    return tt_null;    
}

tt_void_t* demo_subscribe_sync_thread(tt_void_t* arg)
{
    tt_trace_d("sync, subscribe thread");

    // subsrcibe topic
    uspf_node_ref_t node = uspf_subscribe(USPF_MSG_ID(demo_topic), USPF_SYNC, tt_null);

    uspf_poll_sync(node, 0);

    demo_data_t data;
    if(uspf_copy(USPF_MSG_ID(demo_topic), node, &data))
        tt_trace_d("sync data, %s, %d", data.name, data.a);

    return tt_null;    
}
