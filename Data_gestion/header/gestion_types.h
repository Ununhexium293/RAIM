#ifndef GESTION_TYPE_H
#define GESTION_TYPE_H


/*________________tab dynamique string________________*/

/*Crée un tableau dynamique de string de taille size_tab + 5 sur le tas et renvoit le pointeur vers celui-ci*/
tab_string_t *init_tab_string(int size_tab);

/*Libere l'espace alloué au tableau dynamique de string tab_string*/
void free_tab_string(tab_string_t *tab_string);

/*Ajoute le string string_e au tableau tab_string, s'il n'y a pas de place, double la taille du tableau avant d'ajouter le string, et incremente la variable tab_string -> nb_string*/
void add_tab_string(tab_string_t *tab_string, char *string_e);

/*Retire le string à l'emplacement indice du tableau tab_string et avance d'un indice tous les elements suivant du tableau, renvoit -1 si l'indice est trop grand, 0 sinon*/
int remove_tab_string(tab_string_t *tab_string, int indice);


/*________________tableau dynamique couple nom - unite________________*/

/*Crée un tableau dynamique de couple nom - unite de taille size_tab + 5 sur le tas et renvoit le pointeur vers celui-ci*/
tab_ingredient_nom_unite_t *init_tab_ingredient_nom_unite(int size_tab);

/*Libere l'espace alloué au tableau dynamique de couple nom - unite tab_ingredient_nom_unite*/
void free_tab_ingredient_nom_unite(tab_ingredient_nom_unite_t *tab_ingredient_nom_unite);

/*Ajoute le couple (string, unit) au tableau tab_ingredient_nom_unite, s'il n'y a pas de place, double la taille du tableau avant d'ajouter le couple, et incremente la variable tab_ingredient_nom_unite -> nb_ingredient*/
void add_tab_ingredient_nom_unite(tab_ingredient_nom_unite_t *tab_ingredient_nom_unite, char *string, char unit);

/*Retire le couple nom - unite à l'emplacement indice du tableau tab_ingredient_nom_unite et avance d'un indice tous les elements suivant du tableau, renvoit -1 si l'indice est trop grand, 0 sinon*/
int remove_tab_ingredient_nom_unite(tab_ingredient_nom_unite_t *tab_ingredient_nom_unite, int indice);


/*________________tableau dynamique couple nom - quantite________________*/

/*Crée un tableau dynamique de couple nom - quantite de taille size_tab + 5 sur le tas et renvoit le pointeur vers celui-ci*/
tab_ingredients_t *init_tab_ingredient(int size_array);

/*Libere l'espace alloué au tableau dynamique de couple nom - quantite tab_ingredient*/
void free_tab_ingredient(tab_ingredients_t *tab_ingredient);

/*Ajoute le couple (id_ingredient, unit) au tableau tab_ingredient, s'il n'y a pas de place, double la taille du tableau avant d'ajouter le couple, et incremente la variable tab_ingredient -> nb_ingredient*/
void add_tab_ingredient(tab_ingredients_t *tab_ingredient, int id_ingredient, int quantity);

/*Retire le couple nom - quantite à l'emplacement indice du tableau tab_ingredient et avance d'un indice tous les elements suivant du tableau, renvoit -1 si l'indice est trop grand, 0 sinon*/
int remove_tab_ingredient(tab_ingredients_t *tab_ingredient, int indice);


/*________________tableau dynamique recette ingredient________________*/

/*Crée un tableau dynamique de tab_ingredient de taille size_tab + 5 sur le tas et renvoit le pointeur vers celui-ci*/
tab_recette_ingredients_t *init_tab_recette(int size_array);

/*Libere l'espace alloué au tableau dynamique de tab_ingredient tab_recette*/
void free_tab_recette(tab_recette_ingredients_t *tab_recette);

/*Ajoute le tableau d'ingredient au tableau tab_recette, s'il n'y a pas de place, double la taille du tableau avant d'ajouter le couple, et incremente la variable tab_recette -> nb_rectte*/
void add_tab_recette(tab_recette_ingredients_t *tab_recette, tab_ingredients_t *tab_ingredient);

/*Retire le tableau d'ingredient à l'emplacement indice du tableau tab_recette et avance d'un indice tous les elements suivant du tableau, renvoit -1 si l'indice est trop grand, 0 sinon*/
int remove_tab_recette(tab_recette_ingredients_t *tab_recette, int indice);


/*________________tab dynamique int________________*/

/*Crée un tableau dynamique de string de taille size_tab + 5 sur le tas et renvoit le pointeur vers celui-ci*/
tab_int_t *init_tab_int(int size_tab);

/*Libere l'espace alloué au tableau dynamique de string tab_string*/
void free_tab_int(tab_int_t *tab_int);

/*Ajoute le string string_e au tableau tab_string, s'il n'y a pas de place, double la taille du tableau avant d'ajouter le string, et incremente la variable tab_string -> nb_string*/
void add_tab_int(tab_int_t *tab_int, int int_e);

/*Retire le string à l'emplacement indice du tableau tab_string et avance d'un indice tous les elements suivant du tableau, renvoit -1 si l'indice est trop grand, 0 sinon*/
int remove_tab_int(tab_int_t *tab_int, int indice);

#endif