#ifndef STRUCT_H
#define STRUCT_H

/*tableau dynamique de string*/
typedef struct tab_string_{
    char **tb_string;
    int nb_string;
    int taille_tab;
}tab_string_t;


/*tableau dynamique de tableau d'entier*/
typedef struct tab_int_{
    int **tb_int;
    int nb_int;
    int taille_tab;
}tab_int_t;












#endif