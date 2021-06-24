/*
 * @Copyright (C) 2019-2021, TTLIB
 * @file       bit.h
 * @ingroup    utils
 * @author     tango
 * @date       2020-11-19 
 * @brief      bit.h file
 */

#ifndef TT_UTILS_BIT_H
#define TT_UTILS_BIT_H

/* //////////////////////////////////////////////////////////////////////////////////////
 * includes
 */
#include "prefix.h"

/* //////////////////////////////////////////////////////////////////////////////////////
 * macros
 */

// val=target variable, pos=bit number to act upon 0-n
#define tt_bits_set(val, pos)                ((val) |= (1ULL<<(pos)))
#define tt_bits_clear(val, pos)              ((val) &= ~(1ULL<<(pos)))
#define tt_bits_flip(val, pos)               ((val) ^= (1ULL<<(pos)))
#define tt_bits_check(val, pos)              (!!((val) & (1ULL<<(pos))))  // '!!' to make sure this returns 0 or 1

// x=target variable, y=mask 
#define tt_bitmask_set(val, mask)            ((val) |= (mask))
#define tt_bitmask_clear(val, mask)          ((val) &= (~(mask)))
#define tt_bitmask_flip(val, mask)           ((val) ^= (mask))
#define tt_bitmask_check_all(val, mask)      (!(~(val) & (mask)))
#define tt_bitmask_check_any(val, mask)      ((val) & (mask))


// swap
#ifndef tt_bits_swap_u16
#   define tt_bits_swap_u16(x)          tt_bits_swap_u16_inline((tt_uint16_t)(x))
#endif
#ifndef tt_bits_swap_u32
#   define tt_bits_swap_u32(x)          tt_bits_swap_u32_inline((tt_uint32_t)(x))
#endif

/* //////////////////////////////////////////////////////////////////////////////////////
 * cl0
 */
static __tt_inline__ tt_size_t tt_bits_cl0_u32_be_inline(tt_uint32_t x)
{
    tt_check_return_val(x, 32);

    tt_size_t n = 31;
    if (x & 0xffff0000) { n -= 16;  x >>= 16;   }
    if (x & 0xff00)     { n -= 8;   x >>= 8;    }
    if (x & 0xf0)       { n -= 4;   x >>= 4;    }
    if (x & 0xc)        { n -= 2;   x >>= 2;    }
    if (x & 0x2)        { n--;                  }

    return n;
}
static __tt_inline__ tt_size_t tt_bits_cl0_u32_le_inline(tt_uint32_t x)
{
    tt_check_return_val(x, 32);

    tt_size_t n = 31;
    if (x & 0x0000ffff) { n -= 16;  } else x >>= 16;
    if (x & 0x00ff)     { n -= 8;   } else x >>= 8;
    if (x & 0x0f)       { n -= 4;   } else x >>= 4;
    if (x & 0x3)        { n -= 2;   } else x >>= 2;
    if (x & 0x1)        { n--;      }

    return n;
}
static __tt_inline__ tt_size_t tt_bits_cl0_u64_be_inline(tt_uint64_t x)
{
    tt_check_return_val(x, 64);

    tt_size_t n = tt_bits_cl0_u32_be_inline((tt_uint32_t)(x >> 32));
    if (n == 32) n += tt_bits_cl0_u32_be_inline((tt_uint32_t)x);

    return n;
}
static __tt_inline__ tt_size_t tt_bits_cl0_u64_le_inline(tt_uint64_t x)
{
    tt_check_return_val(x, 64);

    tt_size_t n = tt_bits_cl0_u32_le_inline((tt_uint32_t)x);
    if (n == 32) n += tt_bits_cl0_u32_le_inline((tt_uint32_t)(x >> 32));

    return n;
}

#if (TT_CPU_BITSIZE == 32)
#   define tt_bits_fb0_le(x)   tt_bits_cl0_u32_le_inline(x)
#else
#   define tt_bits_fb0_le(x)   tt_bits_cl0_u64_le_inline(x)
#endif

/* //////////////////////////////////////////////////////////////////////////////////////
 * swap
 */

// swap
static __tt_inline__ tt_uint16_t tt_bits_swap_u16_inline(tt_uint16_t x)
{
    x = (x >> 8) | (x << 8);
    return x;
}

static __tt_inline__ tt_uint32_t tt_bits_swap_u24_inline(tt_uint32_t x)
{
    return (x >> 16) | (x & 0x0000ff00) | (x << 16);
}

static __tt_inline__ tt_uint32_t tt_bits_swap_u32_inline(tt_uint32_t x)
{
    x = ((x << 8) & 0xff00ff00) | ((x >> 8) & 0x00ff00ff);
    x = (x >> 16) | (x << 16);
    return x;
}

static __tt_inline__ tt_hize_t tt_bits_swap_u64_inline(tt_hize_t x)
{
    union
    {
        tt_hize_t   u64;
        tt_uint32_t u32[2];

    } w, r;

    w.u64 = x;

    r.u32[0] = tt_bits_swap_u32(w.u32[1]);
    r.u32[1] = tt_bits_swap_u32(w.u32[0]);

    return r.u64;
}

#ifdef TT_WORDS_BIGENDIAN
#   define tt_bits_be_to_ne_u16(x)      ((tt_uint16_t)(x))
#   define tt_bits_le_to_ne_u16(x)      tt_bits_swap_u16(x)
#else
#   define tt_bits_be_to_ne_u16(x)      tt_bits_swap_u16(x)
#   define tt_bits_le_to_ne_u16(x)      ((tt_uint16_t)(x))
#endif

#define tt_bits_ne_to_be_u16(x)         tt_bits_be_to_ne_u16(x)
#define tt_bits_ne_to_le_u16(x)         tt_bits_le_to_ne_u16(x)





#endif