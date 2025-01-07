#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include "../header/struct_passage.h"
#include "../../Data_gestion/header/read_data.h"

passage_changement_page *init_changement_page(GtkWidget *stack, GtkWidget *page){

    passage_changement_page *changement = malloc(sizeof(passage_changement_page));

    if (changement == NULL){
        exit(EXIT_FAILURE);
    }

    changement -> stack = GTK_STACK(stack);
    changement -> page = page;

    return changement;
}

passage_tab_t *init_passage_tab(void){
    passage_tab_t *passage_tab = malloc(sizeof(passage_tab_t));

    if (passage_tab == NULL){
        exit(EXIT_FAILURE);
    }

    passage_tab -> liste_ingredient = read_ingredient();
    passage_tab -> liste_inventaire = read_inventaire();
    passage_tab -> liste_link = read_database();
    passage_tab -> liste_recette = read_recette();

    return passage_tab;
}

update_page_t *init_update_page(passage_tab_t *passage_tab, GtkWidget *page){
    
    update_page_t *update_page_recette = malloc(sizeof(update_page_t));

    if (update_page_recette == NULL){
        exit(EXIT_FAILURE);
    }

    update_page_recette -> passage_tab = passage_tab;
    update_page_recette -> page = page; 

    return update_page_recette;
}