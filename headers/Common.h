// ---------------------------------------------------------
//
//  Andrew Conner Skatzes (C) 2025
//
//  BSD-3 Clause license
//
//  Description:
//      Common things we need to make the world go around
//
// ---------------------------------------------------------

#ifndef COMMON_H
#define COMMON_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "config.h"

#if defined(__linux__)

#elif defined(_WIN32)
    #include <windows.h>
    #ifndef sleep
    /* I was told we have to cast to DWORD*/
    #define sleep(x) Sleep((DWORD)1000 * (x))
    #endif 
#elif (__apple__)

#endif

// Heard this has something to do with the audio waves
#if defined(__clang__)
#define PI      3.14159265358979323846

#elif defined(__STDC_IEC_559__) && !defined(__STDC_IEC_559_DOUBLE__)
#define PI      3.14159265358979323846f // <-- legacy support
#endif

typedef int8_t      int8;
typedef int16_t     int16;
typedef int32_t     int32;
typedef int64_t     int64;
typedef uint8_t     uint8;
typedef uint16_t    uint16;
typedef uint32_t    uint32;
typedef uint64_t    uint64;

char* cstrdup(const char* x);

/** 
*@brief Optimized sine function for double values.
*@param x The angle in radians.
*@returns The sine of the angle.
*/
double csin(double x);

/** 
*@brief Optimized sine function for float values.
*@param x The angle in radians.
*@returns The sine of the angle.
*/
float csinf(float x);


/* If we don't have a standard c library*/
#if !defined(HAS_LIBC)

/* Credit to the linux kernel for using code to make the c library*/

#if __has_attribute(__fallthrough__)
    #define fallthrough     __attribute__((__fallthrough__))
#else 
    #define fallthrough     do {} while (0) /* This is how it works behind the scenes?*/
#endif

typedef __builtin_va_list va_list;
#define va_start(v, last)  __builtin_va_start(v, last)
#define va_end(v)       __builtin_va_end(v)
#define va_arg(v, T)    __builtin_va_arg(v, T)
#define va_copy(d, s)   __builtin_va_copy(d, s)

#define ZEROPAD 1
#define SIGN    2
#define PLUS    4
#define SPACE   8
#define LEFT    16
#define SMALL   32
#define SPECIAL 64

#define __do_div(n, base) ({ \
    int __res; \
    __res = ((unsigned long) n) % (unsigned) base; \
    n = ((unsigned long) n) / (unsigned) base; \
    __res; })

#define _U  0x01    // Upper
#define _L  0x02    // Lower
#define _D  0x04    // Digit
#define _C  0x08    // Control chars
#define _P  0x10    // Punctuation/symbols
#define _S  0x20    // White space
#define _X  0x40    // Hex digit
#define _SP 0x80    // Hard space

#if __has_builtin(__builtin_isdigit)
    #define isdigit(c) __builtin_isdigit(c)
#else 

    static inline int isdigit(int c)
    {
        return '0' <= c && c <= '9';
    }

#endif

static int skip_atoi(const char** s);

static char* number(char* string, long number, int base, int size, int precision, int type);

int vsprintf(char* buffer, const char* fmt, va_list args);

int sprintf(char* buffer, const char* fmt, ...);

int printf(const char* fmt, ...);

#endif

#ifdef __cplusplus
}
#endif

#endif