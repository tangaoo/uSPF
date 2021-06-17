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

/* //////////////////////////////////////////////////////////////////////////////////////
 * macros
 */
#define	uspf_event_t	sem_t

/* //////////////////////////////////////////////////////////////////////////////////////
 * types
 */
typedef enum __uspf_err_t
{
	USPF_OK			= 0,
	USPF_FAILED 	= -1,

}uspf_err_t;

typedef struct __uspf_node_t
{
	// flag
	volatile int  renewal;

	// semaphore
	uspf_event_t  envet;

	// cb
	void 		  (*cb)(void* param);

	// next node
	struct __uspf_node_t* next;

}uspf_node_t, *uspf_node_ref_t;

typedef struct __uspf_hub_t
{
	const char*		msg_name;
	const int 		msg_size;
	void* 			pdata;
	int				published;
	int 			(*echo)(void* param);
	int				last_pub_time;
	float			freq;
	uspf_node_ref_t	link_head;
	uspf_node_ref_t	link_tail;
	int 			link_num;

}uspf_hub_t, *uspf_hub_ref_t; 

typedef struct __uspf_hub_list_t
{
	uspf_hub_ref_t 	hub;
	struct __uspf_hub_list_t* next;
}uspf_hub_list_t, *uspf_hub_list_ref_t;

/* //////////////////////////////////////////////////////////////////////////////////////
 * helper macros
 */

// uspf msg id, used for Subscribe、Publish and so on
#define USPF_MSG_ID(name)		(&__uspf_##name)

// declare uspf msg 
#define USPF_MSG_DECLARE(name)	extern uspf_hub_t __uspf_##name	

// define uspf msg 
#define USPF_MSG_DEFINE(name, size)     \
	uspf_hub_t __uspf_##name = {    	\
			.msg_name	   = name,		\
			.msg_size	   = size,		\
			.pdata		   = NULL,		\
			.published     = 0, 		\
			.echo		   = NULL, 		\
			.last_pub_time = 0,			\
			.freq		   = 0.0f,		\
			.link_head	   = NULL,		\
			.link_tail	   = NULL,		\
			.link_num	   = 0,			\
	}									

#ifdef __cplusplus
extern "C" {
#endi

/* //////////////////////////////////////////////////////////////////////////////////////
 * interfaces
 */

/*! register uspf msg hub
 *
 * @param hub           the msg hub
 * @param echo          the cb function when need print the msg
 *
 * @return              USPF_OK or USPF_FAILED
 */
uspf_err_t				uspf_register(uspf_hub_ref_t hub, int (*echo)(void* param));	

/*! subscribe uspf msg
 *
 * @param hub           the msg hub
 * @param event         the event used for sync; NULL for async
 * @param cb            the cb function, It will be call in publish
 *
 * @return              the uspf node, used for poll、coye msg... 
 */
uspf_node_ref_t			uspf_subscribe(uspf_hub_ref_t hub, uspf_event_t event, void (*cb)(void* param));

/*! unsubscribe uspf msg
 *
 * @param a             brief
 *
 * @return              tt_void_t
 */
uspf_node_ref_t			uspf_unsubscribe(uspf_hub_ref_t hub, uspf_node_ref_t node);

#ifdef __cplusplus
}
#endi

#endif