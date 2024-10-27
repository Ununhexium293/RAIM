#include <stdio.h>
#include <stdlib.h>
#include "struct.h"

void write_database(tab_recette_ingredients * ListeRec){
    FILE * f = fopen("./Data_gestion/Data/temp_database.txt","w");
    int i = 0;
    char virg = ',';
    for(;i<ListeRec->nb_recette;i++){
        fprintf(f,"ing=[");
        int j = 0;
        for(;j<ListeRec->recette_ingredients[i].nb_ingredient;j++){
            fprintf(f,"(%d:%d)",ListeRec->recette_ingredients[i].tab_ingredient_quantite[j].id_ingredient,ListeRec->recette_ingredients[i].tab_ingredient_quantite[j].quantite);
        }
        fprintf(f,"]");
        if(i == ListeRec->nb_recette-1){
            break;
        }
        fprintf(f,";\n");
    }
    fclose(f);
    remove("./Data_gestion/Data/database.txt");
    rename("./Data_gestion/Data/temp_database.txt","./Data_gestion/Data/database.txt");
    return;
}

