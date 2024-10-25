#define MAX_RECETTES 1024
#define MAX_INGREDIENTS 64
#include <stdio.h>
#include <stdlib.h>

//#include "write.c"

//fait____________________________________________________________________

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

//__________________________________________________________________________



Recette ListeRec[MAX_RECETTES];
int NOMBRE_RECETTE;

void setup_ListRec(){
    int i;
    /*Je rempli ListeRec de -1 sur l'id de ses elements car ça pourrait etre utile plus tard je pense imo*/
    for(i=0;i<MAX_RECETTES;i++){
        ListeRec[i].id = -1;
    }
    return;
}

void read_database(){
    FILE * fread;
    fread = fopen("./Data/database.txt","r");
    if(fread==NULL){
        printf("Faut remplir\n");
        return;
    }

    /*Je declare les valeur importante a fscanf*/
    int id;
    int ing;
    int quant;
    char virg;
    char pointvirgule;
    int i;

    for(i=0;i<MAX_RECETTES;i++){
    

        /*Recupere l'ID de recette et le stock dans le tableau pour que ça soit plus rapide par la suite (btw jsp pk mais il est rapid a l'execution le code ajd)*/
        fscanf(fread,"id=%d",&id);
        ListeRec[id-1].id = id;
        printf("\n%d\n",id);

        /*Je scanne " / ing=[" pour m'en debarassey*/
        fscanf(fread," / ing=[");


        /*Boucle pour recuperer les couple ingredient*/
        int j = 0;
        while(j<MAX_INGREDIENTS){

            /* Je fscanf les valeur du couple dans les parenthese et ce qui suit la parenthese*/
            fscanf(fread,"(%d:%d)%c",&ing,&quant,&virg);
            printf("(%d : %d) %c|",ing,quant,virg);
            /*J'assigne a la liste d'Ingredient de ma struc recette les valeurs*/
            ListeRec[id-1].liste[j] = (Ingredient){
                ing,
                quant
            };

            /*Fin du tableau entre crocher => break*/
            if(virg == ']'){
                ListeRec[id-1].nb_ing = j+1;
                break;
            }
            j++;
        }

        fscanf(fread,"%c\n",&pointvirgule);

        /*Je break si la derniere ligne n'est pas un ; c'est temporaire je sais pas reconnaitre une fin de fichier en C dcp je vais le faire
        automatiquement a l'ecriture etc*/
        if(feof(fread)!=0){
            break;
        }
        printf("[[[[%d--%d]]]]",NOMBRE_RECETTE,i);
    }
    fclose(fread);
    NOMBRE_RECETTE = i+1;
}

void input_recipe(Recette recette){
    /*Bon le code est vrm pas compliqué mais c'est pour mieu lire par la suite quand on aura des fonctions dans des fonctions*/
    ListeRec[recette.id-1] = recette;
    return;
}

void delete_recipe(Recette recette){
    /*Bon le code est vrm pas compliqué mais c'est pour mieu lire par la suite quand on aura des fonctions dans des fonctions*/
    ListeRec[recette.id-1].id = -1;
    return;
}

void fill_void_database(){
    int i;

    /*La variable decalager sere a connaitre le nombre de trou qui ont été bouché afin d'estimer ou se trouve la valeur a deplacer a la position de i*/
    int decalage = 0;
    for(i=0;i<NOMBRE_RECETTE;i++){
        if(ListeRec[i].id==-1){
            /*A chaque trou on augmente le decalage*/
            decalage++;
        }
        ListeRec[i] = ListeRec[i+decalage];
        /*Comme on modifie la position dans le tableau on modifie aussi id*/
        /*NE PAS OUBLIER DE MODIFIER L'ID SUR LA FUTURE TABLE D'ID-RECETTE (toujours pas ajoutée mais atres prochainement la team)*/
        ListeRec[i].id -= decalage;
    }
    /*On modifie pas le nombre de recette a la suppression pour pouvoir l'utiliser quand on fait la boucle donc on le modifie ici
    sachant que le nombre de decalage = nombre de trou = nombre de suppression*/
    NOMBRE_RECETTE-=decalage;
    return;
}

void print_ligne_database(int id_recette){
    /*J'ouvre tmp_database.txt en add*/
    FILE * fmodif;
    fmodif = fopen("./Data/tmp_database.txt","a");

    /*Je fprintf tout ce qui est "flat" dans le sens que le patern est fixe*/
    fprintf(fmodif,"id=%d / ing=[",ListeRec[id_recette-1].id);
    int i = 0;
    /*Je fprintf dans une boucle chaque ingredient avec ses quantité qui s'arrete au nombre d'ingredient defini*/
    while(i<ListeRec[id_recette-1].nb_ing-1){
        /*printf parceque je petais mon crane sur un bug taleur*/
        printf("(%d:%d)\n",ListeRec[id_recette-1].liste[i].id_ingredient,ListeRec[id_recette-1].liste[i].quantité);
        fprintf(fmodif,"(%d:%d),",ListeRec[id_recette-1].liste[i].id_ingredient,ListeRec[id_recette-1].liste[i].quantité);
        i++;
        printf("----");
    }
    fprintf(fmodif,"(%d:%d)]",ListeRec[id_recette-1].liste[i].id_ingredient,ListeRec[id_recette-1].liste[i].quantité);
    
    /*Si on est pas a la derniere recette de ListeRec on fprintf un ; et un saut de ligne*/
    if(id_recette<NOMBRE_RECETTE){
        fprintf(fmodif,";\n");
    }
    fclose(fmodif);
    return;
}

void print_database(){
    /*Je créé un nouveau fichier "tmp_database.txt" sur lequel on va reecrire la base de donnée depuis ListeRec*/
    FILE * f = fopen("./Data/tmp_database.txt","w");
    fclose(f);

    /*Je boucle toute les recette*/
    int i;
    for(i=0;i<NOMBRE_RECETTE;i++){
        /*On print chaque recette 1 a 1 pour plus de lisibilité*/
        print_ligne_database(i+1);
    }
    /*Je supprime database.txt pour renommer tmp_database.txt afin de remplacer l'ancienne database par la nouvelle*/
    remove("Data/database.txt");
    rename("Data/tmp_database.txt","Data/database.txt");
    return;
}