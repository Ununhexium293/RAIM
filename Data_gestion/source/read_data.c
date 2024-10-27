#include <stdio.h>
#include <stdlib.h>
#include "struct.h"


/*Charge les données du fichier database.txt dans un tableau contenu dans la struct tab_recette_ingredients*/
void read_database(tab_recette_ingredients * ListeRec){
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
        int j = 0;
        while(virg != ']'){
            fscanf(f,"(%d:%d)%c",&ListeRec->recette_ingredients[i].tab_ingredient_quantite[j].id_ingredient,&ListeRec->recette_ingredients[i].tab_ingredient_quantite[j].quantite,&virg);
            j++;
        }
        fscanf(f,";\n");
        i++;
    }
    
    ListeRec->nb_recette = i;
    fclose(f);
}

/*Charge les données du fichier recette.txt dans un tableau contenu dans la struct tab_recette_ingredients*/
void read_recette(tab_nom_recette_t * ListeNom){
    FILE * f = fopen("./../Data/recette.txt","r");
    if(f==NULL){
        fclose(f);
        printf("[ERROR] file not found\n");
        return;
    }
    int i = 0;

    /*Desolé du while 1 mais je peux pas faire autrement vu que jveux pas fscanf(f,";\n") a chaque tour de boucle faut que je m'arrete
    en plein milieu*/
    while(1){
        fscanf(f,"nom '%s'",&ListeNom->tb_recette[i]);
        i++;
        if(feof(f)==0){
            break;
        }
        fscanf(f,";\n");
    }

    fclose(f);
    return;    
}

/*Charge les données du fichier inventaire.txt dans un tableau contenu dans la struct tab_inventaire*/
void read_inventaire(tab_ingredients * Inventaire){
    FILE * f = fopen("./../Data/inventaire.txt","r");
    if(f==NULL){
        fclose(f);
        printf("[ERROR] file not found\n");
        return;
    }
    int i = 0;

    /*Desolé du while 1 mais je peux pas faire autrement vu que jveux pas fscanf(f,";\n") a chaque tour de boucle faut que je m'arrete
    en plein milieu*/
    while(1){
        fscanf(f,"ing=%d qt=%d",&Inventaire->tab_ingredient_quantite[i].id_ingredient,&Inventaire->tab_ingredient_quantite[i].quantite);
        i++;
        if(feof(f) == 0){
            break;
        }
        fscanf(f,";\n");
    }
    Inventaire->nb_ingredient = i;
    fclose(f);
    return;
}

/*Charge les données du fichier ingredient.txt dans un tableau contenu dans la struct tab_ingredient_nom_unite*/
void read_ingredient(tab_ingredient_nom_unite * ListeIng){
    FILE * f = fopen("./../Data/ingredient.txt","r");
    if(f==NULL){
        fclose(f);
        printf("[ERROR] file not found\n");
        return;
    }
    int i = 0;
    /*Toujours obligé de while 1 mais je peux vrm pas faire autrement*/
    while(1){
        fscanf(f,"qt=%c nom='%s'",&ListeIng->tab_ingredient_unite[i].unite,&ListeIng->tab_ingredient_unite[i].nom);
        i++;
        if(feof(f) == 0){
            break;
        }
        fscanf(f,";\n");
    }
    ListeIng->nb_ingredient = i;
    fclose(f);
    return;
}

//