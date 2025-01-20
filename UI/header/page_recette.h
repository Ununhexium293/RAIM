#ifndef PAGE_RECETTE_H
#define PAGE_RECETTE_H

#include "struct_passage.h"
#include <gtk/gtk.h>

GtkWidget *page_recette(GtkWidget *stack, passage_tab_t *passage_tab);

void update_visual_recette(GtkWidget *widget, gpointer data);

int update_tab_inv(passage_tab_t *passage_tab, tab_ingredients_t* Recette, int mode);


#endif