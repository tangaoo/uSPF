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
	const char* name;
	int a;
}demo_data_t, *demo_data_ref_t;

/* //////////////////////////////////////////////////////////////////////////////////////
 * globals
 */
USPF_MSG_DEFINE(demo_topic, sizeof(demo_data_t));

/* //////////////////////////////////////////////////////////////////////////////////////
 * declaration
 */
void* demo_publish_thread(void* arg);
void* demo_subscribe_thread(void* arg);

int main(void)
{
	pthread_t t1, t2;

	tt_lib_init(tt_null);

	tt_trace_i("ttlib");

	pthread_create(&t2, NULL, demo_subscribe_thread, NULL);
	sleep(1);
	pthread_create(&t1, NULL, demo_publish_thread, NULL);

	// join the thread
	pthread_join(t1, NULL);
	pthread_join(t2, NULL);

	return 0;
}

void* demo_publish_thread(void* arg)
{
	printf("publish thread\n");
	// register topic
	uspf_register(USPF_MSG_ID(demo_topic), NULL);	

	// get msg data
	demo_data_t data = {"demo data", 8};
	uspf_publish(USPF_MSG_ID(demo_topic), &data);

	return NULL;
}

void* demo_subscribe_thread(void* arg)
{
	printf("subscribe thread\n");
	uspf_bool_t ok = USPF_FLASE;
	// subsrcibe topic
	uspf_node_ref_t node = uspf_subscribe(USPF_MSG_ID(demo_topic), 0, NULL);

	do
	{
		ok = uspf_poll(node);
	} while (!ok);

	demo_data_t data;
	uspf_copy(USPF_MSG_ID(demo_topic), node, &data);
	printf("data, %s, %d \n", data.name, data.a);

	return NULL;	
}