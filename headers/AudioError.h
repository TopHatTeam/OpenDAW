// ---------------------------------------------------------
//
//  Andrew Conner Skatzes (C) 2025
//
//  BSD-3 Clause license
//
//  Description:
//      Audio Core engine for the error handling
//
// ---------------------------------------------------------

#include <gtk/gtk.h>
#include <stdio.h>      // for vsnprintf, fprintf, printf
#include <stdarg.h>     // for va_list, va_start, va_end

#if defined(_WIN32)
#include <windows.h>    // for HWND, MessageBox
#endif

#ifndef AUDIOERROR_H
#define AUDIOERROR_H

#ifdef __cplusplus
extern "C" {
#endif

void merror(GtkWindow* parent, const char* msg);

#if defined(_WIN32)

/*
*@brief Displays an error message for the Windows platform.
*@param hwnd The handle to the parent window.
*@param title The title of the error message box.
*@param msg The error message to display, formatted with printf-style syntax.
*@param ... Additional arguments for formatting the message.
*@note This function uses a 1024-byte buffer to format the message
*@returns void
*/
void merror_win32(HWND hwnd, const char* title, const char* msg, ...);

#endif
    
#ifdef __cplusplus
}
#endif

#endif

