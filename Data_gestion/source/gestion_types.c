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

/*________________tab dynamique string____________________*/


/*initialise un tableau dynamique de string*/
tab_string_t *init_tab_string(int size_tab){
    tab_string_t *tab_string = malloc(sizeof(tab_string_t));

    char **tb_string = malloc(sizeof(char*) * (size_tab + 5)); //on ajoute quelques emplacemnet libre en plus si jamais on souhaite faire de petits ajouts

    if (tb_string == NULL){
        exit(EXIT_FAILURE);
    }

    tab_string -> tb_string = tb_string;
    tab_string -> nb_string = 0;
    tab_string -> taille_tab = size_tab + 5;

    return tab_string;
}


/*libere la memoire allouée au tableau dynamique*/
void free_tab_string(tab_string_t *tab_string){

    for (int i = 0; i < tab_string -> nb_string; i++){
        free(tab_string -> tb_string[i]);
    }

    free(tab_string -> tb_string);
    free(tab_string);
}


/*ajoute une entrée dans dans le tableau tab_string*/
void add_tab_string(tab_string_t *tab_string, char *string_e){

    if (tab_string -> nb_string == tab_string -> taille_tab){     //Si il n'y a plus de place dans le tableau, on double la taille de celui-ci
        
        char **tb_string_sub = malloc(sizeof(char*) * (tab_string -> taille_tab) * 2);

        if (tb_string_sub == NULL){
            exit(EXIT_FAILURE);
        }
        
        for (int i = 0; i < tab_string -> taille_tab; i++){       //copie l'ancien tableau dans le nouveau
            tb_string_sub[i] = tab_string -> tb_string[i];
        }

        tab_string -> taille_tab *= 2;

        free(tab_string -> tb_string);      //On libere la mémoir alloué à l'ancien tableau
        tab_string -> tb_string = tb_string_sub;
    }

    char *string_bis = malloc(sizeof(char) * len_string(string_e) + 1);

    if (string_bis == NULL){
        exit(EXIT_FAILURE);
    }

    cp_string(string_e, string_bis);

    tab_string -> tb_string[tab_string -> nb_string] = string_bis;
    tab_string -> nb_string += 1;
}


/*supprime une entrée du tableau et avance les élément suivants*/
int remove_tab_string(tab_string_t *tab_string, int indice){

    if (indice >= tab_string -> nb_string){       //On verifie que l'element que l'on souhaite supprimer existe (pourras etre enlever plus tard / fais pour du debug principalement au cas où)
        printf("Impossible de supprimer la chaine de charactere, indice trop grand.\n");
        return -1;
    }

    free(tab_string -> tb_string[indice]);

    for (int i = indice; i < tab_string -> nb_string - 1; i++){
        tab_string -> tb_string[i] = tab_string -> tb_string[i + 1];
    }

    tab_string -> nb_string -= 1;

    return 0;
}