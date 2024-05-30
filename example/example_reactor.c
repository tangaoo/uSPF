
#define TT_TRACE_MODULE_NAME    "uspf_example_reactor"
#define TT_TRACE_MODULE_DEBUG   0


/* //////////////////////////////////////////////////////////////////////////////////////
 * includes
 */
#include "example_reactor.h"
#include "example_publish.h"


/* //////////////////////////////////////////////////////////////////////////////////////
 * define
 */
#define  EXAMPLE_REACTOR_MSG_CNT        3

/* //////////////////////////////////////////////////////////////////////////////////////
 * globals
 */
USPF_MSG_DECLARE(demo_topic1);
USPF_MSG_DECLARE(demo_topic2);
USPF_MSG_DECLARE(demo_topic3);

static uspf_reactor_node_t  s_reactor_node[EXAMPLE_REACTOR_MSG_CNT];
uspf_reactor_t  s_reactor = {0};

/* //////////////////////////////////////////////////////////////////////////////////////
 * declaration
 */
static void example_reactor_handler(uspf_reactor_ref_t reactor, uspf_msg_t const * const msg)
{
    demo_data_ref_t demo_data = tt_null;

    // done
    demo_data = (demo_data_ref_t)msg->pdata;
    tt_trace_i("reactor handler, [actor]%s, [msg]%s, [data]%s,%d", reactor->actor.name, msg->msg_name, demo_data->name, demo_data->a); 
    reactor->actor.renewal = tt_false;

}

tt_bool_t example_reactor_init(tt_uint8_t priority, void const *const param)
{
    s_reactor.msg_handler = example_reactor_handler;

    for(tt_uint32_t i = 0; i < EXAMPLE_REACTOR_MSG_CNT; i++)
    {
        s_reactor_node[i].reactor = &s_reactor;
        s_reactor_node[i].debug = 88;
    }

    tt_trace_d("reactor_node0,%x, reactor,%x, handle,%x", &s_reactor_node[0], s_reactor_node[0].reactor, s_reactor_node[0].reactor->msg_handler);

    uspf_reactor_init(USPF_MSG_ID(demo_topic1), &s_reactor_node[0], priority, param);
    uspf_reactor_init(USPF_MSG_ID(demo_topic2), &s_reactor_node[1], priority, param);

    return tt_true;
}

