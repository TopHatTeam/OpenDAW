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

#include "headers/vst.h"

#if defined(__linux__)

#elif defined(_WIN32)

    WIN32_FIND_DATA     vstfile;
    HANDLE              hFind;

    /* Placeholder function for getting VSTs using Windows' API*/
    int FindVSTs(WIN32_FIND_DATA file, HANDLE hFind)
    {
        hFind = FindFirstFile("C:\\Program Files\\VSTPlugins\\*.dll", &file);

        if (hFind == INVALID_HANDLE_VALUE)
        {
            printf("No VSTs found.\n");
            return 1;
        }

        do 
        {
            printf("Found VST: %s\n", file.cFileName);
        } while (FindNextFile(hFind, &file) != 0);

        FindClose(hFind);
        return 0;
    }

#elif defined(__apple__)

#endif