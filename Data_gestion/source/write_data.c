#include <stdio.h>
#include <stdlib.h>
#include "struct.h"
#include "gestion_types.h"

//#define DEBUG_WRITE_DATA
//#include "read_data.h"


/*On remplace les donnée du txt database.txt par celles du tableau dynamique associé*/
void write_database(tab_recette_ingredients_t *ListeRec){

    FILE *f = fopen("./Data_gestion/Data/temp_database.txt", "w");
    
    int n = ListeRec -> nb_recette;

    fprintf(f,"elem = %d;\n",n);

    for(int i = 0; i < n; i++){

        int nb_ingredient = ListeRec -> recette_ingredients[i] -> nb_ingredient;
        
        fprintf(f, "ing= nb %d : [", nb_ingredient);
        
        for(int j = 0; j < ListeRec->recette_ingredients[i] -> nb_ingredient; j++){
            fprintf(f, "(%d:",ListeRec->recette_ingredients[i]->tab_ingredient_quantite[j]->id_ingredient);
            fprintf(f, "%d),", ListeRec->recette_ingredients[i]->tab_ingredient_quantite[j]->quantite);
        }
        fprintf(f,"];\n");
    }

    fclose(f);
    
    remove("./Data_gestion/Data/database.txt");
    rename("./Data_gestion/Data/temp_database.txt","./Data_gestion/Data/database.txt");
    
    free_tab_recette(ListeRec);
}

/*On remplace les donnée du txt recette.txt par celles du tableau dynamique associé*/
void write_recette(tab_string_t *ListeNom){
    FILE * f = fopen("./Data_gestion/Data/temp_recette.txt","w");

    int n = ListeNom -> nb_string;
    fprintf(f, "elem = %d;\n", n);

    for(int i = 0; i<n; i++){
        fprintf(f,"nom %s\n", ListeNom -> tb_string[i]);
    }    

    fclose(f);
    
    remove("./Data_gestion/Data/recette.txt");
    rename("./Data_gestion/Data/temp_recette.txt","./Data_gestion/Data/recette.txt");

    free_tab_string(ListeNom);
}

/*On remplace les donnée du txt inventaire.txt par celles du tableau dynamique associé*/
void write_inventaire(tab_ingredients_t * Inventaire){
    FILE * f = fopen("./Data_gestion/Data/temp_inventaire.txt","w");

    int n = Inventaire -> nb_ingredient;
    fprintf(f, "elem = %d;\n", n);

    for(int i = 0; i < Inventaire -> nb_ingredient; i++){
        fprintf(f, "ing=%d ", Inventaire -> tab_ingredient_quantite[i] -> id_ingredient);
        fprintf(f, "qt=%d;\n", Inventaire -> tab_ingredient_quantite[i] -> quantite);
    }

    fclose(f);

    remove("./Data_gestion/Data/inventaire.txt");
    rename("./Data_gestion/Data/temp_inventaire.txt","./Data_gestion/Data/inventaire.txt");

    free_tab_ingredient(Inventaire);
}

/*On rajoute une ligne a ingredient.txt vu qu'aucune modification n'est autorisée pour pas casser tout les id 🤓*/
void ajout_ingredient(ingredient_nom_unite_t * NouvelIngredient){
    FILE * f = fopen("./Data_gestion/Data/ingredient.txt","a");
    
    fprintf(f, "qt=%c nom= %s;\n", NouvelIngredient -> unite, NouvelIngredient -> nom);
    
    fclose(f);
}


#ifdef DEBUG_WRITE_DATA

int main(void){

    /*Debug write_database*/

    write_database(read_database());

    /*Fin debug write_database*/

    /*Debug write_recette*/

    write_recette(read_recette());

    /*Fin write_recette*/

    /*Debug write_inventaire*/

    write_inventaire(read_inventaire());

    /*Fin debug write inventaire*/



    return 0;
}


#endif