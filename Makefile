SRC= Data_gestion/source/gestion_types.c Data_gestion/source/read_data.c Data_gestion/source/write_data.c UI/sources/page_recette.c UI/sources/struct_passage_gestion.c UI/sources/page_creation_recette.c UI/sources/page_ingredient.c UI/sources/application.c UI/sources/page_inventaire.c UI/sources/page_menu.c

OBJ= $(SRC:.c=.o)

application : $(OBJ)
	gcc -o $@ $^ $$(pkg-config --libs gtk4)

%.o : %.c
	gcc $$(pkg-config --cflags gtk4) -Wall -Werror -c -o $@ $^

.PHONY : clean
clean : 
	rm -f $(OBJ)