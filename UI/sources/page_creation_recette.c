#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include "../header/utilities.h"
#include "../header/struct_passage.h"
#include "../header/struct_passage_gestion.h"
#include "../../Data_gestion/header/struct.h"
#include "../../Data_gestion/header/gestion_types.h"




/*fonction setup partie gauche*/

/*a faire : - bouton rm*/

//wstatic void button_rm_ingr();

static void left_part_component(GtkWidget *sub_box_holder, passage_tab_t *passage_tab, int id_ingr, char *quantite){

    GtkWidget *left_part = gtk_paned_get_start_child(GTK_PANED(sub_box_holder));;
    GtkWidget *scrolled_window = gtk_flow_box_child_get_child(gtk_flow_box_get_child_at_index(GTK_FLOW_BOX(left_part), 2));
    GtkWidget *flowbox = gtk_viewport_get_child(GTK_VIEWPORT(gtk_scrolled_window_get_child(GTK_SCROLLED_WINDOW(scrolled_window))));



    /*setup box holder*/

    GtkWidget *box_holder = gtk_flow_box_new();

    gtk_flow_box_set_max_children_per_line(GTK_FLOW_BOX(box_holder), 1);
    gtk_flow_box_set_selection_mode(GTK_FLOW_BOX(box_holder), GTK_SELECTION_NONE);

    gtk_widget_set_valign(box_holder, GTK_ALIGN_START);

    gtk_widget_set_halign(box_holder, GTK_ALIGN_FILL);
    gtk_widget_set_hexpand(box_holder, 1);





    /*setup label num*/

    char *num = malloc(sizeof(char) * (log_10(id_ingr) + 1));

    sprintf(num, "%d", id_ingr);

    GtkWidget *label_num = gtk_label_new(num);

    free(num);

    gtk_widget_set_visible(label_num, 0);

    gtk_flow_box_append(GTK_FLOW_BOX(box_holder), label_num);







    /*setup box container*/

    GtkWidget *box_container = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    
    gtk_widget_set_valign(box_container, GTK_ALIGN_START);

    gtk_widget_set_halign(box_container, GTK_ALIGN_FILL);
    gtk_widget_set_hexpand(box_container, 1);

    gtk_flow_box_append(GTK_FLOW_BOX(box_holder), box_container);





    /*setup label nom*/

    GtkWidget *label_nom = gtk_label_new(passage_tab -> liste_ingredient -> tab_ingredient_unite[id_ingr] -> nom);

    gtk_widget_set_valign(label_nom, GTK_ALIGN_CENTER);

    gtk_widget_set_halign(label_nom, GTK_ALIGN_START);

    gtk_box_append(GTK_BOX(box_container), label_nom);





    /*setup label quantite*/
    GtkWidget *label_quantite = gtk_label_new(quantite);

    gtk_widget_set_valign(label_quantite, GTK_ALIGN_CENTER);

    gtk_widget_set_halign(label_quantite, GTK_ALIGN_START);

    gtk_box_append(GTK_BOX(box_container), label_quantite);




    /*setup label unite*/
    /*test necessaire*/
    GtkWidget *label_unite = gtk_label_new(&(passage_tab -> liste_ingredient -> tab_ingredient_unite[id_ingr] -> unite));

    gtk_widget_set_valign(label_unite, GTK_ALIGN_CENTER);

    gtk_widget_set_halign(label_unite, GTK_ALIGN_START);

    gtk_box_append(GTK_BOX(box_container), label_unite);






    /*setup espacement*/
    GtkWidget *espacement = gtk_label_new(" ");

    gtk_widget_set_valign(espacement, GTK_ALIGN_CENTER);

    gtk_widget_set_halign(espacement, GTK_ALIGN_FILL);
    gtk_widget_set_hexpand(espacement, 1);

    gtk_box_append(GTK_BOX(box_container), espacement);





    /*setup bouton supprimer*/

    GtkWidget *boutton_supprimer = gtk_button_new_with_label("supprimer");
    
    gtk_widget_set_valign(boutton_supprimer, GTK_ALIGN_CENTER);

    gtk_widget_set_halign(boutton_supprimer, GTK_ALIGN_END);

    gtk_box_append(GTK_BOX(box_container), boutton_supprimer);

    //g_signal_connect(boutton_supprimer, "clicked", G_CALLBACK(button_rm_ingr), passage_tab);





    /*setup separation*/

    GtkWidget *separator = gtk_separator_new(GTK_ORIENTATION_HORIZONTAL);

    gtk_flow_box_append(GTK_FLOW_BOX(box_holder), separator);





    gtk_flow_box_append(GTK_FLOW_BOX(flowbox), box_holder);
}








