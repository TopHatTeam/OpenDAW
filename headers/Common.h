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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if defined(__linux__)

#elif defined(_WIN32)
    #ifndef sleep
    #define sleep(x) Sleep(1000 * (x))
    #endif 
#endif

// Heard this has something to do with the audio waves
#define PI      3.14159265358979323846
#define PI_F    3.14159265358979323846f // <-- legacy support

#ifdef __cplusplus
extern "C" {
#endif

static inline char* cstrdup(const char* x);

static inline double csin(double x);
static inline float csinf(float x);

#ifdef __cplusplus
}
#endif

#endif