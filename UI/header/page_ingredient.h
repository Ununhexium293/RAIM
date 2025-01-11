#ifndef PAGE_INGREDIENT_H
#define PAGE_INGREDIENT_H

#include "struct_passage.h"
#include <gtk/gtk.h>

GtkWidget *page_ingredient(GtkWidget *stack, passage_tab_t *passage_tab);

void update_visual_ingredient(GtkWidget *widget, gpointer data);

#endif