GtkWidget *set_left_part(GtkWidget *sub_box_holder ){

    /*setup main container*/
    GtkWidget *container = gtk_flow_box_new();

    gtk_widget_set_valign(container, GTK_ALIGN_START);
    gtk_widget_set_vexpand(container, 1);

    gtk_widget_set_halign(container, GTK_ALIGN_FILL);
    gtk_widget_set_hexpand(container, 1);

    gtk_flow_box_set_max_children_per_line(GTK_FLOW_BOX(container), 1);
    gtk_flow_box_set_selection_mode(GTK_FLOW_BOX(container), GTK_SELECTION_NONE);

    gtk_paned_set_start_child(GTK_PANED(sub_box_holder), container);






    /*setup entre nom recette*/

    /*setup box*/
    
    GtkWidget *box_on_top = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);

    gtk_widget_set_valign(box_on_top, GTK_ALIGN_START);

    gtk_widget_set_halign(box_on_top, GTK_ALIGN_FILL);

    gtk_flow_box_append(GTK_FLOW_BOX(container), box_on_top);

    /*setup label*/
    
    GtkWidget *label_nom_recettte = gtk_label_new("Nom recette : ");

    gtk_widget_set_valign(label_nom_recettte, GTK_ALIGN_START);

    gtk_widget_set_halign(label_nom_recettte, GTK_ALIGN_START);

    gtk_box_append(GTK_BOX(box_on_top), label_nom_recettte);

    /*setup text entry*/

    GtkWidget *entry_nom_recette = gtk_entry_new();

    gtk_widget_set_valign(entry_nom_recette, GTK_ALIGN_START);

    gtk_widget_set_halign(entry_nom_recette, GTK_ALIGN_FILL);
    gtk_widget_set_hexpand(entry_nom_recette, 1);

    gtk_box_append(GTK_BOX(box_on_top), entry_nom_recette);

    /*end setup nom recette*/





    /*setup separator*/

    GtkWidget *separator = gtk_separator_new(GTK_ORIENTATION_HORIZONTAL);

    gtk_flow_box_append(GTK_FLOW_BOX(container), separator);



    /*setup scrolled window*/

    GtkWidget *scrolled_window = gtk_scrolled_window_new();

    gtk_widget_set_halign(scrolled_window, GTK_ALIGN_FILL);

    gtk_widget_set_valign(scrolled_window, GTK_ALIGN_FILL);
    gtk_widget_set_vexpand(scrolled_window, 1);

    gtk_scrolled_window_set_propagate_natural_height(GTK_SCROLLED_WINDOW(scrolled_window), 1);

    gtk_flow_box_append(GTK_FLOW_BOX(container), scrolled_window);



    /*setup flowbox*/

    GtkWidget *flowbox = gtk_flow_box_new();

    gtk_widget_set_valign(flowbox, GTK_ALIGN_START);
    gtk_widget_set_vexpand(flowbox, 1);

    gtk_widget_set_halign(flowbox, GTK_ALIGN_FILL);
    gtk_widget_set_hexpand(flowbox, 1);

    gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(scrolled_window), flowbox);



    return container;
}














/*setup rigth window*/

