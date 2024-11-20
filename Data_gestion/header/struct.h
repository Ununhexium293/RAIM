#ifndef STRUCT_H
#define STRUCT_H

/*tableau dynamique de string*/
typedef struct tab_string_{
    char **tb_string;
    int nb_string;
    int taille_tab;
}tab_string_t;


//_____________________________COUPLE INGREDIENT NOM - UNITE _____________________________
/*Structure liant le nom d'un ingredient a son unité de mesure*/

typedef struct ingredient_nom_unite_{
    char *nom;
    /*l'unité sera uniquement composé d'un char pour des raison de mémoire occupée et c'est amplement suffisant d'ailleur*/
    char unite;
}ingredient_nom_unite_t;

typedef struct tab_ingredient_nom_unite_{
    ingredient_nom_unite_t **tab_ingredient_unite;
    int nb_ingredient;
    int taille_tab;
}tab_ingredient_nom_unite_t;


//_____________________________COUPLE INGREDIENT QUANTITE_____________________________
/*Structure contenant un ingrédient et sa quantité numerique associée*/
/*ATTETION : ICI EXCEPTIONNELLEMENT JE FORCE D'AVOIR UN ID INGREDIENT POUR POUVOIR ETRE REUTILISE POUR LES RECETTE ET PAS AVOIR UN 
TABLEAU DE INT DE TAILLE NOMBRE TOTAL DINGREDIENT POUR CHAQUE RECETTE  (Ok bien)*/
typedef struct ingredient_quantite_{
    int id_ingredient;
    int quantite;
}ingredient_quantite_t;

//_____________________________TABLEAU DYNAMIQUE POUR INGREDIENTS ET LEUR QUANTITE_____________________________
/*__________POUR INVENTAIRE ET RECETTE__________*/

/*Structure pour tableau dynamique de couble ingredient quantite*/
typedef struct tab_ingredients_{
    int nb_ingredient;
    int taille_tab;
    ingredient_quantite_t **tab_ingredient_quantite;
}tab_ingredients_t;


//_____________________________TABLEAU DYNAMIQUE POUR LISTE DE RECETTE_____________________________

/*Structure pour tableau dynamique de recette_ingredients*/
typedef struct tab_recette_ingredients_{
    tab_ingredients_t **recette_ingredients;
    int taille_tab;
    int nb_recette;
}tab_recette_ingredients_t;

/*_________________________________________________________________________________________________________*/



#endif