#ifndef WRITE_DATA_H
#define WRITE_DATA_H

#include "struct.h"

/*Modifie le fichier database.txt pour correspondre au tableau ListeRec et libere le tableau ListeRec*/
void write_database(tab_recette_ingredients_t *ListeRec);

/*Modifie le fichier recette.txt pour correspondre au tableau ListeNom et libere le tableau ListeNom*/
void write_recette(tab_string_t *ListeNom);

/*Modifie le fichier inventaire.txt pour correspondre au tableau Inventaire et libere le tableau Inventaire*/
void write_inventaire(tab_ingredients_t * Inventaire);

/*Ajoute un ingredient au fichier ingredient.txt*/
void ajout_ingredient(tab_ingredient_nom_unite_t * NouvelIngredient);

void write_menu(tab_int_t * ListeAttente);

#endif