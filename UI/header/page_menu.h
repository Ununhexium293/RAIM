#ifndef PAGE_MENU_H
#define PAGE_MENU_H

#include "struct_passage.h"
#include <gtk/gtk.h>

GtkWidget *page_menu(GtkWidget *stack, passage_tab_t *passage_tab);

void update_visual_menu(GtkWidget *widget, gpointer data);

#endif