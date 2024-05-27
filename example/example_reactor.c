
#define TT_TRACE_MODULE_NAME    "uspf_example_reactor"
#define TT_TRACE_MODULE_DEBUG   0


/* //////////////////////////////////////////////////////////////////////////////////////
 * includes
 */
#include "example_reactor.h"
#include "example_publish.h"

/* //////////////////////////////////////////////////////////////////////////////////////
 * globals
 */
USPF_MSG_DECLARE(demo_topic);

static uspf_reactor_t  s_reactor;


/* //////////////////////////////////////////////////////////////////////////////////////
 * declaration
 */
static void example_reactor_handler(uspf_reactor_ref_t reactor, uspf_msg_t const * const msg)
{
    demo_data_ref_t demo_data = tt_null;

    demo_data = (demo_data_ref_t)msg->pdata;
    tt_trace_i("reactor handler, [actor]%s, [msg]%s, [data]%s,%d", reactor->actor.name, msg->msg_name, demo_data->name, demo_data->a); 
}

tt_bool_t example_reactor_init(tt_uint8_t priority, void const *const param)
{
    s_reactor.msg_handler = example_reactor_handler;
    return uspf_reactor_init(USPF_MSG_ID(demo_topic), &s_reactor, priority, param);
}

