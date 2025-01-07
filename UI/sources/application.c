#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include "../header/struct_passage.h"
#include "../header/struct_passage_gestion.h"
#include "../header/pages.h"

/*à mettre dans un nouveau fichier*/



/*_______________________________________________________*/

static void page_show(GtkWidget *widget, gpointer data){

    passage_changement_page *changement = data;

    gtk_stack_set_visible_child(changement -> stack, changement -> page);
}


static void activate(GtkApplication *app, gpointer user_data){

    passage_tab_t *passage_tab = user_data;

    /*setup main window*/
    
    GtkWidget *main_window = gtk_application_window_new(app);

    gtk_window_set_title (GTK_WINDOW (main_window), "home_page");

    





    /*setup main box*/

    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);

    gtk_widget_set_valign(box, GTK_ALIGN_FILL);
    gtk_widget_set_vexpand(box, 1);

    gtk_widget_set_halign(box, GTK_ALIGN_FILL);
    gtk_widget_set_hexpand(box, 1);

    gtk_window_set_child(GTK_WINDOW(main_window), box);





    /*setup stack*/

    GtkWidget *stack = gtk_stack_new();

    gtk_widget_set_valign(stack, GTK_ALIGN_FILL);
    gtk_widget_set_vexpand(stack, 1);

    gtk_widget_set_halign(stack, GTK_ALIGN_FILL);
    gtk_widget_set_hexpand(stack, 1);

    /*pages à ajouter*/
    GtkWidget *page_recette_1 = page_recette(passage_tab);
    gtk_stack_add_child(GTK_STACK(stack), page_recette_1);

    GtkWidget *page_recette_2 = page_recette(passage_tab);
    gtk_stack_add_child(GTK_STACK(stack), page_recette_2);

    /*___*/

    gtk_box_append(GTK_BOX(box), stack);




    /*setup separator*/
    GtkWidget *separator = gtk_separator_new(GTK_ORIENTATION_VERTICAL);

    gtk_box_prepend(GTK_BOX(box), separator);





    /*setup sidebar*/

    GtkWidget *side_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);

    gtk_widget_set_valign(side_box, GTK_ALIGN_FILL);
    gtk_widget_set_vexpand(side_box, 1);

    gtk_widget_set_halign(side_box, GTK_ALIGN_START);
    gtk_widget_set_hexpand(side_box, 0);

    gtk_box_prepend(GTK_BOX(box), side_box);

    /*button de changement de page*/

    /*page_1*/

    GtkWidget *bouton1 = gtk_button_new_with_label("Recettes");

    passage_changement_page *passe_page_1 = init_changement_page(stack, page_recette_1);

    g_signal_connect(bouton1, "clicked", G_CALLBACK(page_show), passe_page_1);

    gtk_widget_set_halign(bouton1, GTK_ALIGN_START);

    gtk_box_append(GTK_BOX(side_box), bouton1);

    /*page_2*/

    GtkWidget *bouton2 = gtk_button_new_with_label("page_2");

    passage_changement_page *passe_page_2 = init_changement_page(stack, page_recette_2);

    g_signal_connect(bouton2, "clicked", G_CALLBACK(page_show), passe_page_2);

    gtk_widget_set_halign(bouton2, GTK_ALIGN_START);

    gtk_box_append(GTK_BOX(side_box), bouton2);







    
    gtk_window_present (GTK_WINDOW (main_window));
}

int main(int argc, char **argv){

    passage_tab_t *passage_tab = init_passage_tab();

    GtkApplication *app = gtk_application_new("org.gtk.example", G_APPLICATION_DEFAULT_FLAGS);

    g_signal_connect(app, "activate", G_CALLBACK(activate), passage_tab);

    int status = g_application_run(G_APPLICATION(app), argc, argv);

    g_object_unref(app);

    return status;
}