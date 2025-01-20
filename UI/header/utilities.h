#ifndef UTILITIES_H
#define UTILITIES_H

#include <gtk/gtk.h>

int log_10(int n);

void lib_str(gpointer data);

void strlower(char * str);

int filter_str(char * str1, const char * str2);

int compare_str(const char * str1, const char * str2);

#endif