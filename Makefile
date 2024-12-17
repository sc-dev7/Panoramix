##
## EPITECH PROJECT, 2024
## Makefile
## File description:
## ok
##

SRC	=	panoramix.c	\
		handle_error.c

NAME	=	panoramix

all:
	gcc	-o	$(NAME)	$(SRC)	-g3

clean:
	rm	-f	*#

fclean:	clean
	rm	-f	$(NAME)

re:	fclean all
