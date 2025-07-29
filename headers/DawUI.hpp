// ---------------------------------------------------------
//
//  Andrew Conner Skatzes (C) 2025
//
//  BSD-3 Clause license
//
//  Description:
//      The Daw's UI header file
//
// ---------------------------------------------------------

// TODO: Add UI elements for the Daw

#ifndef DAWUI_HPP
#define DAWUI_HPP

#include "AudioCore.h"
#include "AudioError.h"

namespace DAWUI
{
    // -- DawUI API function declarations --
    
    /**
     *@brief Initializes the Daw UI with the specified width, height, and title.
     *@param width The width of the Daw UI window.
     *@param height The height of the Daw UI window.
     *@param title The title of the Daw UI window.
     *@returns 0 on success, or a negative error code on failure.
     */
    int init(int width, int height, const char* title, int argc, char *argv[], GtkWindow* window);

    int cleanup(void);

    int openmidi();
}

#endif 