#include <stdio.h>
#include <stdlib.h>
#include "../header/struct.h"
#include "../header/gestion_types.h"

//#define DEBUG_WRITE_DATA
//#include "../header/read_data.h"


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
        fprintf(f,"nom %s\n",ListeNom -> tb_string[i]);
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

void ajout_ingredient(tab_ingredient_nom_unite_t * NouvelIngredient){
    FILE * f = fopen("./Data_gestion/Data/temp_ingredient.txt","w");

    int n = NouvelIngredient -> nb_ingredient;
    fprintf(f, "elem = %d;\n", n);

    for (int i = 0; i < n; i++){
        fprintf(f, "qt=%c ",  NouvelIngredient -> tab_ingredient_unite[i] -> unite);
        fprintf(f, "nom= %s\n", NouvelIngredient -> tab_ingredient_unite[i] -> nom);
    }
    
    //fprintf(f, "qt=%c nom= %s\n", NouvelIngredient -> unite, NouvelIngredient -> nom);
    
    remove("./Data_gestion/Data/ingredient.txt");
    rename("./Data_gestion/Data/temp_ingredient.txt","./Data_gestion/Data/ingredient.txt");

    fclose(f);
}


void write_menu(tab_int_t * ListeAttente){
    FILE * f = fopen("./Data_gestion/Data/menu.txt","w");

    fprintf(f,"elem = %d;",ListeAttente -> nb_int);

    for(int i = 0; i<ListeAttente -> nb_int; i++){
        fprintf(f,"\n%d;", ListeAttente -> tb_int[i]);
    }

    fclose(f);

    free_tab_int(ListeAttente);

    return;
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

    /*Fin debug write_inventaire*/

    /*Debug write_menu*/

    write_menu(read_menu());

    /*Fin debug write_menu*/



    return 0;
}


#endif