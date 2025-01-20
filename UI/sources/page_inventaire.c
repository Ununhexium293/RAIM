#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include "../header/pages.h"
#include "../header/struct_passage.h"
#include "../header/struct_passage_gestion.h"
#include "../../Data_gestion/header/gestion_types.h"
#include "../header/utilities.h"


static void button_add_qt_inventaire(GtkWidget *widget, gpointer data);





static void init_affiche_inventaire(GtkWidget *flowbox, int id_inventaire, passage_tab_t *passage_tab){
    /*setup box holder*/

    GtkWidget *box_holder = gtk_flow_box_new();

    gtk_flow_box_set_max_children_per_line(GTK_FLOW_BOX(box_holder), 1);
    gtk_flow_box_set_selection_mode(GTK_FLOW_BOX(box_holder), GTK_SELECTION_NONE);

    gtk_widget_set_valign(box_holder, GTK_ALIGN_START);

    gtk_widget_set_halign(box_holder, GTK_ALIGN_FILL);
    gtk_widget_set_hexpand(box_holder, 1);





    /*setup label num*/

    char *num = malloc(sizeof(char) * (log_10(id_inventaire) + 1));

    sprintf(num, "%d", id_inventaire);

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

    GtkWidget *label_nom = gtk_label_new(passage_tab -> liste_ingredient -> tab_ingredient_unite[id_inventaire] -> nom);

    gtk_widget_set_valign(label_nom, GTK_ALIGN_CENTER);

    gtk_widget_set_halign(label_nom, GTK_ALIGN_START);

    gtk_box_append(GTK_BOX(box_container), label_nom);




    //setup affichage quantité actuelle


    int quant = passage_tab -> liste_inventaire -> tab_ingredient_quantite[id_inventaire] -> quantite;
    char unite_ing = passage_tab -> liste_ingredient -> tab_ingredient_unite[id_inventaire] -> unite;

    int taille = log_10(quant);

    if(taille == -1){
        taille++;
    }

    char* label_quantite = (char*) malloc(sizeof(char) * (taille+1+2));//Pour rajouter un espace et une unité

    sprintf(label_quantite, "%d %c", quant, unite_ing);

    GtkWidget *widget_qt_act = gtk_label_new(label_quantite);

    free(label_quantite);

    gtk_widget_set_valign(widget_qt_act, GTK_ALIGN_CENTER);

    gtk_widget_set_halign(widget_qt_act, GTK_ALIGN_FILL);
    gtk_widget_set_hexpand(widget_qt_act, 1);

    gtk_box_append(GTK_BOX(box_container), widget_qt_act);





    //setup text unite

    GtkWidget *quantite_input = gtk_entry_new();

    gtk_widget_set_halign(quantite_input, GTK_ALIGN_END);

    gtk_widget_set_size_request(quantite_input, 50, 50);
    
    gtk_box_append(GTK_BOX(box_container), quantite_input);





    /*setup bouton ajout*/

    GtkWidget *boutton_ajouter = gtk_button_new_with_label("ajouter");
    
    gtk_widget_set_valign(label_nom, GTK_ALIGN_CENTER);

    gtk_widget_set_halign(label_nom, GTK_ALIGN_END);

    gtk_box_append(GTK_BOX(box_container), boutton_ajouter);

    g_signal_connect(boutton_ajouter, "clicked", G_CALLBACK(button_add_qt_inventaire), passage_tab);





    /*setup separation*/

    GtkWidget *separator = gtk_separator_new(GTK_ORIENTATION_HORIZONTAL);

    gtk_flow_box_append(GTK_FLOW_BOX(box_holder), separator);
    




    gtk_flow_box_append(GTK_FLOW_BOX(flowbox), box_holder);

}





