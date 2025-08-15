// ---------------------------------------------------------
//
//  Andrew Conner Skatzes (C) 2025
//
//  BSD-3 Clause license
//
//  Description:
//      The Main entry to the program
//
// ---------------------------------------------------------

#include "headers/AudioCore.h"
#include "headers/AudioError.h"
#include "headers/DawUI.hpp"

/*Switching to Qt6 here fellows!*/

int main(int argc, char *argv[])
{
#if defined(__linux__)
    
    QApplication app(argc, argv);
    QWidget window;
    DAWUI::init("OpenDAW", 1920, 1080, window);
#elif defined(_WIN32)
    
#endif
    return app.exec();
}