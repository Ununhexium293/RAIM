#ifndef STRUCT_H
#define STRUCT_H


//_____________________________TABLEAU DE NOMS_____________________________
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



//_____________________________COUPLE INGREDIENT QUANTITE_____________________________
/*Structure contenant un ingrédient et sa quantité numerique associée*/
typedef struct ingredient_quantite_{
    int id_ingredient;
    int quantite;
}ingredient_quantite;


//_____________________________TABLEAU DYNAMIQUE POUR INVENTAIRE_____________________________
/*__________NE PAS UTILISER POUR AUTRE CHOSE QU'INVENTAIRE__________*/
/*Structure pour tableau dynamique de couble ingredient quantite*/
typedef struct tab_ingredients_{
    int nb_ingredient;
    int taille_tab;
    ingredient_quantite * tab_ingredient_quantite;
}tab_ingredients;

//_____________________________TABLEAU DYNAMIQUE POUR LISTE DE RECETTE_____________________________


/*Structure contenant un tableau de recette, le nombre de recette et la taille du tableau pour les tableau dynamique*/
typedef struct recette_ingredients_{
    int id_recette;
    int taille_tab_ingredient;
    int nb_ingredient;
    ingredient_quantite * tab_ingredient_quantite;
}recette_ingredients;


/*Structure pour tableau dynamique de recette_ingredients*/
typedef struct tab_recette_ingredients_{
    recette_ingredients * recette_ingredients;
    int taille_tab;
    int nb_recette;
}tab_recette_ingredients;

















#endif