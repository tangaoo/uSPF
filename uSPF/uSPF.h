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
#include <pthread.h>
#include <semaphore.h>
#include <string.h>

/* //////////////////////////////////////////////////////////////////////////////////////
 * macros
 */

// event hander port
#define uspf_event_t                    sem_t
#define uspf_event_init(event, val)     sem_init(event, 0, val)
#define uspf_event_send(event)          sem_post(event)
#define uspf_event_wait(event)          sem_wait(event)
#define uspf_event_destory(event)       sem_destory(event)

// event spinlock port
#define uspf_mutex_t                    pthread_mutex_t
#define uspf_mutex_lock(lock)           pthread_mutex_lock(lock)
#define uspf_mutex_unlock(lock)         pthread_mutex_unlock(lock)

// malloc
#define uspf_malloc(size)               malloc(size)
#define uspf_free(ptr)                  free(ptr)

#define uspf_check_abort(x)             do { if (!(x)) {*(volatile int*)0 = 0;}} while (0)

// max number of subscrib to one msg 
#define USPF_LINK_NAME_MAX              16

/* //////////////////////////////////////////////////////////////////////////////////////
 * types
 */
typedef enum __uspf_err_t
{
    USPF_OK         = 0,
    USPF_FAILED     = -1,

}uspf_err_t;

typedef enum __uspf_bool_t
{
    USPF_FLASE      = 0,
    USPF_TRUE       = 1,

}uspf_bool_t;

typedef struct __uspf_node_t
{
    // flag
    volatile int    renewal;

    // semaphore
    uspf_event_t    event;

    // cb
    void            (*cb)(void* param);

    // next node
    struct __uspf_node_t* next;

}uspf_node_t, *uspf_node_ref_t;

typedef struct __uspf_hub_t
{
    const char*     msg_name;
    const int       msg_size;
    void*           pdata;
    int             published;
    int             (*echo)(void* param);
    int             last_pub_time;
    float           freq;
    uspf_node_ref_t link_head;
    uspf_node_ref_t link_tail;
    int             link_num;

}uspf_hub_t, *uspf_hub_ref_t; 

typedef struct __uspf_hub_list_t
{
    uspf_hub_ref_t  hub;
    struct __uspf_hub_list_t* next;

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
            .pdata           = NULL,    \
            .published       = 0,       \
            .echo            = NULL,    \
            .last_pub_time   = 0,       \
            .freq            = 0.0f,    \
            .link_head       = NULL,    \
            .link_tail       = NULL,    \
            .link_num        = 0,       \
    }                                    

#ifdef __cplusplus
extern "C" {
#endif

/* //////////////////////////////////////////////////////////////////////////////////////
 * interfaces
 */

/*! init and register uspf msg hub
 *
 * @param hub           the msg hub
 * @param echo          the cb function when need print the msg
 *
 * @return              USPF_OK or USPF_FAILED
 */
uspf_err_t              uspf_register(uspf_hub_ref_t hub, int (*echo)(void* param));    

/*! subscribe uspf msg
 *
 * @param hub           the msg hub
 * @param event         the event used for sync; NULL for async
 * @param cb            the cb function, It will be call in publish
 *
 * @return              the uspf node, used for poll、coye msg... 
 */
uspf_node_ref_t         uspf_subscribe(uspf_hub_ref_t hub, uspf_event_t event, void (*cb)(void* param));

/*! unsubscribe uspf msg
 *
 * @param hub           the msg hub
 * @param node          the uspf node
 *
 * @return              USPF_OK or USPF_FAILED
 */
uspf_err_t              uspf_unsubscribe(uspf_hub_ref_t hub, uspf_node_ref_t node);

/*! publish data 
 *
 * @param hub           the msg hub
 * @param data          the data
 *
 * @return              USPF_OK or USPF_FAILED
 */
uspf_err_t              uspf_publish(uspf_hub_ref_t hub, const void* data);

/*! uspf poll async
 *
 * @param node          the node
 *
 * @return              USPF_TRUE, or USPF_FALSE 
 */
uspf_bool_t             uspf_poll(uspf_node_ref_t node);

/*! uspf poll sync
 *
 * @param node          the node
 * @param timeout       the time out
 *
 * @return              USPF_TRUE, or USPF_FALSE 
 */
uspf_bool_t             uspf_poll_sync(uspf_node_ref_t node, unsigned int timeout);

/*! copy data
 *
 * @param hub           the hub
 * @param node          the node
 * @param buff [O]      the buff
 *
 * @return              USPF_OK or USPF_FAILED
 */
uspf_err_t              uspf_copy(uspf_hub_ref_t hub, uspf_node_ref_t node, void* buff);

/*! copy data from hub
 *
 * @param hub           the hub
 * @param buff [O]      the buff
 *
 * @return              USPF_OK or USPF_FAILED
 */
uspf_err_t              uspf_copy_hub(uspf_hub_ref_t hub, void* buff);

/*! clear node
 *
 * @param node          the node
 *
 * @return              tt_void_t
 */
void                    uspf_node_clear(uspf_node_ref_t node);    


#ifdef __cplusplus
}
#endif

#endif