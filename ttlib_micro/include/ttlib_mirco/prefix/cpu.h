/*
 * @Copyright (C) 2019-2021, TTLIB
 * @file       cpu.h
 * @ingroup    prefix
 * @author     tango
 * @date       2020-11-19 
 * @brief      cpu.h file
 */

#ifndef TT_PREFIC_CUP_H
#define TT_PREFIC_CUP_H

/* //////////////////////////////////////////////////////////////////////////////////////
 * macros
 */

// check 64-bits
#if defined(__LP64__) \
    || defined(__64BIT__) \
    || defined(_LP64) \
    || defined(__x86_64) \
    || defined(__x86_64__) \
    || defined(__amd64) \
    || defined(__amd64__) \
    || defined(__arm64) \
    || defined(__arm64__) \
    || defined(__sparc64__) \
    || defined(__PPC64__) \
    || defined(__ppc64__) \
    || defined(__powerpc64__) \
    || defined(_M_X64) \
    || defined(_M_AMD64) \
    || defined(_M_IA64) \
    || (defined(__WORDSIZE) && (__WORDSIZE == 64)) \
    || defined(TCC_TARGET_X86_64)
#   define TT_CPU_BIT_64
#   define TT_CPU_SHIFT        6
#   define TT_CPU_BITSIZE      64
#   define TT_CPU_BITBYTE      8
#else // 32bit
#   define TT_CPU_BIT_32
#   define TT_CPU_SHIFT        5
#   define TT_CPU_BITSIZE      32
#   define TT_CPU_BITBYTE      4
#endif

#endif

