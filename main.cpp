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
}

int main(int argc, char *argv[])
{
#if defined(__linux__)
    
#elif defined(_WIN32)
    // initalize the GTK window
    GtkWindow* window = NULL;
    GtkWidget* widget = NULL;
    DAWUI::init(1280, 720, "OpenDAW", widget, window);

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
        while (g_main_context_iteration(NULL, FALSE));


    }

    // Cleanup AudioCore resources
    AudioCore_Cleanup();
    windestroy(window, NULL);

#endif
    return 0;
}