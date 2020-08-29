/*
** gui_gtk for OCR in src
**
** Made by SheatNoisette
** Login   SheatNoisette
**
** Started on  2019 SheatNoisette
*/

#include <stdlib.h>
#include <stdio.h>
#include "ocr.h"
#include <gtk/gtk.h>

/* GTK Based gui support for ocr */

#define UNUSED(x) (void)(x)
/* GTK Handler */
char *image_filename = NULL;
GtkTextView *text_view = NULL;

/* called when window is closed */
void handler_exit_window()
{
    gtk_main_quit();
}

/* Null handler */
gboolean handler_null() { return TRUE; }

/* Pick a file */
void pick_bmp(GtkWidget *widget, gpointer windows) {
    UNUSED( widget );
    GtkWindow *parent_window = windows;

    GtkWidget *dialog;
    GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_OPEN;
    gint res;


    dialog = gtk_file_chooser_dialog_new ("Open File",
                                      parent_window,
                                      action,
                                      ("_Cancel"),
                                      GTK_RESPONSE_CANCEL,
                                      ("_Open"),
                                      GTK_RESPONSE_ACCEPT,
                                      NULL);

    gtk_window_set_transient_for(GTK_WINDOW(dialog), GTK_WINDOW(parent_window));

    res = gtk_dialog_run (GTK_DIALOG (dialog));
    if (res == GTK_RESPONSE_ACCEPT)
    {
        GtkFileChooser *chooser = GTK_FILE_CHOOSER (dialog);
        image_filename = gtk_file_chooser_get_filename (chooser);
        printf("[OCR_GTK] File picked: %s", image_filename);
    }

    gtk_widget_destroy (dialog);
}

void launch_ocr(GtkWidget *widget) {
    UNUSED(widget);

    /* Not init -> quit */
    if (image_filename == NULL || text_view == NULL)
        return;

    char *out_ocr = ocr_run(image_filename, 0, 0, 0, NULL, NULL);

    GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_view));
    gtk_text_buffer_set_text(buffer, out_ocr, strlen(out_ocr));

    /* free(out_ocr); */

}

/* Launch GUI */
void gui_run(int argc, char **argv) {
    GtkBuilder *builder = NULL; 
    GtkWidget *window = NULL;
    GError *err = NULL;

    gtk_init(&argc, &argv);

    builder = gtk_builder_new();

    /* Check if we successifully loaded the glade file */
    if(0 == gtk_builder_add_from_file (builder, "ocr_gui.glade", &err))
    {
        printf("[OCR_GTK] Error adding glade file: %s\n", err->message);
        return;
    }

    window = GTK_WIDGET(gtk_builder_get_object(builder, "ocr_gui"));
    GtkButton* run_ocr = GTK_BUTTON(gtk_builder_get_object(builder, "run_ocr"));
    GtkButton* load_image = 
            GTK_BUTTON(gtk_builder_get_object(builder, "load_image"));
    text_view = GTK_TEXT_VIEW(gtk_builder_get_object(builder, "text_out"));

    /* Buttons signals */
    /* Exit */
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    g_signal_connect(run_ocr, "clicked", G_CALLBACK(launch_ocr), NULL);
    g_signal_connect(load_image, "clicked", G_CALLBACK(pick_bmp), window);

    /* Assign signals */
    gtk_builder_connect_signals(builder, NULL);

    g_object_unref(builder);

    gtk_widget_show(window);                
    gtk_main();
}