static void button_add_ingr(GtkWidget *button, gpointer data){
    passage_tab_t *passage_tab = data;

    GtkWidget *entry = gtk_widget_get_first_child(gtk_widget_get_parent(button));

    GtkWidget *flowbox = gtk_widget_get_parent(gtk_widget_get_parent(gtk_widget_get_parent(button)));

    GtkWidget *paned = gtk_widget_get_parent(gtk_widget_get_parent(gtk_widget_get_parent(gtk_widget_get_parent(gtk_widget_get_parent(flowbox)))));

    char *quantity = gtk_editable_get_chars(GTK_EDITABLE (entry), 0, 32);

    //int quantite = atoi(quantity);

    int id_ingr = atoi(gtk_label_get_text(GTK_LABEL(gtk_flow_box_child_get_child(gtk_flow_box_get_child_at_index(GTK_FLOW_BOX(flowbox), 0)))));


    left_part_component(paned, passage_tab, id_ingr, quantity);
}

static void rigth_part_component(GtkWidget *sub_box_holder, passage_tab_t *passage_tab, int id_ingr){

    GtkWidget *rigth_part = gtk_paned_get_end_child(GTK_PANED(sub_box_holder));;

    GtkWidget *scrolled_window = gtk_flow_box_child_get_child(gtk_flow_box_get_child_at_index(GTK_FLOW_BOX(rigth_part), 2));

    GtkWidget *flowbox = gtk_viewport_get_child(GTK_VIEWPORT(gtk_scrolled_window_get_child(GTK_SCROLLED_WINDOW(scrolled_window))));




    /*setup box holder*/

    GtkWidget *box_holder = gtk_flow_box_new();

    gtk_flow_box_set_max_children_per_line(GTK_FLOW_BOX(box_holder), 1);
    gtk_flow_box_set_selection_mode(GTK_FLOW_BOX(box_holder), GTK_SELECTION_NONE);

    gtk_widget_set_valign(box_holder, GTK_ALIGN_START);

    gtk_widget_set_halign(box_holder, GTK_ALIGN_FILL);
    gtk_widget_set_hexpand(box_holder, 1);





    /*setup label num*/

    char *num = malloc(sizeof(char) * (log_10(id_ingr) + 1));

    sprintf(num, "%d", id_ingr);

    GtkWidget *label_num = gtk_label_new(num);

    free(num);

    gtk_widget_set_visible(label_num, 0);

    gtk_flow_box_append(GTK_FLOW_BOX(box_holder), label_num);







    /*setup box container*/

    GtkWidget *box_container = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    
    gtk_widget_set_valign(box_container, GTK_ALIGN_START);

    gtk_widget_set_halign(box_container, GTK_ALIGN_FILL);
    gtk_widget_set_hexpand(box_container, 1);

    gtk_flow_box_append(GTK_FLOW_BOX(box_holder), box_container);





    /*setup label quantite*/
    GtkWidget *entry_quantite = gtk_entry_new();

    gtk_widget_set_valign(entry_quantite, GTK_ALIGN_CENTER);

    gtk_widget_set_halign(entry_quantite, GTK_ALIGN_START);

    gtk_box_append(GTK_BOX(box_container), entry_quantite);




    /*setup label unite*/
    /*test necessaire*/
    GtkWidget *label_unite = gtk_label_new(&(passage_tab -> liste_ingredient -> tab_ingredient_unite[id_ingr] -> unite));

    gtk_widget_set_valign(label_unite, GTK_ALIGN_CENTER);

    gtk_widget_set_halign(label_unite, GTK_ALIGN_START);

    gtk_box_append(GTK_BOX(box_container), label_unite);






    /*setup espacement*/
    GtkWidget *espacement = gtk_label_new(" ");

    gtk_widget_set_valign(espacement, GTK_ALIGN_CENTER);

    gtk_widget_set_halign(espacement, GTK_ALIGN_FILL);
    gtk_widget_set_hexpand(espacement, 1);

    gtk_box_append(GTK_BOX(box_container), espacement);





    /*setup bouton ajouter*/

    GtkWidget *boutton_ajouter = gtk_button_new_with_label("ajouter");
    
    gtk_widget_set_valign(boutton_ajouter, GTK_ALIGN_CENTER);

    gtk_widget_set_halign(boutton_ajouter, GTK_ALIGN_END);

    gtk_box_append(GTK_BOX(box_container), boutton_ajouter);

    g_signal_connect(boutton_ajouter, "clicked", G_CALLBACK(button_add_ingr), passage_tab);





    /*setup separation*/

    GtkWidget *separator = gtk_separator_new(GTK_ORIENTATION_HORIZONTAL);

    gtk_flow_box_append(GTK_FLOW_BOX(box_holder), separator);





    gtk_flow_box_append(GTK_FLOW_BOX(flowbox), box_holder);
}




