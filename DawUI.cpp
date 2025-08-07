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

int DAWUI::init(int width, int height, const char* title, GtkWidget** widget, GtkWindow** window, GtkApplication** app)
{
    // Initialize GTK or nothing happens :(
    gtk_init();

    // Create a new window on top level
    GtkApplication* a7x_app = gtk_application_new("com.opendaw.GtkApplication", G_APPLICATION_FLAGS_NONE);
    GtkWidget* a7x_widget = gtk_window_new();
    GtkWindow* a7x_window = GTK_WINDOW(a7x_widget);

    // Set the title of the window 
    gtk_window_set_title(a7x_window, title);

    // Set the default size of the window
    gtk_window_set_default_size(a7x_window, width, height);

    *widget = a7x_widget;
    *window = a7x_window;
    *app = a7x_app;

    return 0;
}

int DAWUI::createlayout(GtkWindow* window)
{
    // TODO: Implement the layout creation for the DAW UI
    return 0;
}
int DAWUI::openmidi()
{
    GtkWidget* midi_window = gtk_window_new();
    gtk_window_set_title(GTK_WINDOW(midi_window), "MIDI Editor");
    gtk_window_set_default_size(GTK_WINDOW(midi_window), 800, 600);
    // TODO: Implement MIDI editor layout and functionality
    gtk_widget_show(midi_window);
    return 0;
}