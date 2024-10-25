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

