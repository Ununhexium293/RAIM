#include <stdio.h>
#include <stdlib.h>
#include </home/quentin/Documents/EI3A/Projet/gestion_recette/rep_git/Data_gestion/source/struct.h>//à changer pour l'avoir dans le makefile et chemin relatif

//#define DEBUG
//#include <assert.h> /* Pour debug */


/*_______________________________gestion tableau dynamique___________________________________________*/





/*Donne la taille d'un char* */
static int len_string(char *string){
    int taille = 0;
    for (; string[taille] != '\0'; taille++);
    return taille;
}


/*Permet de copier un string sans copier les adresses*/
static void cp_string(char *donnor, char *reciever){
    for (int i = 0; i <= len_string(donnor); i++){
        reciever[i] = donnor[i];
    }
}





/*________________tab dynamique string____________________*/





/*initialise un tableau dynamique de string*/
tab_string_t *init_tab_string(int size_tab){
    tab_string_t *tab_string = malloc(sizeof(tab_string_t));

    if (tab_string == NULL){
        exit(EXIT_FAILURE);
    }

    char **tb_string = malloc(sizeof(char*) * (size_tab + 5)); //on ajoute quelques emplacemnet libre en plus si jamais on souhaite faire de petits ajouts

    if (tb_string == NULL){
        exit(EXIT_FAILURE);
    }

    tab_string -> tb_string = tb_string;
    tab_string -> nb_string = 0;
    tab_string -> taille_tab = size_tab + 5;

    return tab_string;
}


/*libere la memoire allouée au tableau dynamique de string*/
void free_tab_string(tab_string_t *tab_string){

    for (int i = 0; i < tab_string -> nb_string; i++){
        free(tab_string -> tb_string[i]);
    }

    free(tab_string -> tb_string);
    free(tab_string);
}


/*ajoute une entrée dans dans le tableau tab_string*/
void add_tab_string(tab_string_t *tab_string, char *string_e){

    if (tab_string -> nb_string == tab_string -> taille_tab){     //Si il n'y a plus de place dans le tableau, on double la taille de celui-ci
        
        char **tb_string_sub = malloc(sizeof(char*) * (tab_string -> taille_tab) * 2);

        if (tb_string_sub == NULL){
            exit(EXIT_FAILURE);
        }
        
        for (int i = 0; i < tab_string -> taille_tab; i++){       //copie l'ancien tableau dans le nouveau
            tb_string_sub[i] = tab_string -> tb_string[i];
        }

        tab_string -> taille_tab *= 2;

        free(tab_string -> tb_string);      //On libere la mémoire alloué à l'ancien tableau
        tab_string -> tb_string = tb_string_sub;
    }

    char *string_bis = malloc(sizeof(char) * len_string(string_e) + 1);

    if (string_bis == NULL){
        exit(EXIT_FAILURE);
    }

    cp_string(string_e, string_bis);

    tab_string -> tb_string[tab_string -> nb_string] = string_bis;
    tab_string -> nb_string += 1;
}


/*supprime une entrée du tableau et avance les élément suivants*/
int remove_tab_string(tab_string_t *tab_string, int indice){

    if (indice >= tab_string -> nb_string){       //On verifie que l'element que l'on souhaite supprimer existe (pourras etre enlever plus tard / fais pour du debug principalement au cas où)
        printf("Impossible de supprimer la chaine de charactere, indice trop grand.\n");
        return -1;
    }

    free(tab_string -> tb_string[indice]);

    for (int i = indice; i < tab_string -> nb_string - 1; i++){     //Comme on suprime un element du tableau, on dessend les élément qui le suivent d'un cran
        tab_string -> tb_string[i] = tab_string -> tb_string[i + 1];
    }

    tab_string -> nb_string -= 1;

    return 0;
}





/*___________________________________tableau dynamique couple nom - unite______________________________________*/