void update_visual_inventaire(GtkWidget *widget, gpointer data){

    update_page_t *update_page_inventaire = data;

    GtkWidget *temp = update_page_inventaire -> page;

    GtkWidget *scroll_window = gtk_flow_box_child_get_child(gtk_flow_box_get_child_at_index(GTK_FLOW_BOX(temp),2));
    GtkWidget *flowbox = gtk_viewport_get_child(GTK_VIEWPORT(gtk_scrolled_window_get_child(GTK_SCROLLED_WINDOW(scroll_window))));

    gtk_flow_box_remove_all(GTK_FLOW_BOX(flowbox));

    for (int i = 0; i < update_page_inventaire -> passage_tab -> liste_inventaire -> nb_ingredient; i++){
        init_affiche_inventaire(flowbox, i, update_page_inventaire -> passage_tab);
    }

} 





static void button_add_qt_inventaire(GtkWidget *widget, gpointer data){

    passage_tab_t *passage_tab = data;

    GtkWidget *box_container = gtk_widget_get_parent(widget);
    GtkWidget *box_holder = gtk_widget_get_parent(gtk_widget_get_parent(box_container));
    GtkWidget *label = gtk_flow_box_child_get_child(gtk_flow_box_get_child_at_index(GTK_FLOW_BOX(box_holder), 0));
    
    /*get the id of the recipe*/ 
    int id_inventaire = atoi(gtk_label_get_text(GTK_LABEL(label)));

    gchar* valeur = gtk_editable_get_chars(GTK_EDITABLE(GTK_ENTRY(gtk_widget_get_next_sibling(gtk_widget_get_next_sibling(gtk_widget_get_first_child(box_container))))),0,32);

    fflush(stdout);

    int quantite = atoi(valeur);
    



    //Je rajoute la valeur donnée negative ou positive en verifiant tout de meme si ils n'y a pas de dette

    if (passage_tab -> liste_inventaire -> tab_ingredient_quantite[id_inventaire] -> quantite < -quantite){
        return;
    }


    passage_tab -> liste_inventaire -> tab_ingredient_quantite[id_inventaire] -> quantite += quantite;
    /*update the visual*/
    GtkWidget *flowbox_scrolled_window = gtk_widget_get_parent(gtk_widget_get_parent(box_holder));

    gtk_flow_box_remove_all(GTK_FLOW_BOX(flowbox_scrolled_window));

    for (int i = 0; i < passage_tab -> liste_inventaire -> nb_ingredient; i++){
        init_affiche_inventaire(flowbox_scrolled_window, i, passage_tab);
    }

}










/*________________________________________________________________________________*/



static int filter(GtkFlowBoxChild *child, gpointer data){
    char *str = data;

    GtkWidget *box_holder = gtk_flow_box_child_get_child(child);
    GtkWidget *container = gtk_flow_box_child_get_child(gtk_flow_box_get_child_at_index(GTK_FLOW_BOX(box_holder), 1));
    GtkWidget *label = gtk_widget_get_first_child(container);

    const char *text = gtk_label_get_text(GTK_LABEL(label));

    return filter_str(str, text);
}


static void search_filtre(GtkWidget *widget, gpointer data){

    GtkWidget *flowbox1 = gtk_widget_get_parent(gtk_widget_get_parent(gtk_widget_get_parent(widget)));
    GtkWidget *flowbox2 = gtk_viewport_get_child(GTK_VIEWPORT(gtk_scrolled_window_get_child(GTK_SCROLLED_WINDOW(gtk_flow_box_child_get_child(gtk_flow_box_get_child_at_index(GTK_FLOW_BOX(flowbox1), 2))))));

    char *str = gtk_editable_get_chars(GTK_EDITABLE(widget), 0, 32);

    strlower(str);

    gtk_flow_box_set_filter_func(GTK_FLOW_BOX(flowbox2), filter, str, lib_str);
}


