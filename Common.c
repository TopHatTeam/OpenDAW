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