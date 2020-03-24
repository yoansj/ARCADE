##
## EPITECH PROJECT, 2020
## ARCADE
## File description:
## Makefile
##

all:
		$(MAKE) -C ./Ncurses
		$(MAKE) -C ./SFML
		$(MAKE) -C ./OpenGL

clean:
		$(MAKE) clean -C ./Ncurses
		$(MAKE) clean -C ./SFML
		$(MAKE) clean -C ./OpenGL

fclean:	clean
		$(MAKE) fclean -C ./Ncurses
		$(MAKE) fclean -C ./SFML
		$(MAKE) fclean -C ./OpenGL

re:		fclean all

.PHONY:	all clean fclean re