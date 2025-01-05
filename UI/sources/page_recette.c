#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include "../header/struct_passage.h"

/*a faire*/
/*fonction modif recette*/
/*fonction ajout recette*/
/*fonction supprimer recette*/
/*fonction ajouter recette*/

static int log_10(int n){
    int count = 0;

    while (n != 0){
        n /= 10;
        count++;
    }

    count--;

    return count;
}
























static void init_affiche_recette(GtkWidget *flowbox, int id_recette, passage_tab_t *passage_tab){
    /*setup box holder*/

    GtkWidget *box_holder = gtk_flow_box_new();

    gtk_flow_box_set_max_children_per_line(GTK_FLOW_BOX(box_holder), 1);
    gtk_flow_box_set_selection_mode(GTK_FLOW_BOX(box_holder), GTK_SELECTION_NONE);

    gtk_widget_set_valign(box_holder, GTK_ALIGN_START);

    gtk_widget_set_halign(box_holder, GTK_ALIGN_FILL);
    gtk_widget_set_hexpand(box_holder, 1);





    /*setup label num*/

    char *num = malloc(sizeof(char) * (log_10(id_recette) + 1));

    sprintf(num, "%d", id_recette);

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

    GtkWidget *label_nom = gtk_label_new(passage_tab -> liste_recette -> tb_string[id_recette]);

    gtk_widget_set_valign(label_nom, GTK_ALIGN_CENTER);

    gtk_widget_set_halign(label_nom, GTK_ALIGN_START);

    gtk_box_append(GTK_BOX(box_container), label_nom);





    /*setup espacement*/
    GtkWidget *espacement = gtk_label_new(" ");

    gtk_widget_set_valign(espacement, GTK_ALIGN_CENTER);

    gtk_widget_set_halign(espacement, GTK_ALIGN_FILL);
    gtk_widget_set_hexpand(espacement, 1);

    gtk_box_append(GTK_BOX(box_container), espacement);






    /*setup bouton modif*/

    GtkWidget *boutton_modif = gtk_button_new_with_label("modifier");
    
    gtk_widget_set_valign(label_nom, GTK_ALIGN_CENTER);

    gtk_widget_set_halign(label_nom, GTK_ALIGN_END);

    gtk_box_append(GTK_BOX(box_container), boutton_modif);





    /*setup bouton ajout*/

    GtkWidget *boutton_ajout = gtk_button_new_with_label("ajouter");
    
    gtk_widget_set_valign(label_nom, GTK_ALIGN_CENTER);

    gtk_widget_set_halign(label_nom, GTK_ALIGN_END);

    gtk_box_append(GTK_BOX(box_container), boutton_ajout);





    /*setup bouton supprimer*/

    GtkWidget *boutton_supprimer = gtk_button_new_with_label("supprimer");
    
    gtk_widget_set_valign(label_nom, GTK_ALIGN_CENTER);

    gtk_widget_set_halign(label_nom, GTK_ALIGN_END);

    gtk_box_append(GTK_BOX(box_container), boutton_supprimer);





    /*setup separation*/

    GtkWidget *separator = gtk_separator_new(GTK_ORIENTATION_HORIZONTAL);

    gtk_flow_box_append(GTK_FLOW_BOX(box_holder), separator);
    




    gtk_flow_box_append(GTK_FLOW_BOX(flowbox), box_holder);

}










/*________________________________________________________________________________*/











GtkWidget *page_recette(passage_tab_t *passage_tab){
    
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





    /*setup add_button*/

    GtkWidget *add_button = gtk_button_new_with_label("nouvelle recette");

    gtk_widget_set_halign(add_button, GTK_ALIGN_END);

    gtk_widget_set_size_request(add_button, 200, 50);
    
    gtk_box_append(GTK_BOX(box_on_top), add_button);




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




    /*ajout des recettes enregistre*/

    for (int i = 0; i < passage_tab -> liste_recette -> nb_string; i++){
        init_affiche_recette(flowbox2, i, passage_tab);
    }

    return flowbox1;
}