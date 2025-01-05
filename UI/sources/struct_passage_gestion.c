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