/*initialise un couple nom - unite*/
static ingredient_nom_unite_t *init_couple_ingr_unit(char *string, char unit){
    ingredient_nom_unite_t *couple = malloc(sizeof(ingredient_nom_unite_t));

    if (couple == NULL){
        exit(EXIT_FAILURE);
    }
    
    char *name_bis = malloc(sizeof(char) * len_string(string) + 1);

    if (name_bis == NULL){
        exit(EXIT_FAILURE);
    }

    cp_string(string, name_bis);

    couple -> nom = name_bis;
    couple -> unite = unit;

    return couple;
}


/*libere la memoire alloué à un couple ingredient unite*/
static void free_couple_ingr_unit(ingredient_nom_unite_t *couple_ingr_unit){
    free(couple_ingr_unit -> nom);

    free(couple_ingr_unit);
}



/*initialise un tableau dynamique de couple nom - unite*/
tab_ingredient_nom_unite_t *init_tab_ingredient_nom_unite(int size_tab){
    tab_ingredient_nom_unite_t *tab_ingredient_nom_unite = malloc(sizeof(tab_ingredient_nom_unite_t));

    if (tab_ingredient_nom_unite == NULL){
        exit(EXIT_FAILURE);
    }

    ingredient_nom_unite_t **tb_ingredient_nom_unite = malloc(sizeof(ingredient_nom_unite_t *) * (size_tab + 5));  //on ajoute quelques emplacemnet libre en plus si jamais on souhaite faire de petits ajouts

    if (tb_ingredient_nom_unite == NULL){
        exit(EXIT_FAILURE);
    }

    tab_ingredient_nom_unite -> nb_ingredient = 0;
    tab_ingredient_nom_unite -> taille_tab = size_tab + 5;
    tab_ingredient_nom_unite -> tab_ingredient_unite = tb_ingredient_nom_unite;

    return tab_ingredient_nom_unite;
}


/*libere la memoire alloué à un tableau tab_ingredient_nom_unite*/
void free_tab_ingredient_nom_unite(tab_ingredient_nom_unite_t *tab_ingredient_nom_unite){

    for (int i = 0; i < tab_ingredient_nom_unite -> nb_ingredient; i++){
        free_couple_ingr_unit(tab_ingredient_nom_unite -> tab_ingredient_unite[i]);
    }

    free(tab_ingredient_nom_unite -> tab_ingredient_unite);
    free(tab_ingredient_nom_unite);
}


/*ajoute une entree dans le tableau tab_ingredient_nom_unite*/
void add_tab_ingredient_nom_unite(tab_ingredient_nom_unite_t *tab_ingredient_nom_unite, char *string, char unit){

    ingredient_nom_unite_t *couple = init_couple_ingr_unit(string, unit);

    if (tab_ingredient_nom_unite -> nb_ingredient == tab_ingredient_nom_unite -> taille_tab){   //Si il n'y a plus de place dans le tableau, on double la taille de celui-ci

        ingredient_nom_unite_t **tb_ingredient_nom_unite = malloc(sizeof(ingredient_nom_unite_t *) * tab_ingredient_nom_unite -> taille_tab * 2);

        if (tb_ingredient_nom_unite == NULL){
            exit(EXIT_FAILURE);
        }

        for (int i = 0; i < tab_ingredient_nom_unite -> taille_tab; i++){   //copie l'ancien tableau dans le nouveau
            tb_ingredient_nom_unite[i] = tab_ingredient_nom_unite -> tab_ingredient_unite[i];
        }

        tab_ingredient_nom_unite -> taille_tab *= 2;

        free(tab_ingredient_nom_unite -> tab_ingredient_unite);     //On libere la mémoir alloué à l'ancien tableau
        tab_ingredient_nom_unite -> tab_ingredient_unite = tb_ingredient_nom_unite;
    }

    tab_ingredient_nom_unite -> tab_ingredient_unite[tab_ingredient_nom_unite -> nb_ingredient] = couple;
    tab_ingredient_nom_unite -> nb_ingredient += 1;
}