static int sort(GtkFlowBoxChild *child1, GtkFlowBoxChild *child2, gpointer data){
    GtkWidget *label1 = gtk_widget_get_first_child(gtk_flow_box_child_get_child(gtk_flow_box_get_child_at_index(GTK_FLOW_BOX(gtk_flow_box_child_get_child(child1)), 1)));
    GtkWidget *label2 = gtk_widget_get_first_child(gtk_flow_box_child_get_child(gtk_flow_box_get_child_at_index(GTK_FLOW_BOX(gtk_flow_box_child_get_child(child2)), 1)));
    
    return compare_str(gtk_label_get_text(GTK_LABEL(label1)), gtk_label_get_text(GTK_LABEL(label2)));
}






GtkWidget *page_inventaire(GtkWidget *stack, passage_tab_t *passage_tab){

    
    
    /*setup flowbox*/

    GtkWidget *flowbox1 = gtk_flow_box_new();

    gtk_widget_set_valign(flowbox1, GTK_ALIGN_START);
    gtk_widget_set_vexpand(flowbox1, 1);

    gtk_widget_set_halign(flowbox1, GTK_ALIGN_FILL);
    gtk_widget_set_hexpand(flowbox1, 1);
    
    gtk_flow_box_set_max_children_per_line(GTK_FLOW_BOX(flowbox1), 1);
    gtk_flow_box_set_selection_mode(GTK_FLOW_BOX(flowbox1), GTK_SELECTION_NONE);

    



    /*setup bar on top*/

    GtkWidget *box_on_top = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);

    gtk_widget_set_valign(box_on_top, GTK_ALIGN_START);

    gtk_widget_set_halign(box_on_top, GTK_ALIGN_FILL);
    gtk_widget_set_hexpand(box_on_top, 1);

    gtk_flow_box_append(GTK_FLOW_BOX(flowbox1), box_on_top);





    /*setup searchentry*/

    GtkWidget *searchentry = gtk_search_entry_new();

    gtk_widget_set_halign(searchentry, GTK_ALIGN_FILL);
    gtk_widget_set_hexpand(searchentry, 1);

    gtk_widget_set_valign(searchentry, GTK_ALIGN_FILL);

    gtk_search_entry_set_search_delay(GTK_SEARCH_ENTRY(searchentry), 125);

    gtk_box_append(GTK_BOX(box_on_top), searchentry);

    g_signal_connect(searchentry, "search_changed", G_CALLBACK(search_filtre), NULL);




    /*setup seperator*/
    GtkWidget *separator = gtk_separator_new(GTK_ORIENTATION_HORIZONTAL);

    gtk_flow_box_append(GTK_FLOW_BOX(flowbox1), separator);





    /*setup scroll_window*/

    GtkWidget *scrollwindow = gtk_scrolled_window_new();

    gtk_widget_set_halign(searchentry, GTK_ALIGN_FILL);

    gtk_widget_set_valign(searchentry, GTK_ALIGN_FILL);
    gtk_widget_set_vexpand(scrollwindow, 1);

    gtk_scrolled_window_set_propagate_natural_height(GTK_SCROLLED_WINDOW(scrollwindow), 1);

    gtk_flow_box_append(GTK_FLOW_BOX(flowbox1), scrollwindow);





    /*setup child_flow_box*/

    GtkWidget *flowbox2 = gtk_flow_box_new();

    gtk_widget_set_valign(flowbox2, GTK_ALIGN_START);

    gtk_widget_set_halign(flowbox2, GTK_ALIGN_FILL);
    gtk_widget_set_hexpand(flowbox2, 1);

    gtk_flow_box_set_max_children_per_line(GTK_FLOW_BOX(flowbox2), 1);
    gtk_flow_box_set_selection_mode(GTK_FLOW_BOX(flowbox2), GTK_SELECTION_NONE);

    gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(scrollwindow), flowbox2);

    gtk_flow_box_set_sort_func(GTK_FLOW_BOX(flowbox2), sort, NULL, NULL);

    gtk_stack_add_child(GTK_STACK(stack), flowbox1);

    /*ajout des inventaires enregistre*/

    for (int i = 0; i < passage_tab -> liste_inventaire -> nb_ingredient; i++){
        init_affiche_inventaire(flowbox2, i, passage_tab);
    }

    return flowbox1;
}