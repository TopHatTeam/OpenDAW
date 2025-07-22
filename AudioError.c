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

#include "headers/AudioError.h"

void merror(GtkWindow* parent, const char* msg)
{
    GtkWidget* dialog = gtk_message_dialog_new(
        parent,
        GTK_DIALOG_DESTROY_WITH_PARENT,
        GTK_MESSAGE_ERROR,
        GTK_BUTTONS_CLOSE,
        "%s", msg
    );
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
}