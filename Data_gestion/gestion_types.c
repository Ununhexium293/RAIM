typedef struct Ingredient_{
    /*Relie des ingredient a ses quantités*/
    int id_ingredient;
    int quantité;
}Ingredient;

typedef struct Recette_{
    /*Relie un id de recette a une liste de la struct Ingredient*/
    int id;
    Ingredient liste[MAX_INGREDIENTS];
    int nb_ing;
}Recette;