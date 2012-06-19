##
## DUCK-ENGINE
## Made by theo marchal
## http://code.google.com/p/duck-engine/
##

NAME	=	duck-engine
OBJ	=	$(SRC:.c=.o)
CC	=	gcc
CFLAGS	=	-W -Wall -Wextra -Wunused -pedantic -pedantic -O3 -pipe -g
LIB	=	-lSDLmain -lSDL -lSDL_image -lSDL_ttf -lfmodex64
SRC	=	src/main.c		\
		src/get_next_line.c	\
		src/xmalloc.c		\
		src/list.c		\
		src/text.c		\
		src/limit_char.c	\
		src/show_error.c	\
		src/music.c		\
		src/clean_exit.c	\
		src/open_fd.c		\
		src/characters.c	\
		src/init_zero.c		\
		src/init_window_size.c	\
		src/init_window.c	\
		src/text_module.c	\
		src/events.c		\
		src/scene.c		\
		src/text_history.c	\

all:	comp

comp: $(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(LIB)

fclean:
	rm -rf $(OBJ)
	rm -rf $(NAME)

re: fclean all