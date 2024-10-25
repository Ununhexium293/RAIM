#include <stdio.h>
#include <stdlib.h>
#include </home/quentin/Documents/EI3A/Projet/gestion_recette/rep_git/Data_gestion/source/struct.h>//à changer pour l'avoir dans le makefile et chemin relatif

/*_______________________________gestion tableau dynamique___________________________________________*/


/*Donne la taille d'un char* */
int len_string(char *string){
    int taille = 0;
    for (; string[taille] != '\0'; taille++);
    return taille;
}


/*Permet de copier un string sans copier les adresses*/
void cp_string(char *donnor, char *reciever){
    for (int i = 0; i <= len_string(donnor); i++){
        reciever[i] = donnor[i];
    }
}


/*________________tab dynamique recette____________________*/


/*initialise la structure*/
tab_nom_recette_t *init_tab_nom_recette(int nb_recette){
    tab_nom_recette_t *tab_nom = malloc(sizeof(tab_nom_recette_t));

    char **tab_recette = malloc(sizeof(char*) * (nb_recette + 5)); //on ajoute quelques emplacemnet libre en plus si jamais on souhaite faire de petits ajouts

    if (tab_recette == NULL){
        exit(EXIT_FAILURE);
    }

    tab_nom -> tb_recette = tab_recette;
    tab_nom -> nb_recette = nb_recette;
    tab_nom -> taille_tab = nb_recette + 5;

    return tab_nom;
}


/*libere la memoire allouée au tableau dynamique*/
void free_tab_nom_recette(tab_nom_recette_t *tab_nom){

    /*pas sur d'en avoir besoin*/
    for (int i = 0; i < tab_nom -> nb_recette; i++){
        free(tab_nom -> tb_recette[i]);
    }

    free(tab_nom -> tb_recette);
    free(tab_nom);
}


/*ajoute une entrée dans dans le tableau tab_recette*/
void add_tab_nom_recette(tab_nom_recette_t *tab_nom, char *nom_recette){

    if (tab_nom -> nb_recette == tab_nom -> taille_tab){     //Si il n'y a plus de place dans le tableau, on double la taille de celui-ci et on ajoute ensuite ce que l'on voulais ajouter
        
        char **tab_recette = malloc(sizeof(char*) * (tab_nom -> taille_tab) * 2);

        if (tab_recette == NULL){
            exit(EXIT_FAILURE);
        }

        
        for (int i = 0; i < tab_nom -> taille_tab; i++){       //copie l'ancien tableau dans le nouveau
            tab_recette[i] = tab_nom -> tb_recette[i];
        }

        tab_nom -> taille_tab *= 2;

        free(tab_nom -> tb_recette);
        tab_nom -> tb_recette = tab_recette;
    }

    char *nom_recette_bis = malloc(sizeof(char) * len_string(nom_recette) + 1);

    if (nom_recette_bis == NULL){
        exit(EXIT_FAILURE);
    }

    cp_string(nom_recette, nom_recette_bis);

    tab_nom -> tb_recette[tab_nom -> nb_recette] = nom_recette_bis;
    tab_nom -> nb_recette += 1;
}