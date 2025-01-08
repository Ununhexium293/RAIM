#include <stdio.h>
#include <stdlib.h>
#include "../header/struct.h"
#include "../header/gestion_types.h"

#define MAX_LEN_STRING 32

//#define DEBUG_read_data


//_____________________________________LES PATHS SONT ECRIT DEPUIS RIM_____________________________________


/*Charge les données du fichier database.txt dans un tableau contenu dans la struct tab_recette_ingredients*/
tab_recette_ingredients_t *read_database(void){
    FILE * file = fopen("./Data_gestion/Data/database.txt","r");       //ouvre le fichier database.txt
    if(file==NULL){
        fclose(file);
        printf("[ERROR] file not found\n");
        fflush(stdout);
        exit(EXIT_FAILURE);
    }

    int size_array;
    fscanf(file,"elem = %d;\n",&size_array);
    
    tab_recette_ingredients_t *listerec = init_tab_recette(size_array);

    for (int i = 0; i < size_array; i++){       //On replis les cases du tableau listerec

        int nb_ingr;
        fscanf(file, "ing = nb %d : [", &nb_ingr);

        tab_ingredients_t *tab_ingredient = init_tab_ingredient(nb_ingr);

        for (int j = 0; j < nb_ingr; j++){      //rempli les cases du tableau tab_ingredient
            int id_ingr, quantity;
            fscanf(file, "(%d:%d),", &id_ingr, &quantity);

            add_tab_ingredient(tab_ingredient, id_ingr, quantity);
        }

        fscanf(file, "];\n");

        add_tab_recette(listerec, tab_ingredient);
    }
    fclose(file);

    return listerec;
}


/*Charge les données du fichier recette.txt dans un tableau contenu dans la struct tab_recette_ingredients*/
tab_string_t *read_recette(void){
    FILE * f = fopen("./Data_gestion/Data/recette.txt","r");
    if(f==NULL){
        fclose(f);
        printf("[ERROR] file not found\n");
        fflush(stdout);
        exit(EXIT_FAILURE);
    }

    int size_array;
    fscanf(f,"elem = %d;\n",&size_array);

    tab_string_t *tab_nom = init_tab_string(size_array);

    for (int i = 0; i < size_array; i++){
        char temp[MAX_LEN_STRING];

        fscanf(f, "nom %s\n", temp);

        add_tab_string(tab_nom, temp);
    }

    fclose(f);
    return tab_nom;    
}

/*Charge les données du fichier inventaire.txt dans un tableau contenu dans la struct tab_inventaire*/
tab_ingredients_t *read_inventaire(void){
    FILE * f = fopen("./Data_gestion/Data/inventaire.txt","r");
    if(f==NULL){
        fclose(f);
        printf("[ERROR] file not found\n");
        exit(EXIT_FAILURE);
    }

    int size_array;
    fscanf(f,"elem = %d;\n",&size_array);

    tab_ingredients_t *tab_ingredient = init_tab_ingredient(size_array);

    for (int i = 0; i < size_array; i++){
        int id_ingr, quantity;
        fscanf(f, "ing=%d qt=%d;\n", &id_ingr, &quantity);

        add_tab_ingredient(tab_ingredient, id_ingr, quantity);
    }

    fclose(f);
    return tab_ingredient;
    
}

/*Charge les données du fichier ingredient.txt dans un tableau contenu dans la struct tab_ingredient_nom_unite*/
tab_ingredient_nom_unite_t *read_ingredient(void){
    FILE * f = fopen("./Data_gestion/Data/ingredient.txt","r");
    if(f==NULL){
        fclose(f);
        printf("[ERROR] file not found\n");
        exit(EXIT_FAILURE);
    }

    int size_array;
    fscanf(f,"elem = %d;\n",&size_array);

    tab_ingredient_nom_unite_t *tab_ingr = init_tab_ingredient_nom_unite(size_array);

    for (int i = 0; i < size_array; i++){
        char quantity;
        char name[MAX_LEN_STRING];

        fscanf(f, "qt=%c nom= %s\n", &quantity, name);

        add_tab_ingredient_nom_unite(tab_ingr, name, quantity);
    }

    fclose(f);
    return tab_ingr;
}

tab_int_t * read_menu(void){

    FILE * f = fopen("./Data_gestion/Data/menu.txt","r");

    if(f==NULL){
        fclose(f);
        printf("[ERROR] file not found\n");
        exit(EXIT_FAILURE);
    }

    int nb,add;
    fscanf(f,"elem = %d;",&nb);


    tab_int_t * ListeAttente;
    ListeAttente = init_tab_int(nb);

    for(int i = 0;i<nb;i++){

        fscanf(f,"\n%d;",&add);
        add_tab_int(ListeAttente,add);


    }



    fclose(f);

    return ListeAttente;
}


#ifdef DEBUG_read_data

int main(void){

    /*Debug read_database (ok)*/

    printf("Debug read_recette\n");

    tab_recette_ingredients_t *tab_recette = read_database();
    
    for (int i = 0; i < tab_recette -> nb_recette; i++){
        tab_ingredients_t *tab_ingr = tab_recette -> recette_ingredients[i];

        printf("|");

        for (int j = 0; j < tab_ingr -> nb_ingredient; j++){
            printf(" %d, %d |", tab_ingr -> tab_ingredient_quantite[j] -> id_ingredient, tab_ingr -> tab_ingredient_quantite[j] -> quantite);
        }

        printf("\n");
    }

    free_tab_recette(tab_recette);

    /*Fin debug read_database*/

    /*Debug read_nom*/

    printf("\n\nDebug read_nom\n");

    tab_string_t *tab_nom = read_recette();

    for (int i = 0; i < tab_nom -> nb_string; i++){
        printf("nom : %s\n", tab_nom -> tb_string[i]);
    }

    free_tab_string(tab_nom);

    /*Fin debug read_nom*/

    /*Debug read inventaire*/

    printf("\n\nDebug read_inventaire\n\n");

    tab_ingredients_t *tab_ingredient = read_inventaire();

    for (int i = 0; i < tab_ingredient -> nb_ingredient; i++){
        printf("id = %d, qt = %d\n", tab_ingredient -> tab_ingredient_quantite[i] -> id_ingredient, tab_ingredient -> tab_ingredient_quantite[i] -> quantite);
    }

    free_tab_ingredient(tab_ingredient);
    /*Fin debug read_inventaire*/

    /*Debug read_ingredients*/

    printf("\n\nDebug read_ingredients\n");

    tab_ingredient_nom_unite_t *tab_ingr_nom_unite = read_ingredient();

    for (int i = 0; i < tab_ingr_nom_unite -> nb_ingredient; i++){
        printf("qt = %c, nom : %s\n", tab_ingr_nom_unite -> tab_ingredient_unite[i] -> unite, tab_ingr_nom_unite -> tab_ingredient_unite[i] -> nom);
    }

    free_tab_ingredient_nom_unite(tab_ingr_nom_unite);

    /*Fin debug read ingredients*/

    /*Debug read_menu*/

    printf("\n\nDebug read_menu\n");


    tab_int_t *tab_id = read_menu();

    for (int i = 0; i < tab_id -> nb_int; i++){
        printf("id recette : %d\n", tab_id -> tb_int[i]);
    }

    free_tab_int(tab_id);

    /*Fin debug read_menu*/


    return 0;
}

#endif