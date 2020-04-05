##
## EPITECH PROJECT, 2020
## ARCADE
## File description:
## Makefile
##

all:
		$(MAKE) -C ./Ncurses
		$(MAKE) -C ./SFML
		$(MAKE) -C ./Caca

clean:
		$(MAKE) clean -C ./Ncurses
		$(MAKE) clean -C ./SFML
		$(MAKE) clean -C ./Caca

fclean:	clean
		$(MAKE) fclean -C ./Ncurses
		$(MAKE) fclean -C ./SFML
		$(MAKE) fclean -C ./Caca

re:		fclean all

.PHONY:	all clean fclean re
