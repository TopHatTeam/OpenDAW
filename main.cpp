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
    GtkApplication* app;
    GtkWindow* window;
    GtkWidget* widget;
    DAWUI::init(1280, 720, "OpenDAW", &widget, &window, &app);

    if (window == NULL)
    {
        merror_win32(NULL, "DawUI Error", "Failed to create the GTK window");
        return -1;
    }
    
    /* Checkin' if the ol' widget is NULL
    Because the son of a bitch doesn't like to work!
    My momma always told me to tell a program to kiss my American ass 
    */
    if (widget == NULL)
    {
        merror_win32(NULL, "DawUI Error", "Failed to create the GTK widget");
        return -1;
    }

    if (app == NULL)
    {
        merror_win32(NULL, "DawUI Error", "Failed to create GTK application");
        return -1;
    }

    // Initialize the AudioCore
    if (AudioCore_Init("default", 44100) < 0)
    {
        merror_win32(NULL, "AudioCore Error", "Failed to initialize AudioCore");
        return -1;
    }

    gtk_widget_show(widget);

    // Check if the window was asked to close
    g_signal_connect(window, "close-request", G_CALLBACK(windestroy), NULL);

    /* REMOVED MANUAL LOOP BECAUSE I'M USE TO OTHER APIs*/

    // Cleanup AudioCore resources
    AudioCore_Cleanup();

#endif
    return g_application_run(G_APPLICATION(app), argc, argv);
}