/*supprime une entrée du tableau et avance les élément suivants*/
int remove_tab_ingredient_nom_unite(tab_ingredient_nom_unite_t *tab_ingredient_nom_unite, int indice){

    if (indice >= tab_ingredient_nom_unite -> nb_ingredient){       //On verifie que l'element que l'on souhaite supprimer existe (pourras etre enlever plus tard / fais pour du debug principalement au cas où)
        printf("Impossible de supprimer le couple ingredient nom - unite, indice trop grand.\n");
        return -1;
    }

    free_couple_ingr_unit(tab_ingredient_nom_unite -> tab_ingredient_unite[indice]);

    for (int i = indice; i < tab_ingredient_nom_unite -> nb_ingredient - 1; i++){       //Comme on suprime un element du tableau, on dessend les élément qui le suivent d'un cran
        tab_ingredient_nom_unite -> tab_ingredient_unite[i] = tab_ingredient_nom_unite -> tab_ingredient_unite[i + 1];
    }

    tab_ingredient_nom_unite -> nb_ingredient -= 1;

    return 0;
}





/*___________________________________tableau dynamique couple nom - quantite______________________________________*/





/*initialise un couple id_ingredient - quantite*/
static ingredient_quantite_t *init_ingredient_quantity(int id, int quantity){
    ingredient_quantite_t *couple = malloc(sizeof(ingredient_quantite_t));

    if (couple == NULL){
        exit(EXIT_FAILURE);
    }

    couple -> id_ingredient = id;
    couple -> quantite = quantity;

    return couple;
}


/*initialise un tableau dynamique de couple id_ingredient - quantite*/
tab_ingredients_t *init_tab_ingredient(int size_array){
    tab_ingredients_t *tab_ingredient = malloc(sizeof(tab_ingredients_t));

    if (tab_ingredient == NULL){
        exit(EXIT_FAILURE);
    }

    ingredient_quantite_t **tab_ingredient_quantite = malloc(sizeof(ingredient_quantite_t *) * (size_array + 5));   //on ajoute quelques emplacemnet libre en plus si jamais on souhaite faire de petits ajouts

    if (tab_ingredient_quantite == NULL){
        exit(EXIT_FAILURE);
    }

    tab_ingredient -> nb_ingredient = 0;
    tab_ingredient -> taille_tab = size_array + 5;
    tab_ingredient -> tab_ingredient_quantite = tab_ingredient_quantite;

    return tab_ingredient;
}

/*libere la memoire allouée au tableau tab_ingredient*/
tab_ingredients_t *free_tab_ingredient(tab_ingredients_t *tab_ingredient){
    
    for (int i = 0; i < tab_ingredient -> nb_ingredient; i++){
        free(tab_ingredient -> tab_ingredient_quantite[i]);
    }
    

    free(tab_ingredient -> tab_ingredient_quantite);
    free(tab_ingredient);

    return 0;
}

/*ajoute une entrée dans dans le tableau tab_ingredient*/
void add_tab_ingredient(tab_ingredients_t *tab_ingredient, int id_ingredient, int quantity){

    if(tab_ingredient -> nb_ingredient == tab_ingredient -> taille_tab){    //Si il n'y a plus de place dans le tableau, on double la taille de celui-ci

        ingredient_quantite_t **tab_ingredient_quantite = malloc(sizeof(ingredient_quantite_t *) * (tab_ingredient -> taille_tab) * 2);

        if (tab_ingredient_quantite == NULL){
            exit(EXIT_FAILURE);
        }

        for (int i = 0; i < tab_ingredient -> nb_ingredient; i++){      //copie l'ancien tableau dans le nouveau
            tab_ingredient_quantite[i] = tab_ingredient -> tab_ingredient_quantite[i];
        }

        tab_ingredient -> taille_tab *= 2;

        free(tab_ingredient -> tab_ingredient_quantite);        //On libere la mémoir alloué à l'ancien tableau
        tab_ingredient -> tab_ingredient_quantite = tab_ingredient_quantite;
    }

    ingredient_quantite_t *couple = init_ingredient_quantity(id_ingredient, quantity);

    tab_ingredient -> tab_ingredient_quantite[tab_ingredient -> nb_ingredient] = couple;
    tab_ingredient -> nb_ingredient += 1;
}


