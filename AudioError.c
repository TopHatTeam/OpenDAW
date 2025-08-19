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
    char command[1200]; // <-- holds the zenity command

    va_list args;                                   // <-- Declare a variable to hold the variable arguments
    va_start(args, msg);                            // <-- Initialize 'args' to point to the first argument after 'msg'
    vsnprintf(buffer, sizeof(buffer), msg, args);   // <-- Write formatted string into buffer
    va_end(args);                                   // <-- Clean up the variable argument list

    snprintf(command, sizeof(command), "zenity --error --text='%s'", buffer);
    
    system(command);
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