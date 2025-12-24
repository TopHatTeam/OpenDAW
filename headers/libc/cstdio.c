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

#include "cstdio.h"

int print(const char* RESTRICT fmt, ...)
{
    int result;
    va_list args;

    va_start(args, fmt);
    result = vfprintf(stdout, fmt, args);
    va_end(args);

    return (result);
}