/*supprime une entrée du tableau et avance les élément suivants*/
int remove_tab_ingredient(tab_ingredients_t *tab_ingredient, int indice){

    if (indice >= tab_ingredient -> nb_ingredient){     //On verifie que l'element que l'on souhaite supprimer existe (pourras etre enlever plus tard / fais pour du debug principalement au cas où)
        printf("Impossible de supprimer le couple id_ingredient quantite, indice trop grand.\n");
        return -1;
    }

    free(tab_ingredient -> tab_ingredient_quantite[indice]);

    for (int i = indice; i < tab_ingredient -> nb_ingredient - 1; i++){     //Comme on suprime un element du tableau, on dessend les élément qui le suivent d'un cran
        tab_ingredient -> tab_ingredient_quantite[i] = tab_ingredient -> tab_ingredient_quantite[i + 1];
    }

    tab_ingredient -> nb_ingredient -= 1;

    return 0;
}





/*___________________________________tableau dynamique recette ingredient______________________________________*/





/*initialise un tableau dynamique de tab_ingredients_t*/
tab_recette_ingredients_t *init_tab_recette(int size_array){
    tab_recette_ingredients_t *tab_recette = malloc(sizeof(tab_recette_ingredients_t));

    if (tab_recette == NULL){
        exit(EXIT_FAILURE);
    }

    tab_ingredients_t **tab_ingredient = malloc(sizeof(tab_ingredients_t *) * (size_array + 5));       //on ajoute quelques emplacemnet libre en plus si jamais on souhaite faire de petits ajouts

    if(tab_ingredient == NULL){
        exit(EXIT_FAILURE);
    }

    tab_recette -> recette_ingredients = tab_ingredient;
    tab_recette -> nb_recette = 0;
    tab_recette -> taille_tab = size_array + 5;

    return tab_recette;
}


/*libere la memoire allouée au tableau tab_recette*/
void free_tab_recette(tab_recette_ingredients_t *tab_recette){

    for (int i = 0; i < tab_recette -> nb_recette; i++){
        free_tab_ingredient(tab_recette -> recette_ingredients[i]);
    }

    free(tab_recette -> recette_ingredients);
    free(tab_recette);
}


/*ajoute une entrée dans le tableau*/
void add_tab_recette(tab_recette_ingredients_t *tab_recette, tab_ingredients_t *tab_ingredient){

    if (tab_recette -> nb_recette == tab_recette -> taille_tab){        //Si il n'y a plus de place dans le tableau, on double la taille de celui-ci

        tab_ingredients_t **recette_ingredients_sub = malloc(sizeof(tab_ingredients_t *) * (tab_recette -> taille_tab) * 2);
        
        if (recette_ingredients_sub == NULL){
            exit(EXIT_FAILURE);
        }

        for (int i = 0; i < tab_recette -> nb_recette; i++){        //copie l'ancien tableau dans le nouveau
            recette_ingredients_sub[i] = tab_recette -> recette_ingredients[i];
        }

        tab_recette -> taille_tab *= 2;

        free(tab_recette -> recette_ingredients);       //On libere la mémoire alloué à l'ancien tableau
        tab_recette -> recette_ingredients = recette_ingredients_sub;     
    }

    tab_recette -> recette_ingredients[tab_recette -> nb_recette] = tab_ingredient;
    tab_recette -> nb_recette += 1;
}


/*supprime une entrée du tableau et avance les éléments suivants*/
int remove_tab_recette(tab_recette_ingredients_t *tab_recette, int indice){

    if (indice >= tab_recette -> nb_recette){
        printf("Impossible de supprimer la recette, l'indice est trop grand");
        return -1;
    }

    free_tab_ingredient(tab_recette -> recette_ingredients[indice]);

    for (int i = indice; i < tab_recette -> nb_recette - 1; i++){
        tab_recette -> recette_ingredients[i] = tab_recette -> recette_ingredients[i + 1];
    }

    tab_recette -> nb_recette -= 1;
    return 0;
}







