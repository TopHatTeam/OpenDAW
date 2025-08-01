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

int DAWUI::init(int width, int height, const char* title, int argc, char *argv[], GtkWindow** window)
{
    // Initialize GTK or nothing happens :(
    gtk_init(&argc, &argv);

    // Create a new window on top level
    *window = GTK_WINDOW(gtk_window_new(GTK_WINDOW_TOPLEVEL));

    // Set the title of the window 
    gtk_window_set_title(window, title);

    // Set the default size of the window
    gtk_window_set_default_size(window, width, height);

    return 0;
}

int DAWUI::createlayout(GtkWindow* window)
{
    // TODO: Implement the layout creation for the DAW UI
    return 0;
}

int DAWUI::cleanup(void)
{
    gtk_main_quit();
    return 0;
}

int DAWUI::openmidi()
{
    GtkWidget* midi_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_widget_set_title(midi_window, "MIDI Editor");
    gtk_wdiget_set_default_size(midi_window, 800, 600);
    // TODO: Implement MIDI editor layout and functionality
    return 0;
}