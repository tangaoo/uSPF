/*!The TT Library
 *
 * @Copyright (C) 2019-2021, TTLIB
 *
 * @file       protocol.h
 * @ingroup    utils
 * @author     tango
 * @date       2021-03-11 
 * @brief      protocol.h file
 */

#ifndef TT_UTILS_PROTOCOL_H
#define TT_UTILS_PROTOCOL_H

/* //////////////////////////////////////////////////////////////////////////////////////
 * includes
 */
#include "prefix.h"

/*!  common protocol
 *
 * 
 *   1-byte   1-byte     1-byte   1-byte     4-bytes                  2-bytes crc check
 *     |         |         |        |             |                           | 
 *  +-------+--------+----------+--------+-----------------+--------+---------+--------+
 *  | SYNC  |  SYNC  |   CLASS  |   ID   |    LENGTH       |  DATA  |  CRC_A  |  CRC_B |
 *  | CHAR  |  CHAR  |          |        |  little endian  |        |         |        |
 *  +-------+--------+----------+--------+-----------------+--------+---------+--------+ 
 *                   |                                              | 
 *                   +-----        range for crc check          ----+ 
 * 
 */


#endif