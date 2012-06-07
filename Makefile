NAME	=	duck-engine
OBJ	=	$(SRC:.c=.o)
CC	=	gcc
CFLAGS	=	-W -Wall -Werror -Wextra -Wunused -pedantic -pedantic -O3 -pipe -g
LIB	=	-lSDLmain -lSDL -lSDL_image
SRC	=	src/main.c		\
		src/get_next_line.c	\
		src/xmalloc.c		\
		src/list.c		\

all:	comp

comp: $(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(LIB)

fclean:
	rm -rf $(OBJ)