#include <stdio.h>
#include <stdlib.h>
#include "struct.h"
#include "gestion_types.c"


/*On remplace les donnée du txt database.txt par celles du tableau dynamique associé*/
void write_database(tab_recette_ingredients_t ListeRec){
    FILE * f = fopen("./Data_gestion/Data/temp_database.txt","w");
    int i = 0;
    char virg = ',';
    for(;i<ListeRec.nb_recette;i++){
        fprintf(f,"ing=[");
        int j = 0;
        for(;j<ListeRec.recette_ingredients[i].nb_ingredient;j++){
            fprintf(f,"(%d:%d)",ListeRec.recette_ingredients[i].tab_ingredient_quantite[j].id_ingredient,ListeRec.recette_ingredients[i].tab_ingredient_quantite[j].quantite);
        }
        fprintf(f,"]");
        if(i == ListeRec.nb_recette-1){
            break;
        }
        fprintf(f,";\n");
    }
    fclose(f);
    remove("./Data_gestion/Data/database.txt");
    rename("./Data_gestion/Data/temp_database.txt","./Data_gestion/Data/database.txt");
    return;
}

/*On remplace les donnée du txt recette.txt par celles du tableau dynamique associé*/
void write_recette(tab_string_t ListeNom){
    FILE * f = fopen("./Data_gestion/Data/temp_recette.txt","w");
    int i = 0;
    for(;i<ListeNom.nb_string;i++){
        fprintf(f,"nom '%s'",ListeNom.tb_string[i]);
        if(i==ListeNom.nb_string-1){
            break;
        }
        fprintf(f,";\n");
    }    
    fclose(f);
    remove("./Data_gestion/Data/recette.txt");
    rename("./Data_gestion/Data/temp_recette.txt","./Data_gestion/Data/recette.txt");
    return;
}

/*On remplace les donnée du txt inventaire.txt par celles du tableau dynamique associé*/
void write_inventaire(tab_ingredients_t Inventaire){
    FILE * f = fopen("./Data_gestion/Data/temp_inventaire.txt","w");
    int i = 0;
    for(;i<Inventaire.nb_ingredient;i++){
        fprintf(f,"ing=%d qt=%d",Inventaire.tab_ingredient_quantite[i].id_ingredient,Inventaire.tab_ingredient_quantite[i].quantite);
        if(i==Inventaire.nb_ingredient-1){
            break;
        }
        fprintf(f,";\n");
    }    
    fclose(f);
    remove("./Data_gestion/Data/inventaire.txt");
    rename("./Data_gestion/Data/temp_inventaire.txt","./Data_gestion/Data/inventaire.txt");
    return;
}


/*On rajoute une ligne a ingredient.txt vu qu'aucune modification n'est autorisée pour pas casser tout les id 🤓*/
void ajout_ingredient(ingredient_nom_unite_t NouvelIngredient){
    FILE * f = fopen("./Data_gestion/Data/ingredient.txt","a");
    fprintf(f,";\nqt=%c nom='%s'",NouvelIngredient.unite, NouvelIngredient.nom);
    fclose(f);
    return;
}