int main(void){

    #ifdef DEBUG

    /*test tableau de string*/

    printf("Debug tableau string :\n");

    tab_string_t *tab_string = init_tab_string(1);

    assert(tab_string -> taille_tab == 6);

    add_tab_string(tab_string, "test0");
    add_tab_string(tab_string, "test1");
    add_tab_string(tab_string, "test2");
    add_tab_string(tab_string, "test3");
    add_tab_string(tab_string, "test4");
    add_tab_string(tab_string, "test5");
    add_tab_string(tab_string, "test6");
    add_tab_string(tab_string, "test7");
    add_tab_string(tab_string, "test8");
    add_tab_string(tab_string, "test9");

    assert(tab_string -> nb_string == 10);

    assert(tab_string -> taille_tab == 12);

    printf("contenu case 5 : %s\n", tab_string -> tb_string[5]);

    remove_tab_string(tab_string, 5);

    printf("contenu case 5 : %s\n", tab_string -> tb_string[5]);
    assert(tab_string -> nb_string == 9);

    printf("contenu case 8 : %s\n", tab_string -> tb_string[8]);

    remove_tab_string(tab_string, 8);

    assert(tab_string -> nb_string == 8);

    printf("contenu case 0 : %s\n", tab_string -> tb_string[0]);

    free_tab_string(tab_string);

    /*fin test tableau de string*/

    

    /*test tableau de couple nom - unite*/

    printf("\nDebug tableau string :\n");

    tab_ingredient_nom_unite_t *tab_ingredient_nom_unite = init_tab_ingredient_nom_unite(1);

    assert(tab_ingredient_nom_unite -> taille_tab == 6);

    add_tab_ingredient_nom_unite(tab_ingredient_nom_unite, "test0", 't');
    add_tab_ingredient_nom_unite(tab_ingredient_nom_unite, "test1", 't');
    add_tab_ingredient_nom_unite(tab_ingredient_nom_unite, "test2", 't');
    add_tab_ingredient_nom_unite(tab_ingredient_nom_unite, "test3", 't');
    add_tab_ingredient_nom_unite(tab_ingredient_nom_unite, "test4", 't');
    add_tab_ingredient_nom_unite(tab_ingredient_nom_unite, "test5", 't');
    add_tab_ingredient_nom_unite(tab_ingredient_nom_unite, "test6", 't');
    add_tab_ingredient_nom_unite(tab_ingredient_nom_unite, "test7", 't');
    add_tab_ingredient_nom_unite(tab_ingredient_nom_unite, "test8", 't');
    add_tab_ingredient_nom_unite(tab_ingredient_nom_unite, "test9", 't');

    assert(tab_ingredient_nom_unite -> nb_ingredient == 10);
    assert(tab_ingredient_nom_unite -> taille_tab == 12);
    
    printf("contenu case 5 : %s\n", tab_ingredient_nom_unite -> tab_ingredient_unite[5] -> nom);

    remove_tab_ingredient_nom_unite(tab_ingredient_nom_unite, 5);

    printf("contenu case 5 : %s\n", tab_ingredient_nom_unite -> tab_ingredient_unite[5] -> nom);
    printf("contenu case 8 : %s\n", tab_ingredient_nom_unite -> tab_ingredient_unite[8] -> nom);

    assert(tab_ingredient_nom_unite -> nb_ingredient == 9);

    remove_tab_ingredient_nom_unite(tab_ingredient_nom_unite, 8);

    assert(tab_ingredient_nom_unite -> nb_ingredient == 8);

    printf("contenu case 0 : %s\n", tab_ingredient_nom_unite -> tab_ingredient_unite[0] -> nom);

    free_tab_ingredient_nom_unite(tab_ingredient_nom_unite);

    /*fin test tableau de couple nom - unite*/


    /*test tableau couple nom - quantite*/

    printf("\nDebug tableau couple nom - quantite :\n");

    tab_ingredients_t *tab_ingredient = init_tab_ingredient(1);

    assert(tab_ingredient -> taille_tab == 6);

    add_tab_ingredient(tab_ingredient, 0, 5);
    add_tab_ingredient(tab_ingredient, 1, 5);
    add_tab_ingredient(tab_ingredient, 2, 5);
    add_tab_ingredient(tab_ingredient, 3, 5);
    add_tab_ingredient(tab_ingredient, 4, 5);
    add_tab_ingredient(tab_ingredient, 5, 5);
    add_tab_ingredient(tab_ingredient, 6, 5);
    add_tab_ingredient(tab_ingredient, 7, 5);
    add_tab_ingredient(tab_ingredient, 8, 5);
    add_tab_ingredient(tab_ingredient, 9, 5);

    assert(tab_ingredient -> taille_tab == 12);
    assert(tab_ingredient -> nb_ingredient == 10);

    printf("contenu case 5 : %d\n", tab_ingredient -> tab_ingredient_quantite[5] -> id_ingredient);

    remove_tab_ingredient(tab_ingredient, 5);

    printf("contenu case 5 : %d\n", tab_ingredient -> tab_ingredient_quantite[5] -> id_ingredient);
    printf("contenu case 8 : %d\n", tab_ingredient -> tab_ingredient_quantite[8] -> id_ingredient);
    assert(tab_ingredient -> nb_ingredient == 9);

    remove_tab_ingredient(tab_ingredient, 8);

    assert(tab_ingredient -> nb_ingredient == 8);

    printf("contenu case 0 : %d\n", tab_ingredient -> tab_ingredient_quantite[0] -> id_ingredient);

    free_tab_ingredient(tab_ingredient);

    
    
    /*fin test tableau couple nom - quantite*/


    /*test tableau rectte ingredient*/

    printf("\nDebug tableau recette ingredient :\n");

    tab_recette_ingredients_t *tab_recette = init_tab_recette(1);

    assert(tab_recette -> taille_tab == 6);


    tab_ingredients_t *tab_ingredient0 = init_tab_ingredient(1);

    add_tab_ingredient(tab_ingredient0, 0, 0);
    add_tab_ingredient(tab_ingredient0, 1, 0);
    add_tab_ingredient(tab_ingredient0, 2, 0);
    add_tab_ingredient(tab_ingredient0, 3, 0);
    add_tab_ingredient(tab_ingredient0, 4, 0);

    tab_ingredients_t *tab_ingredient1 = init_tab_ingredient(1);

    add_tab_ingredient(tab_ingredient1, 0, 1);
    add_tab_ingredient(tab_ingredient1, 1, 1);
    add_tab_ingredient(tab_ingredient1, 2, 1);
    add_tab_ingredient(tab_ingredient1, 3, 1);
    add_tab_ingredient(tab_ingredient1, 4, 1);

    tab_ingredients_t *tab_ingredient2 = init_tab_ingredient(1);

    add_tab_ingredient(tab_ingredient2, 0, 2);
    add_tab_ingredient(tab_ingredient2, 1, 2);
    add_tab_ingredient(tab_ingredient2, 2, 2);
    add_tab_ingredient(tab_ingredient2, 3, 2);
    add_tab_ingredient(tab_ingredient2, 4, 2);

    tab_ingredients_t *tab_ingredient3 = init_tab_ingredient(1);

    add_tab_ingredient(tab_ingredient3, 0, 3);
    add_tab_ingredient(tab_ingredient3, 1, 3);
    add_tab_ingredient(tab_ingredient3, 2, 3);
    add_tab_ingredient(tab_ingredient3, 3, 3);
    add_tab_ingredient(tab_ingredient3, 4, 3);

    tab_ingredients_t *tab_ingredient4 = init_tab_ingredient(1);

    add_tab_ingredient(tab_ingredient4, 0, 4);
    add_tab_ingredient(tab_ingredient4, 1, 4);
    add_tab_ingredient(tab_ingredient4, 2, 4);
    add_tab_ingredient(tab_ingredient4, 3, 4);
    add_tab_ingredient(tab_ingredient4, 4, 4);

    tab_ingredients_t *tab_ingredient5 = init_tab_ingredient(1);

    add_tab_ingredient(tab_ingredient5, 0, 5);
    add_tab_ingredient(tab_ingredient5, 1, 5);
    add_tab_ingredient(tab_ingredient5, 2, 5);
    add_tab_ingredient(tab_ingredient5, 3, 5);
    add_tab_ingredient(tab_ingredient5, 4, 5);

    tab_ingredients_t *tab_ingredient6 = init_tab_ingredient(1);

    add_tab_ingredient(tab_ingredient6, 0, 6);
    add_tab_ingredient(tab_ingredient6, 1, 6);
    add_tab_ingredient(tab_ingredient6, 2, 6);
    add_tab_ingredient(tab_ingredient6, 3, 6);
    add_tab_ingredient(tab_ingredient6, 4, 6);

    tab_ingredients_t *tab_ingredient7 = init_tab_ingredient(1);

    add_tab_ingredient(tab_ingredient7, 0, 7);
    add_tab_ingredient(tab_ingredient7, 1, 7);
    add_tab_ingredient(tab_ingredient7, 2, 7);
    add_tab_ingredient(tab_ingredient7, 3, 7);
    add_tab_ingredient(tab_ingredient7, 4, 7);

    tab_ingredients_t *tab_ingredient8 = init_tab_ingredient(1);

    add_tab_ingredient(tab_ingredient8, 0, 8);
    add_tab_ingredient(tab_ingredient8, 1, 8);
    add_tab_ingredient(tab_ingredient8, 2, 8);
    add_tab_ingredient(tab_ingredient8, 3, 8);
    add_tab_ingredient(tab_ingredient8, 4, 8);

    tab_ingredients_t *tab_ingredient9 = init_tab_ingredient(1);

    add_tab_ingredient(tab_ingredient9, 0, 9);
    add_tab_ingredient(tab_ingredient9, 1, 9);
    add_tab_ingredient(tab_ingredient9, 2, 9);
    add_tab_ingredient(tab_ingredient9, 3, 9);
    add_tab_ingredient(tab_ingredient9, 4, 9);


    add_tab_recette(tab_recette, tab_ingredient0);
    add_tab_recette(tab_recette, tab_ingredient1);
    add_tab_recette(tab_recette, tab_ingredient2);
    add_tab_recette(tab_recette, tab_ingredient3);
    add_tab_recette(tab_recette, tab_ingredient4);
    add_tab_recette(tab_recette, tab_ingredient5);
    add_tab_recette(tab_recette, tab_ingredient6);
    add_tab_recette(tab_recette, tab_ingredient7);
    add_tab_recette(tab_recette, tab_ingredient8);
    add_tab_recette(tab_recette, tab_ingredient9);

    assert(tab_recette -> nb_recette == 10);
    assert(tab_recette -> taille_tab == 12);

    printf("contenu de la case 5 : %d\n", tab_recette -> recette_ingredients[5] -> tab_ingredient_quantite[0] -> quantite);

    remove_tab_recette(tab_recette, 5);

    assert(tab_recette -> nb_recette == 9);
    printf("contenu de la case 5 : %d\n", tab_recette -> recette_ingredients[5] -> tab_ingredient_quantite[0] -> quantite);
    printf("contenu de la case 8 : %d\n", tab_recette -> recette_ingredients[8] -> tab_ingredient_quantite[0] -> quantite);

    remove_tab_recette(tab_recette, 8);

    assert(tab_recette -> nb_recette == 8);
    printf("contenu de la case 0 : %d\n", tab_recette -> recette_ingredients[0] -> tab_ingredient_quantite[0] -> quantite);

    free_tab_recette(tab_recette);


    /*fin test tableau rectte ingredient*/

    #endif

    return 0;
}