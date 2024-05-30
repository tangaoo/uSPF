#define TT_TRACE_MODULE_NAME    "uspf_example_publish"
#define TT_TRACE_MODULE_DEBUG   1

/* //////////////////////////////////////////////////////////////////////////////////////
 * includes
 */
#include "example_publish.h"



/* //////////////////////////////////////////////////////////////////////////////////////
 * globals
 */
USPF_MSG_DEFINE(demo_topic1, sizeof(demo_data_t), 1);
USPF_MSG_DEFINE(demo_topic2, sizeof(demo_data_t), 2);
USPF_MSG_DEFINE(demo_topic3, sizeof(demo_data_t), 3);

tt_void_t* demo_publish_thread(tt_void_t* arg)
{
    // tt_trace_d("publish thread");

    // get msg data
    demo_data_t data = {"demo data", 0};
    
    while (1)
    {
        tt_trace_d("[demo_topic1] publish %d", data.a);
        uspf_publish(USPF_MSG_ID(demo_topic1), &data);

        tt_trace_d("[demo_topic2] publish %d", data.a);
        uspf_publish(USPF_MSG_ID(demo_topic2), &data);

        data.a++;
        tt_sleep(1);
    }

    return tt_null;
}