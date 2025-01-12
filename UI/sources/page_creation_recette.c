#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include "../header/struct_passage.h"
#include "../header/struct_passage_gestion.h"
#include "../../Data_gestion/header/gestion_types.h"


static void cancel_button_function(GtkWidget *widget, gpointer data){
    passage_changement_page *changement = data;

    gtk_stack_set_visible_child(changement -> stack, changement -> page);
}

GtkWidget *page_creation_recette(GtkWidget *stack, GtkWidget *page, passage_tab_t *passage_tab){

    /*setup box_holder*/
    GtkWidget *box_holder = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);

    gtk_widget_set_valign(box_holder, GTK_ALIGN_FILL);

    gtk_widget_set_halign(box_holder, GTK_ALIGN_FILL);





    /*setup sub_box_holder*/
    GtkWidget *sub_box_holder = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);

    gtk_widget_set_valign(sub_box_holder, GTK_ALIGN_FILL);

    gtk_widget_set_halign(sub_box_holder, GTK_ALIGN_FILL);

    gtk_box_append(GTK_BOX(box_holder), sub_box_holder);





    /*setup holder_separator*/
    GtkWidget *holder_separator = gtk_separator_new(GTK_ORIENTATION_HORIZONTAL);

    gtk_widget_set_valign(sub_box_holder, GTK_ALIGN_CENTER);

    gtk_widget_set_halign(sub_box_holder, GTK_ALIGN_FILL);

    gtk_box_append(GTK_BOX(box_holder), holder_separator);




    /*setup bar_on_bottom*/
    GtkWidget *bar_on_bottom = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);

    gtk_widget_set_valign(bar_on_bottom, GTK_ALIGN_END);

    gtk_widget_set_halign(bar_on_bottom, GTK_ALIGN_END);

    gtk_box_append(GTK_BOX(box_holder), bar_on_bottom);




    /*boutton cancel*/
    GtkWidget *cancel_button = gtk_button_new_with_label("cancel");

    gtk_widget_set_valign(cancel_button, GTK_ALIGN_CENTER);

    gtk_widget_set_halign(cancel_button, GTK_ALIGN_END);

    g_signal_connect(cancel_button, "clicked", G_CALLBACK(cancel_button_function), init_changement_page(stack, page));

    gtk_box_append(GTK_BOX(bar_on_bottom), cancel_button);


    gtk_stack_add_child(GTK_STACK(stack), box_holder);

    return box_holder;
}