/*
 * @Copyright (C) 2019-2021, TTLIB
 * @file       utils.h
 * @ingroup    prefix
 * @author     tango
 * @date       2020-11-19 
 * @brief      utils.h file
 */

#ifndef _TT_PREFIX_UTILS_H
#define _TT_PREFIX_UTILS_H

/* //////////////////////////////////////////////////////////////////////////////////////
 * includes
 */
#include "type.h"
#include "check.h"

/* //////////////////////////////////////////////////////////////////////////////////////
* macros
*/

/// abs
#define tt_abs(x)                       ((x) > 0 ? (x) : -(x)) 

/// max
#define tt_max(x, y)                    ((x) > (y) ? (x) : (y))

/// min
#define tt_min(x, y)                    (((x) < (y))? (x) : (y))

/// max3
#define tt_max3(x, y, z)                (((x) > (y))? (((x) > (z))? (x) : (z)) : (((y) > (z))? (y) : (z)))

/// min3
#define tt_min3(x, y, z)                (((x) < (y))? (((x) < (z))? (x) : (z)) : (((y) < (z))? (y) : (z)))

///num entry of array
#define tt_arrayn(x)                    ((sizeof((x)) / sizeof((x)[0])))

/// ispow2: 1, 2, 4, 8, 16, 32, ...
#define tt_ispow2(x)                    (!((x) & ((x) - 1)) && (x))

/// align2
#define tt_align2(x)                    (((x) + 1) >> 1 << 1)

/// align4
#define tt_align4(x)                    (((x) + 3) >> 2 << 2)

/// align8
#define tt_align8(x)                    (((x) + 7) >> 3 << 3)

/// align
#define tt_align(x, b)                  (((tt_size_t)(x) + ((tt_size_t)(b) - 1)) & ~((tt_size_t)(b) - 1))

/// align u32
#define tt_align_u32(x, b)              (((tt_uint32_t)(x) + ((tt_uint32_t)(b) - 1)) & ~((tt_uint32_t)(b) - 1))

/// align u64
#define tt_align_u64(x, b)              (((tt_uint64_t)(x) + ((tt_uint64_t)(b) - 1)) & ~((tt_uint64_t)(b) - 1))

/// align by pow2
#define tt_align_pow2(x)                (((x) > 1)? (tt_ispow2(x)? (x) : ((tt_size_t)1 << (32 - tt_bits_cl0_u32_be_inline((tt_uint32_t)(x))))) : 1)

/// align by cpu
#ifdef TT_CPU_BIT_64
#   define tt_align_cpu(x)              tt_align8(x)
#else
#   define tt_align_cpu(x)              tt_align4(x)
#endif

/// offsetof
#if defined(TT_COMPILER_IS_GCC)
#   define tt_offsetof(s, m)            (tt_size_t)__builtin_offsetof(s, m)
#else
#   define tt_offsetof(s, m)            (tt_size_t)&(((s const*)0)->m)
#endif

/// container_of  跟据类型为s的结构体成员变量m的地址p，求得结构体首地址
#define tt_container_of(s, m, p)        ((s*)(((tt_byte_t*)(p)) - tt_offsetof(s, m)))

/// memsizeof
#define tt_memsizeof(s, m)              sizeof(((s const*)0)->m)

/// memtailof
#define tt_memtailof(s, m)              (tt_offsetof(s, m) + tt_memsizeof(s, m))

/// memdiffof: lm - rm
#define tt_memdiffof(s, lm, rm)         (tt_memtailof(s, lm) - tt_memtailof(s, rm))

/// check the offset and size of member for struct or union
#define tt_memberof_eq(ls, lm, rs, rm)  ((tt_offsetof(ls, lm) == tt_offsetof(rs, rm)) && (tt_memsizeof(ls, lm) == tt_memsizeof(rs, rm)))

/// swap
#define tt_swap(t, l, r)                do { t __p = (r); (r) = (l); (l) = __p; } while (0)

/// pointer to u8
#define tt_p2u8(x)                      ((tt_uint8_t)(tt_size_t)(x))
#define tt_p2s32(x)                     ((tt_int32_t)(tt_long_t)(x))

/// unsigned integer to pointer
#define tt_u2p(x)                       ((tt_pointer_t)(tt_size_t)(x))

// is digit
#define tt_isdigit(x)                   ((x) > 0x2f && (x) < 0x3a)

// is 0b digit
#define tt_isdigit2(x)                  ((x) == '0' || (x) == '1')

// is 8 digit
#define tt_isdigit8(x)                  (((x) > 0x2f && (x) < 0x38))

// is 10 digit
#define tt_isdigit10(x)                 (tt_isdigit(x))


#endif