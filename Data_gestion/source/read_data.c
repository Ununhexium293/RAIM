#include <stdio.h>
#include <stdlib.h>
#include "struct.h"
#include "gestion_types.h"

#define DEBUG_read_data


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

        printf("%d\n", nb_ingr);
        fflush(stdout);

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
//void read_recette(tab_string_t * ListeNom){
//    FILE * f = fopen("./Data_gestion/Data/recette.txt","r");
//    if(f==NULL){
//        fclose(f);
//        printf("[ERROR] file not found\n");
//        return;
//    }
//
//
//
//
//
//
//
//    int i = 0;
//
//    /*Desolé du while 1 mais je peux pas faire autrement vu que jveux pas fscanf(f,";\n") a chaque tour de boucle faut que je m'arrete
//    en plein milieu*/
//    while(1){
//        fscanf(f,"nom '%s'",&ListeNom->tb_string[i]);
//        i++;
//        if(feof(f)==0){
//            break;
//        }
//        fscanf(f,";\n");
//    }
//
//    fclose(f);
//    return;    
//}
//
///*Charge les données du fichier inventaire.txt dans un tableau contenu dans la struct tab_inventaire*/
//void read_inventaire(tab_ingredients_t * Inventaire){
//    FILE * f = fopen("./Data_gestion/Data/inventaire.txt","r");
//    if(f==NULL){
//        fclose(f);
//        printf("[ERROR] file not found\n");
//        return;
//    }
//    int i = 0;
//
//    /*Desolé du while 1 mais je peux pas faire autrement vu que jveux pas fscanf(f,";\n") a chaque tour de boucle faut que je m'arrete
//    en plein milieu*/
//    while(1){
//        fscanf(f,"ing=%d qt=%d",&Inventaire->tab_ingredient_quantite[i].id_ingredient,&Inventaire->tab_ingredient_quantite[i].quantite);
//        i++;
//        if(feof(f) == 0){
//            break;
//        }
//        fscanf(f,";\n");
//    }
//    Inventaire->nb_ingredient = i;
//    fclose(f);
//    return;
//}
//
///*Charge les données du fichier ingredient.txt dans un tableau contenu dans la struct tab_ingredient_nom_unite*/
//void read_ingredient(tab_ingredient_nom_unite_t * ListeIng){
//    FILE * f = fopen("./Data_gestion/Data/ingredient.txt","r");
//    if(f==NULL){
//        fclose(f);
//        printf("[ERROR] file not found\n");
//        return;
//    }
//    int i = 0;
//    /*Toujours obligé de while 1 mais je peux vrm pas faire autrement*/
//    while(1){
//        fscanf(f,"qt=%c nom='%s'",&ListeIng->tab_ingredient_unite[i].unite,&ListeIng->tab_ingredient_unite[i].nom);
//        i++;
//        if(feof(f) == 0){
//            break;
//        }
//        fscanf(f,";\n");
//    }
//    ListeIng->nb_ingredient = i;
//    fclose(f);
//    return;
//}
//
//

int main(void){

    #ifdef DEBUG_read_data

    /*Debug read_recette (ok)*/

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

    /*Fin debug read_recette*/

    #endif

    return 0;
}