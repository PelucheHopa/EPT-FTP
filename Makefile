##
## EPITECH PROJECT, 2020
## nothing
## File description:
## nothing
##

SRC 	=	-C src/*.c

UTFLAGS =       -l criterion --coverage

NAME	=	myftp

CFLAGS	=	-W -Wall -Werror

INCLUDE	=	-I include/

all:	$(NAME)

$(NAME):
	gcc -c $(CLFLAGS) -fpic $(INCLUDE) src/*.c
	mv *.o src/
	gcc -o $(NAME) src/*.o
	rm src/*.o
clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)
	rm -f $(NAME_TEST)
	rm -f *.gcno
	rm -f *.gcda
	rm -f *.out

tri-all:
	mv *.h include/
	mv *.c src
tri-c:
	mv *.c src/
auteur:
	echo $(USER) > auteur

re:     fclean all
## n'affiche pas les commandes
.SILENT:

## ne compare pas les fichiers
.PHONY:

##export xLDFLAGS
##	
