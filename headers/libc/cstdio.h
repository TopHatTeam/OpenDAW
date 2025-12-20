// ---------------------------------------------------------
//
//  OpenDAW
//
//  Andrew Conner Skatzes (C) 2025
//
//  BSD-3 Clause license
//
//  Description:
//      C standard output for users without libc
//
// ---------------------------------------------------------

#ifndef STDIO_H
#define STDIO_H

#include <stdio.h>
#include <stdarg.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef NULL
#ifdef __cplusplus
#define NULL 0 
#else
#define NULL ((void*)0)
#endif
#endif

#if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
#define RESTRICT restrict 
#else 
#define RESTRICT
#endif

int print(const char* RESTRICT msg, ...);

#ifdef __cplusplus
}
#endif


#endif