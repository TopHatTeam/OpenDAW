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

#include "headers/DawUI.hpp"

void DAWUI::init(const char* title, int width, int height, QWidget &window)
{
    window.resize(width, height);
    window.setWindowTitle(title);
    window.show();
}