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

#include "example_reactor.h"
#include "example_publish.h"


/* //////////////////////////////////////////////////////////////////////////////////////
 * globals
 */
USPF_MSG_DECLARE(demo_topic);

/* //////////////////////////////////////////////////////////////////////////////////////
 * declaration
 */

tt_void_t* demo_uspf_run_thread(tt_void_t* arg);

tt_int_t main(tt_void_t)
{
    pthread_t t1, t3;

    // init ttlib
    tt_lib_init(tt_null);

    // init uspf
    uspf_init();

    // register topic
    uspf_register(USPF_MSG_ID(demo_topic), tt_null);    

    example_reactor_init(8, "reactor1");

    pthread_create(&t3, tt_null, demo_uspf_run_thread, tt_null);
    sleep(1);
    pthread_create(&t1, tt_null, demo_publish_thread, tt_null);

    // join the thread
    pthread_join(t1, tt_null);
    // pthread_join(t2, tt_null);
    pthread_join(t3, tt_null);

    // exit uspf
    uspf_exit(); 

    return 0;
}



tt_void_t* demo_uspf_run_thread(tt_void_t* arg)
{
    tt_trace_d("demo_uspf_run_thread");

    uspf_run();

    return tt_null;    
}



