#include <stdio.h>
#include <stdlib.h>
#include "struct.h"



void read_database(liste_recette_ingredients * ListRec){
    FILE * f = fopen("./../Data/database.txt","r");
    if(f==NULL){
        fclose(f);
        printf("[ERROR] file not found\n");
        return;
    }

    /*Bloc a ajouté si les database commencent par "elem {NOMBRE ELEMENT}:\n"*/
    /*
    fscanf(f,"elem %d:\n",&(ListRec->taille_tab));
    ListRec->taille_tab+=5;
    */

    int i = 0;
    char virg;
    while(feof(f) != 0){
        fscanf(f,"id=%d / ing=[",&ListRec->tb_recette_ingredients[i].id);

        int j = 0;
        while(virg != ']'){
            fscanf(f,"(%d:%d)%c",&ListRec->tb_recette_ingredients[i].liste_ingredient[j].id_ingredient,&ListRec->tb_recette_ingredients[i].liste_ingredient[j].quantite,&virg);
            j++;
        }
        fscanf(f,";\n");
        i++;
    }
    
    ListRec->taille_tab = i;
}
