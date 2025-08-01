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

static gboolean winclose = FALSE;

static void windestroy(GtkWindow* window, gpointer data)
{
    // Set the winclose flag to TRUE when the window is destroyed
    winclose = TRUE;
    DAWUI::cleanup();
}

int main(int argc, char *argv[])
{
#if defined(__linux__)
    DAWUI dui;
    
#elif defined(_WIN32)
    // initalize the GTK window
    DAWUI dui;
    GtkWindow* window = NULL;
    DAWUI::init(1280, 720, "OpenDAW", argc, argv, &window);

    // Initialize the AudioCore
    if (AudioCore_Init("default", 44100) < 0)
    {
        merror_win32(NULL, "AudioCore Error", "Failed to initialize AudioCore");
        return -1;
    }

    // Check if the window was asked to close
    g_signal_connect(window, "close-request", G_CALLBACK(windestroy), NULL);

    // Manual loop for GTK
    while (!winclose)
    {
        while (gtk_events_pending())
        {
            gtk_main_iteration();
        }


    }

    // Cleanup AudioCore resources
    AudioCore_Cleanup();
    windestroy(window, NULL);

#endif
    return 0;
}