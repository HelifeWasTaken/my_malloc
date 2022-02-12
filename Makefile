##
## EPITECH PROJECT, 2022
## make
## File description:
## make
##

CC 		=	gcc

CFLAGS 	= 	-W -Wall -Wextra -Werror -fPIC -lpthread

SRC 	= 	./malloc.c \
			./block.c \
			./block2.c

OBJ 	=	$(SRC:.c=.o)

NAME 	=	libmy_malloc.so

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(CFLAGS) -shared

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all
