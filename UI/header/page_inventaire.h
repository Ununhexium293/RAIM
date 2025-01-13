#ifndef PAGE_INVENTAIRE_H
#define PAGE_INVENTAIRE_H

#include "struct_passage.h"
#include <gtk/gtk.h>

GtkWidget *page_inventaire(GtkWidget *stack, passage_tab_t *passage_tab);

void update_visual_inventaire(GtkWidget *widget, gpointer data);

#endif