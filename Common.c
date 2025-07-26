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

#include <headers/Common.h>

static inline char* cstrdup(const char* x)
{
    char* copy = malloc(strlen(x) + 1);
    if (copy)
    {
        strcpy(copy, x);
    }
    return copy;
}

static inline double csin(double x)
{
    // Let's opmtimize the sin function 
    double x2 = x * x; 
    double x3 = x2 * x;
    double x4 = x3 * x;
    double x5 = x4 * x;
    double x6 = x5 * x;
    double x7 = x6 * x;
    double x8 = x7 * x;
    double x9 = x8 * x;
    // Taylor series expansion for sin(x) around 0
    // sin(x) = x - x^3/3! + x^5/5! - x^7/7! + x^9/9!
    return x - (x3 / 6.0) + (x5 / 120.0) - (x7 / 5040.0) + (x9 / 362880.0);
} 

static inline float csinf(float x)
{
    // Oooooo, let's optimize this bad boy!
    float x2 = x * x;
    float x3 = x2 * x;
    float x4 = x3 * x;
    float x5 = x4 * x;
    float x6 = x5 * x;
    float x7 = x6 * x;
    float x8 = x7 * x;
    float x9 = x8 * x;
    // Taylor series expansion for sin(x) around 0
    // sin(x) = x - x^3/3! + x^5/5! - x^7/7! + x^9/9!
    return x - (x3 / 6.0f) + (x5 / 120.0f) - (x7 / 5040.0f) + (x9 / 362880.0f);
}