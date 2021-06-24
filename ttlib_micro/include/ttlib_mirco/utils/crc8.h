/*
 * @Copyright (C) 2019-2021, TTLIB
 * @file       crc8.h
 * @ingroup    utils
 * @author     tango
 * @date       2020-11-19 
 * @brief      crc8.h file
 */

#ifndef TB_HASH_CRC8_H
#define TB_HASH_CRC8_H

/* //////////////////////////////////////////////////////////////////////////////////////
 * includes
 */
#include "prefix.h"

/* //////////////////////////////////////////////////////////////////////////////////////
 * macros
 */

// encode value
#define tt_crc8_make_value(mode, crc, value)       tt_crc8_make(mode, crc, (tb_byte_t const*)&(value), sizeof(value))

/* //////////////////////////////////////////////////////////////////////////////////////
 * extern
 */
__tt_extern_c_enter__

/* //////////////////////////////////////////////////////////////////////////////////////
 * interfaces
 */

/*! make crc8 (ATM)
 *
 * @param data      the input data
 * @param size      the input size
 * @param seed      uses this seed if be non-zero
 *
 * @return          the crc value
 */
tt_uint8_t         tt_crc8_make(tt_byte_t const* data, tt_size_t size, tt_uint8_t seed);

/*! make crc8 (ATM) for cstr
 *
 * @param cstr      the input cstr
 * @param seed      uses this seed if be non-zero
 *
 * @return          the crc value
 */
tt_uint8_t         tt_crc8_make_from_cstr(tt_char_t const* cstr, tt_uint8_t seed);

/* //////////////////////////////////////////////////////////////////////////////////////
 * extern
 */
__tt_extern_c_leave__

#endif

