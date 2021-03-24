SRC	=	$(shell find -name '*.c')

OBJ	=	$(SRC:.c=.o)

CC	=	gcc -g3 -I./include

FLAG	=	-W -Wall -Werror -Wextra -pedantic -lm

NAME    =       tp1

all:    $(NAME)

$(NAME):        $(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(FLAG)
	rm -f $(shell find -name '*.o')

clean:
	rm -f $(shell find -name '*~')
	rm -f $(shell find -name '*#')
	rm -f $(shell find -name '*.o')

fclean: clean
	rm -f $(NAME)

re:     fclean all

.PHONY: all clean fclean re