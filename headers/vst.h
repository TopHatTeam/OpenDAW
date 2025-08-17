// ---------------------------------------------------------
//
//  Andrew Conner Skatzes (C) 2025
//
//  BSD-3 Clause license
//  Created by Andrew Skatzes on 8/16/25.
//  vst.h
//
//  Description:
//      VST functionality
//
// ---------------------------------------------------------

#ifndef VST_H
#define VST_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>

#if defined(__linux__)
    #include <unistd.h>
#elif defined(_WIN32)
    #include <windows.h>
    
    extern WIN32_FIND_DATA  vstfile;
    extern HANDLE           hFind; 

    int FindVSTs(WIN32_FIND_DATA file, HANDLE hFind);

#elif defined(__apple__)

#endif



#ifdef __cplusplus
}
#endif

#endif