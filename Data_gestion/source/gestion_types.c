#include <stdio.h>
#include <stdlib.h>
#include </home/quentin/Documents/EI3A/Projet/gestion_recette/rep_git/Data_gestion/struct.h>//à changer pour l'avoir dans le makefile et chemin relatif

/*_______________________________gestion tableau dynamique___________________________________________*/

/*________________tab dynamique recette____________________*/

/*initialise la structure*/
tab_nom_recette_t *init_tab_nom_recette(int nb_recette){
    tab_nom_recette_t *tab_nom = malloc(sizeof(tab_nom_recette_t));

    char **tab_recette = malloc(sizeof(char*) * nb_recette + 5); //on ajoute quelques emplacemnet libre en plus si jamais on souhaite faire de petits ajouts

    tab_nom -> tb_recette = tab_recette;
    tab_nom -> nb_recette = nb_recette;
    tab_nom -> taille_tab = nb_recette + 5;

    return tab_nom;
}

/*libere la memoire allouée au tableau dynamique*/
void free_tab_nom_recette(tab_nom_recette_t *tab_nom){

    /*pas sur d'en avoir besoin*/
    //for (int i = 0; i < nom_recette -> nb_recette; i++){
    //    free(tab_nom -> recette[i]);
    //}

    free(tab_nom -> tb_recette);
    free(tab_nom);
}

/*ajoute une entrée dans dans le tableau tab_recette*/
void add_tab_nom_recette(tab_nom_recette_t *tab_nom, char *nom_recette){

    if (tab_nom -> nb_recette == tab_nom -> taille_tab){     //Si il n'y a plus de place dans le tableau, on double la taille de celui-ci et on ajoute ensuite ce que l'on voulais ajouter

        char **tab_recette = malloc(sizeof(char*) * (tab_nom -> taille_tab) * 2);

        
        for (int i = 0; i < taille_tab; i++){       //copie l'ancien tableau dans le nouveau
            tab_recette[i] = tab_nom -> tb_recette[i];
        }

        tab_nom -> taille_tab *= 2;

        free(tab_nom -> tb_recette);
        tab_nom -> tb_recette = tab_recette;
    }

    tab_nom -> tb_recette[nb_recette] = nom_recette;
    tab_nom -> nb_recette += 1;


    /*debug / test*/

    printf("test ligne 30\n";)
    printf("%s\n", nom_recette);
    printf("%s\n", tab_nom -> tb_recette[nb_recette]);

    /*fin debug / test*/
}

