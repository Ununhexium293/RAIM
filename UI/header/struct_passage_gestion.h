#ifndef STRUCT_PASSAGE_GESTION_H
#define STRUCT_PASSAGE_GESTION_H

#include "struct_passage.h"
#include "../../Data_gestion/header/struct.h"

passage_changement_page *init_changement_page(GtkWidget *stack, GtkWidget *page);

passage_tab_t *init_passage_tab(void);

update_page_t *init_update_page(passage_tab_t *passage_tab, GtkWidget *page);

#endif