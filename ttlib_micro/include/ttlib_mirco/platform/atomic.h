/*!The TT Library
 *
 * @Copyright (C) 2019-2021, TTLIB
 *
 * @file       atomic.h
 * @ingroup    atomic
 * @author     tango
 * @date       2021-06-22 
 * @brief      atomic.h file
 */
#ifndef TT_PLATFORM_COMPILER_LIBC_ATOMIC_H
#define TT_PLATFORM_COMPILER_LIBC_ATOMIC_H

/* //////////////////////////////////////////////////////////////////////////////////////
 * includes
 */
#include "prefix.h"
#include <stdatomic.h>

/* //////////////////////////////////////////////////////////////////////////////////////
 * macros
 */

#define TT_ATOMIC_RELAXED                               memory_order_relaxed
#define TT_ATOMIC_CONSUME                               memory_order_consume
#define TT_ATOMIC_ACQUIRE                               memory_order_acquire
#define TT_ATOMIC_RELEASE                               memory_order_release
#define TT_ATOMIC_ACQ_REL                               memory_order_acq_rel
#define TT_ATOMIC_SEQ_CST                               memory_order_seq_cst

#define tt_memory_barrier                               atomic_thread_fence(memory_order_seq_cst)

#define TT_ATOMIC_FLAG_INIT                             ATOMIC_FLAG_INIT

// test and set
#define tt_atomic_flag_test_and_set_explicit(a, mode)   atomic_flag_test_and_set_explicit(a, mode)
#define tt_atomic_flag_test_and_set                     atomic_flag_test_and_set(a)

// test
#ifdef  atomic_flag_test_explicit
#   define tt_atomic_flag_test_explicit(a, mode)        atomic_flag_test_explicit(a, mode)
#else
#   define tt_atomic_flag_test_explicit(a, mode)        tt_atomic_flag_test_explicit_libc(a, mode)
#endif
#define tt_atomic_flag_test(a)                          tt_atomic_flag_test_explicit(a, memory_order_seq_cst)
#define tt_atomic_flag_test_noatomic(a)                 tt_atomic_flag_test_noatomic_libc(a)

// clear
#define tt_atomic_flag_clear_explicit(a, mode)          atomic_flag_clear_explicit(a, mode)
#define tt_atomic_flag_clear(a)                         atomic_flag_clear(a)

/* //////////////////////////////////////////////////////////////////////////////////////
 * pravite implementation
 */
static __tt_inline__ tt_bool_t tt_atomic_flag_test_explicit_libc(tt_atomic_flag_t* a, tt_init_t mode)
{
    tt_assert(a);
    tt_assert_static(sizeof(tt_atomic_flag_t) == sizeof(unsigned char));
    
    return (tt_bool_t)atomic_load_explicit((__tt_volatite__ _Atomic unsigned char*)a, mode);
}

static __tt_inline__ tt_bool_t tt_atomic_flag_test_noatomic_libc(tt_atomic_flag_t* a)
{
    tt_assert(a);
    tt_assert_static(sizeof(tt_atomic_flag_t) == sizeof(unsigned char));

    return (tt_bool_t)*((__tt_volatile__ unsigned char*)a);
}

#endif