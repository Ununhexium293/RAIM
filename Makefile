SRC= Data_gestion/source/gestion_types.c Data_gestion/source/read_data.c Data_gestion/source/write_data.c UI/sources/page_recette.c UI/sources/struct_passage_gestion.c UI/sources/application.c

OBJ= $(SRC:.c=.o)

application : $(OBJ)
	gcc $$(pkg-config --libs gtk4) -o $@ $^

%.o : %.c
	gcc $$(pkg-config --cflags gtk4) -Wall -Werror -c -o $@ $^

.PHONY : clean
clean : 
	rm -f $(OBJ)