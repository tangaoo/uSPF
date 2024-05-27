#define TT_TRACE_MODULE_NAME    "uspf_example_publish"
#define TT_TRACE_MODULE_DEBUG   0

/* //////////////////////////////////////////////////////////////////////////////////////
 * includes
 */
#include "example_publish.h"



/* //////////////////////////////////////////////////////////////////////////////////////
 * globals
 */
USPF_MSG_DEFINE(demo_topic, sizeof(demo_data_t));

tt_void_t* demo_publish_thread(tt_void_t* arg)
{
    tt_trace_d("publish thread");

    // get msg data
    demo_data_t data = {"demo data", 0};
    
    while (1)
    {
        uspf_publish(USPF_MSG_ID(demo_topic), &data);
        data.a++;
        tt_sleep(1);
    }

    return tt_null;
}