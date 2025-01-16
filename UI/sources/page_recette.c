#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include "../header/pages.h"
#include "../header/struct_passage.h"
#include "../header/struct_passage_gestion.h"
#include "../../Data_gestion/header/gestion_types.h"

/*a faire*/
/*fonction ajout recette*/
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


static void create_recipe(GtkWidget *widget, gpointer data){
    passage_changement_page *changement = data;

    gtk_stack_set_visible_child(changement -> stack, changement -> page);
}


static void rm_recette(passage_tab_t *passage_tab, int id_recette){
    remove_tab_string(passage_tab -> liste_recette, id_recette);
    remove_tab_recette(passage_tab -> liste_link, id_recette);
}





static void button_rm_recette(GtkWidget *widget, gpointer data);

static void button_add_recette_menu(GtkWidget *widget, gpointer data);






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





    /*setup bouton ajout*/

    GtkWidget *boutton_ajout = gtk_button_new_with_label("ajouter");
    
    gtk_widget_set_valign(label_nom, GTK_ALIGN_CENTER);

    gtk_widget_set_halign(label_nom, GTK_ALIGN_END);

    gtk_box_append(GTK_BOX(box_container), boutton_ajout);

    g_signal_connect(boutton_ajout, "clicked", G_CALLBACK(button_add_recette_menu), passage_tab);




    /*setup bouton supprimer*/

    GtkWidget *boutton_supprimer = gtk_button_new_with_label("supprimer");
    
    gtk_widget_set_valign(label_nom, GTK_ALIGN_CENTER);

    gtk_widget_set_halign(label_nom, GTK_ALIGN_END);

    gtk_box_append(GTK_BOX(box_container), boutton_supprimer);

    g_signal_connect(boutton_supprimer, "clicked", G_CALLBACK(button_rm_recette), passage_tab);





    /*setup separation*/

    GtkWidget *separator = gtk_separator_new(GTK_ORIENTATION_HORIZONTAL);

    gtk_flow_box_append(GTK_FLOW_BOX(box_holder), separator);





    gtk_flow_box_append(GTK_FLOW_BOX(flowbox), box_holder);

}





void update_visual_recette(GtkWidget *widget, gpointer data){

    update_page_t *update_page_recette = data;

    GtkWidget *temp = update_page_recette -> page;

    GtkWidget *scroll_window = gtk_flow_box_child_get_child(gtk_flow_box_get_child_at_index(GTK_FLOW_BOX(temp),2));
    GtkWidget *flowbox = gtk_viewport_get_child(GTK_VIEWPORT(gtk_scrolled_window_get_child(GTK_SCROLLED_WINDOW(scroll_window))));

    gtk_flow_box_remove_all(GTK_FLOW_BOX(flowbox));

    for (int i = 0; i < update_page_recette -> passage_tab -> liste_recette -> nb_string; i++){
        init_affiche_recette(flowbox, i, update_page_recette -> passage_tab);
    }

} 


static void button_add_recette_menu(GtkWidget *widget, gpointer data){

    passage_tab_t *passage_tab = data;

    GtkWidget *box_container = gtk_widget_get_parent(widget);
    GtkWidget *box_holder = gtk_widget_get_parent(gtk_widget_get_parent(box_container));
    GtkWidget *label = gtk_flow_box_child_get_child(gtk_flow_box_get_child_at_index(GTK_FLOW_BOX(box_holder), 0));
    
    /*get the id of the recipe*/ 
    int id_recette = atoi(gtk_label_get_text(GTK_LABEL(label)));

    if (update_tab_inv(passage_tab,passage_tab  -> liste_link -> recette_ingredients[id_recette],-1) == -1){
        return;
    }

    add_tab_int(passage_tab -> liste_menu, id_recette);

    return;
}

static void button_rm_recette(GtkWidget *widget, gpointer data){

    passage_tab_t *passage_tab = data;

    GtkWidget *box_container = gtk_widget_get_parent(widget);
    GtkWidget *box_holder = gtk_widget_get_parent(gtk_widget_get_parent(box_container));
    GtkWidget *label = gtk_flow_box_child_get_child(gtk_flow_box_get_child_at_index(GTK_FLOW_BOX(box_holder), 0));
    
    /*get the id of the recipe*/ 
    int id_recette = atoi(gtk_label_get_text(GTK_LABEL(label)));

    /*remove the recipe from data*/
    rm_recette(passage_tab, id_recette);

    /*update the visual*/
    GtkWidget *flowbox_scrolled_window = gtk_widget_get_parent(gtk_widget_get_parent(box_holder));

    gtk_flow_box_remove_all(GTK_FLOW_BOX(flowbox_scrolled_window));

    for (int i = 0; i < passage_tab -> liste_recette -> nb_string; i++){
        init_affiche_recette(flowbox_scrolled_window, i, passage_tab);
    }

}



int update_tab_inv(passage_tab_t *passage_tab, tab_ingredients_t* Recette, int mode){
    //Mode add = 1
    //Mode del = -1
    int i ,indice,qt_inv,qt_recette;
    if(mode == -1){
        for(i = 0;i<Recette->nb_ingredient;i++){
            indice = Recette -> tab_ingredient_quantite[i] -> id_ingredient -1 ;
            qt_recette = Recette -> tab_ingredient_quantite[i] -> quantite;
            qt_inv = passage_tab -> liste_inventaire -> tab_ingredient_quantite[indice] -> quantite;
            if(qt_inv < qt_recette){
                return -1;
            }
        }

        for(i = 0;i<Recette->nb_ingredient;i++){
            indice = Recette -> tab_ingredient_quantite[i] -> id_ingredient -1;
            passage_tab -> liste_inventaire -> tab_ingredient_quantite[indice] -> quantite -= Recette -> tab_ingredient_quantite[i] -> quantite;
        }
    }else{
        for(i = 0;i<Recette->nb_ingredient;i++){
            indice = Recette -> tab_ingredient_quantite[i] -> id_ingredient -1;
            passage_tab -> liste_inventaire -> tab_ingredient_quantite[indice] -> quantite += Recette -> tab_ingredient_quantite[i] -> quantite;
        }
        
    }

    return 1;
}






/*________________________________________________________________________________*/











GtkWidget *page_recette(GtkWidget *stack, passage_tab_t *passage_tab){

    
    
    /*setup flowbox*/

    GtkWidget *flowbox1 = gtk_flow_box_new();


    gtk_widget_set_valign(flowbox1, GTK_ALIGN_START);
    gtk_widget_set_vexpand(flowbox1, 1);

    gtk_widget_set_halign(flowbox1, GTK_ALIGN_FILL);
    gtk_widget_set_hexpand(flowbox1, 1);
    
    gtk_flow_box_set_max_children_per_line(GTK_FLOW_BOX(flowbox1), 1);
    gtk_flow_box_set_selection_mode(GTK_FLOW_BOX(flowbox1), GTK_SELECTION_NONE);
    
    gtk_stack_add_child(GTK_STACK(stack), flowbox1);




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

    GtkWidget *page_sub = page_creation_recette(stack, flowbox1, passage_tab);

    g_signal_connect(add_button, "clicked", G_CALLBACK(create_recipe), init_changement_page(stack, page_sub));




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