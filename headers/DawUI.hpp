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

/* TIPS For New C++ Developers:
- Learn C first, then C++
- Start learning Java or C# before attempting C++
- Understand you can treat C++ code as C code
- Use C++ features only when necessary
- Don't overuse Object Oriented Programming because it leads to complex code
- Also learn you can use namespaces, they are better than classes for simple code 
- Also just avoid C++ as much as possible, use C instead (Linus Torvalds was right)
*/

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
     *@param widget A pointer to a GtkWidget that will be used for the Daw UI
     *@param window A pointer to a GtkWindow that will be used for the Daw UI
     *@returns 0 on success, or a negative error code on failure.
     */
    int init(int width, int height, const char* title, GtkWidget** widget, GtkWindow** window, GtkApplication** app);

    int createlayout(GtkWindow* window);

    int openmidi();
}

#endif 