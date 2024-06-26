#ifndef EXAMPLE_PUBLISH_H
#define EXAMPLE_PUBLISH_H


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
 * interfaces
 */
tt_void_t* demo_publish_thread(tt_void_t* arg);

#endif