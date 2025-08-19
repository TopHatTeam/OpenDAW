// ---------------------------------------------------------
//
//  Andrew Conner Skatzes (C) 2025
//
//  BSD-3 Clause license
//
//  Description:
//      Apple platform specific stuff
//
// ---------------------------------------------------------

#include "headers/AudioError.h"

#if defined(__linux__)

void merror_linux(const char* msg, ...)
{
    char buffer[1024];  // <-- Temporary buffer to hold the formatted message

    va_list args;                                   // <-- Declare a variable to hold the variable arguments
    va_start(args, msg);                            // <-- Initialize 'args' to point to the first argument after 'msg'
    vsnprintf(buffer, sizeof(buffer), msg, args);   // <-- Write formatted string into buffer
    va_end(args);                                   // <-- Clean up the variable argument list

    /* Damn how pissed was I?*/
    FILE* fucking_work = popen("zenity --error --text\"$(cat)\"", "w");

    if (fucking_work)
    {
        fprintf(fucking_work, "%s", buffer);
        pclose(fucking_work);
    }
    else 
    {   
        /* backup just in case this code doesn't work*/
        fprintf(stderr, "ERROR: %s\n", buffer);
    }
}

#elif defined(_WIN32)

void merror_win32(HWND hwnd, const char* title, const char* msg, ...)
{
    char buffer[1024]; // <-- Temporary buffer to hold the formatted message

    va_list args;                                   // <-- Declare a variable to hold the variable arguments
    va_start(args, msg);                            // <-- Initialize 'args' to point to the first argument after 'msg'
    vsnprintf(buffer, sizeof(buffer), msg, args);   // <-- Write formatted string into buffer
    va_end(args);                                   // <-- Clean up the variable argument list

    MessageBox(hwnd, msg, title, MB_OK | MB_ICONERROR); // <-- Show the error message box
}

#endif