GtkWidget *set_rigth_part(GtkWidget *sub_box_holder, passage_tab_t *passage_tab){

    /*setup main container*/
    GtkWidget *container = gtk_flow_box_new();

    gtk_widget_set_valign(container, GTK_ALIGN_START);
    gtk_widget_set_vexpand(container, 1);

    gtk_widget_set_halign(container, GTK_ALIGN_FILL);
    gtk_widget_set_hexpand(container, 1);

    gtk_flow_box_set_max_children_per_line(GTK_FLOW_BOX(container), 1);
    gtk_flow_box_set_selection_mode(GTK_FLOW_BOX(container), GTK_SELECTION_NONE);

    gtk_paned_set_end_child(GTK_PANED(sub_box_holder), container);






    /*setup searchbar*/

    /*setup box*/
    
    GtkWidget *box_on_top = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);

    gtk_widget_set_valign(box_on_top, GTK_ALIGN_START);

    gtk_widget_set_halign(box_on_top, GTK_ALIGN_FILL);

    gtk_flow_box_append(GTK_FLOW_BOX(container), box_on_top);

    /*setup text entry*/

    GtkWidget *searchbar = gtk_search_entry_new();

    gtk_widget_set_valign(searchbar, GTK_ALIGN_START);

    gtk_widget_set_halign(searchbar, GTK_ALIGN_FILL);
    gtk_widget_set_hexpand(searchbar, 1);

    gtk_box_append(GTK_BOX(box_on_top), searchbar);

    /*end setup searchbar*/





    /*setup separator*/

    GtkWidget *separator = gtk_separator_new(GTK_ORIENTATION_HORIZONTAL);

    gtk_flow_box_append(GTK_FLOW_BOX(container), separator);



    /*setup scrolled window*/

    GtkWidget *scrolled_window = gtk_scrolled_window_new();

    gtk_widget_set_halign(scrolled_window, GTK_ALIGN_FILL);

    gtk_widget_set_valign(scrolled_window, GTK_ALIGN_FILL);
    gtk_widget_set_vexpand(scrolled_window, 1);

    gtk_scrolled_window_set_propagate_natural_height(GTK_SCROLLED_WINDOW(scrolled_window), 1);

    gtk_flow_box_append(GTK_FLOW_BOX(container), scrolled_window);


    /*setup flowbox*/

    GtkWidget *affiche_ingr = gtk_flow_box_new();

    gtk_widget_set_halign(affiche_ingr, GTK_ALIGN_FILL);

    gtk_widget_set_valign(affiche_ingr, GTK_ALIGN_FILL);

    gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(scrolled_window), affiche_ingr);

    for (int i = 0; i < passage_tab -> liste_ingredient -> nb_ingredient; i++){
        rigth_part_component(sub_box_holder, passage_tab, i);
    }


    return container;
}






/*setup main page*/

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
    GtkWidget *sub_box_holder = gtk_paned_new(GTK_ORIENTATION_HORIZONTAL);

    gtk_widget_set_valign(sub_box_holder, GTK_ALIGN_FILL);
    gtk_widget_set_vexpand(sub_box_holder, 1);

    gtk_widget_set_halign(sub_box_holder, GTK_ALIGN_FILL);
    gtk_widget_set_hexpand(sub_box_holder, 1);

    gtk_paned_set_wide_handle(GTK_PANED(sub_box_holder), 1);

    gtk_box_append(GTK_BOX(box_holder), sub_box_holder);
    

    /*setup left part*/
    /*GtkWidget *left_part =*/ set_left_part(sub_box_holder);

    /*setup rigth part*/
    /*test*/set_rigth_part(sub_box_holder, passage_tab);


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