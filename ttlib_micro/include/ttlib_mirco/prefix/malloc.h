/*
 * @Copyright (C) 2019-2021, TTLIB
 * @file       malloc.h
 * @ingroup    prefix
 * @author     tango
 * @date       2020-11-19 
 * @brief      malloc.h file
 */
#ifndef TT_PREFIX_MALLOC_H
#define TT_PREFIX_MALLOC_H

/* //////////////////////////////////////////////////////////////////////////////////////
 * includes
 */
#include "keyword.h"
#include "type.h"

#include <stdlib.h>

/* //////////////////////////////////////////////////////////////////////////////////////
 * macros
 */
#define tt_malloc(size)                         malloc(size)
#define tt_malloc0(size)                        calloc(1, size)
#define tt_nalloc(item, size)                   calloc(item, size)
#define tt_nalloc0(item, size)                  calloc(item, size)
#define tt_ralloc(data, size)                   realloc(data, size)
#define tt_free(data)                           free(data) 

#endif