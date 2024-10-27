#ifndef STRUCT_H
#define STRUCT_H

/*Tableau dynamique pour stocker les recettes et leur nombre*/
typedef struct tab_nom_recette_{
    char **tb_recette;
    int nb_recette;
    int taille_tab;
}tab_nom_recette_t;

/*Tableau dynamique pour stocker les ingredients et leur nombre*/
typedef struct tab_nom_ingredient_{
    char **tb_ingredient;
    int nb_ingredient;
    int taille_tab;
}tab_nom_ingredient_t;

/*Structure contenant un ingrédient et sa quantité numerique associée*/
typedef struct ingredient_quantite_{
    int id_ingredient;
    int quantite;
}ingredient_quantite;

/*Structure contenant un id de recette et un tableau d'ingredients et leur quantité avec*/
typedef struct recette_ingredients_{
    int id;
    int taille_ingredient;
    ingredient_quantite * liste_ingredient;
}recette_ingredients;

/*Structure contenant un tableau de recette, le nombre de recette et la taille du tableau pour les tableau dynamique*/
typedef struct liste_recette_ingredients_{
    int taille_tab;
    int nb_recette;
    recette_ingredients * tb_recette_ingredients;
}liste_recette_ingredients;

















#endif