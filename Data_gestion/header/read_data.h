#ifndef READ_DATA_TYPE_H
#define READ_DATA_TYPE_H

tab_recette_ingredients_t *read_database(void);

tab_string_t *read_recette(void);

tab_ingredients_t *read_inventaire(void);

tab_ingredient_nom_unite_t *read_ingredient(void);

tab_int_t * read_menu(void);

#endif