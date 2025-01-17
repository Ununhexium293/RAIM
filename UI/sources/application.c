#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include "../header/struct_passage.h"
#include "../header/struct_passage_gestion.h"
#include "../header/pages.h"
#include "../../Data_gestion/header/write_data.h"


/*à mettre dans un nouveau fichier*/



/*_______________________________________________________*/

static void page_show(GtkWidget *widget, gpointer data){

    passage_changement_page *changement = data;

    gtk_stack_set_visible_child(changement -> stack, changement -> page);
}

static void ferme(GtkWidget *widget, gpointer data){
    passage_tab_t *passage_tab = data;

    write_database(passage_tab -> liste_link);
    write_recette(passage_tab -> liste_recette);
    write_inventaire(passage_tab -> liste_inventaire);
    write_menu(passage_tab -> liste_menu);
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
    GtkWidget *page_recette_1 = page_recette(stack, passage_tab);

    GtkWidget *page_recette_2 = page_recette(stack, passage_tab);

    GtkWidget *page_ingredient_3 = page_ingredient(stack, passage_tab);

    GtkWidget *page_inventaire_4 = page_inventaire(stack, passage_tab);

    GtkWidget *page_menu_5 = page_menu(stack, passage_tab);

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

    /*permet de changer de page*/

    passage_changement_page *passe_page_1 = init_changement_page(stack, page_recette_1);

    g_signal_connect(bouton1, "clicked", G_CALLBACK(page_show), passe_page_1);

    /*permet de mettre à jour la page*/

    update_page_t *update_page_recette1 = init_update_page(passage_tab, page_recette_1);

    g_signal_connect(bouton1, "clicked", G_CALLBACK(update_visual_recette), update_page_recette1);

    gtk_widget_set_halign(bouton1, GTK_ALIGN_START);

    gtk_box_append(GTK_BOX(side_box), bouton1);

    /*page_2*/

    GtkWidget *bouton2 = gtk_button_new_with_label("page_2");

    /*permet de changer de page*/

    passage_changement_page *passe_page_2 = init_changement_page(stack, page_recette_2);

    g_signal_connect(bouton2, "clicked", G_CALLBACK(page_show), passe_page_2);

    /*permet de mettre à jour la page*/

    update_page_t *update_page_recette2 = init_update_page(passage_tab, page_recette_2);

    g_signal_connect(bouton2, "clicked", G_CALLBACK(update_visual_recette), update_page_recette2);

    gtk_widget_set_halign(bouton2, GTK_ALIGN_START);

    gtk_box_append(GTK_BOX(side_box), bouton2);




    /*page_3*/

    GtkWidget *bouton3 = gtk_button_new_with_label("Ingredients");

    /*permet de changer de page*/

    passage_changement_page *passe_page_3 = init_changement_page(stack, page_ingredient_3);

    g_signal_connect(bouton3, "clicked", G_CALLBACK(page_show), passe_page_3);

    /*permet de mettre à jour la page*/

    update_page_t *update_page_ingredient3 = init_update_page(passage_tab, page_ingredient_3);

    g_signal_connect(bouton3, "clicked", G_CALLBACK(update_visual_ingredient), update_page_ingredient3);

    gtk_widget_set_halign(bouton3, GTK_ALIGN_START);

    gtk_box_append(GTK_BOX(side_box), bouton3);




    //page 4

    GtkWidget *bouton4 = gtk_button_new_with_label("Iventaire");

    //Permet de changer de page

    passage_changement_page *passe_page_4 = init_changement_page(stack, page_inventaire_4);

    g_signal_connect(bouton4, "clicked", G_CALLBACK(page_show), passe_page_4);

    //permet de mettre a jour la page

    update_page_t *update_page_inventaire4 = init_update_page(passage_tab, page_inventaire_4);

    g_signal_connect(bouton4, "clicked", G_CALLBACK(update_visual_inventaire), update_page_inventaire4);

    gtk_widget_set_halign(bouton4, GTK_ALIGN_START);

    gtk_box_append(GTK_BOX(side_box), bouton4);



    //page 5

    GtkWidget *bouton5 = gtk_button_new_with_label("Menu");

    //Permet de changer de page

    passage_changement_page *passe_page_5 = init_changement_page(stack, page_menu_5);

    g_signal_connect(bouton5, "clicked", G_CALLBACK(page_show), passe_page_5);

    //permet de mettre a jour la page

    update_page_t *update_page_menu5 = init_update_page(passage_tab, page_menu_5);

    g_signal_connect(bouton5, "clicked", G_CALLBACK(update_visual_menu), update_page_menu5);

    gtk_widget_set_halign(bouton5, GTK_ALIGN_START);

    gtk_box_append(GTK_BOX(side_box), bouton5);






    g_signal_connect(main_window, "close-request", G_CALLBACK(ferme), passage_tab);
    
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