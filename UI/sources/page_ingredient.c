#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include "../header/struct_passage.h"
#include "../../Data_gestion/header/gestion_types.h"
#include "../../Data_gestion/header/write_data.h"
#include "../header/utilities.h"





static void init_affiche_ingredient(GtkWidget *flowbox, int id_ingredient, passage_tab_t *passage_tab){
    /*setup box holder*/

    GtkWidget *box_holder = gtk_flow_box_new();

    gtk_flow_box_set_max_children_per_line(GTK_FLOW_BOX(box_holder), 1);
    gtk_flow_box_set_selection_mode(GTK_FLOW_BOX(box_holder), GTK_SELECTION_NONE);

    gtk_widget_set_valign(box_holder, GTK_ALIGN_START);

    gtk_widget_set_halign(box_holder, GTK_ALIGN_FILL);
    gtk_widget_set_hexpand(box_holder, 1);





    /*setup label num*/

    char *num = malloc(sizeof(char) * (log_10(id_ingredient) + 1));

    sprintf(num, "%d", id_ingredient);

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

    GtkWidget *label_nom = gtk_label_new(passage_tab -> liste_ingredient -> tab_ingredient_unite[id_ingredient] -> nom);

    gtk_widget_set_valign(label_nom, GTK_ALIGN_CENTER);

    gtk_widget_set_halign(label_nom, GTK_ALIGN_START);

    gtk_box_append(GTK_BOX(box_container), label_nom);




    /*setup espacement*/
    GtkWidget *espacement = gtk_label_new(" ");

    gtk_widget_set_valign(espacement, GTK_ALIGN_CENTER);

    gtk_widget_set_halign(espacement, GTK_ALIGN_FILL);
    gtk_widget_set_hexpand(espacement, 1);

    gtk_box_append(GTK_BOX(box_container), espacement);

    

    /*setup separation*/

    GtkWidget *separator = gtk_separator_new(GTK_ORIENTATION_HORIZONTAL);

    gtk_flow_box_append(GTK_FLOW_BOX(box_holder), separator);




    gtk_flow_box_append(GTK_FLOW_BOX(flowbox), box_holder);

}





void update_visual_ingredient(GtkWidget *widget, gpointer data){

    update_page_t *update_page_ingredient = data;

    GtkWidget *temp = update_page_ingredient -> page;

    GtkWidget *scroll_window = gtk_flow_box_child_get_child(gtk_flow_box_get_child_at_index(GTK_FLOW_BOX(temp),2));
    GtkWidget *flowbox = gtk_viewport_get_child(GTK_VIEWPORT(gtk_scrolled_window_get_child(GTK_SCROLLED_WINDOW(scroll_window))));

    gtk_flow_box_remove_all(GTK_FLOW_BOX(flowbox));

    for (int i = 0; i < update_page_ingredient -> passage_tab -> liste_ingredient -> nb_ingredient; i++){
        init_affiche_ingredient(flowbox, i, update_page_ingredient -> passage_tab);
    }

} 



void add_ingredient(GtkWidget *widget,  gpointer data){

    
    passage_tab_t *passage_tab = data;

    //on recup le widget parent commun aux 2 text box
    GtkWidget *box_on_top = gtk_widget_get_parent(widget);
    
    //je recup le content des 2 text box
    gchar* ing = gtk_editable_get_chars(GTK_EDITABLE(gtk_widget_get_first_child(box_on_top)),0,32);
    strlower(ing);

    gchar* unite = gtk_editable_get_chars(GTK_EDITABLE(gtk_widget_get_next_sibling(gtk_widget_get_first_child(box_on_top))),0,32);


    //je vide la zone de texte
    gtk_editable_delete_text(GTK_EDITABLE(gtk_widget_get_first_child(box_on_top)),0,32);
    gtk_editable_delete_text(GTK_EDITABLE(gtk_widget_get_next_sibling(gtk_widget_get_first_child(box_on_top))),0,32);

    //je rajoute le nouvel ing dans le tableau
    add_tab_ingredient_nom_unite(passage_tab -> liste_ingredient, ing, unite[0]);


    //Je crée une case d'inventaire pour le nouvel ingredient
    add_tab_ingredient(passage_tab -> liste_inventaire, passage_tab -> liste_ingredient  -> nb_ingredient -1, 0);

    init_affiche_ingredient(gtk_viewport_get_child(GTK_VIEWPORT(gtk_scrolled_window_get_child(GTK_SCROLLED_WINDOW(gtk_flow_box_child_get_child(gtk_flow_box_get_child_at_index(GTK_FLOW_BOX(gtk_widget_get_parent(gtk_widget_get_parent(box_on_top))), 2)))))), passage_tab -> liste_ingredient -> nb_ingredient - 1, passage_tab);

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






GtkWidget *page_ingredient(GtkWidget *stack, passage_tab_t *passage_tab){

    
    
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


    //setup text unite

    GtkWidget *textunite = gtk_entry_new();

    gtk_widget_set_halign(textunite, GTK_ALIGN_END);

    gtk_widget_set_size_request(textunite, 50, 50);
    
    gtk_box_append(GTK_BOX(box_on_top), textunite);


    /*setup add_button*/

    GtkWidget *add_button = gtk_button_new_with_label("nouvel ingredient");

    gtk_widget_set_halign(add_button, GTK_ALIGN_END);

    gtk_widget_set_size_request(add_button, 200, 50);
    
    gtk_box_append(GTK_BOX(box_on_top), add_button);

    g_signal_connect(add_button, "clicked", G_CALLBACK(add_ingredient) ,passage_tab);
    





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

    gtk_flow_box_set_sort_func(GTK_FLOW_BOX(flowbox2), sort, NULL, NULL);

    gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(scrollwindow), flowbox2);

    gtk_stack_add_child(GTK_STACK(stack), flowbox1);

    /*ajout des ingredients enregistre*/

    for (int i = 0; i < passage_tab -> liste_ingredient -> nb_ingredient; i++){
        init_affiche_ingredient(flowbox2, i, passage_tab);
    }

    return flowbox1;
}