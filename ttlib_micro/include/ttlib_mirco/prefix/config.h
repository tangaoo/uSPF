/*
 * @Copyright (C) 2019-2021, TTLIB
 * @file       config.h
 * @ingroup    prefix
 * @author     tango
 * @date       2020-11-19 
 * @brief      config.h file
 */

#ifndef TT_PREFIC_CONFIG_H
#define TT_PREFIC_CONFIG_H

/* //////////////////////////////////////////////////////////////////////////////////////
 * includes
 */
#include "compiler.h"
#include "cpu.h"

/* //////////////////////////////////////////////////////////////////////////////////////
 * macros
 */

/// c++
#ifdef __cplusplus
#undef __cplusplus
#endif

/// debug
#define __tt_debug__           1

/// endian
//#define TT_WORD_BIGENDIAN
#define TT_WORD_LITTLEENDIAN


#endif