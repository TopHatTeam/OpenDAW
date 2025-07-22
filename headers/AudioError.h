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

#include <gtk-2.0/gtk/gtk.h>

#ifndef AUDIOERROR_H
#define AUDIOERROR_H

#ifdef __cplusplus
extern "C" {
#endif

void merror(GtkWindow* parent, const char* msg);
    
#ifdef __cplusplus
}
#endif

#endif

