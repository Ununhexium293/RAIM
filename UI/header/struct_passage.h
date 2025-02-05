#ifndef STRUCT_PASSAGE_H
#define STRUCT_PASSAGE_H

#include "../../Data_gestion/header/struct.h"

typedef struct passage_tab_{
    tab_string_t *liste_recette;
    tab_ingredient_nom_unite_t *liste_ingredient;
    tab_ingredients_t *liste_inventaire;
    tab_recette_ingredients_t *liste_link;
    tab_int_t *liste_menu;
} passage_tab_t;

typedef struct passage_changement_page_{
    GtkStack *stack;
    GtkWidget *page;
} passage_changement_page;

typedef struct update_page_{
    passage_tab_t *passage_tab;
    GtkWidget *page;
}update_page_t;

typedef struct validate_function_pass_{
    passage_tab_t *passage_tab;
    passage_changement_page *changement;
}validate_function_pass_t;

#endif