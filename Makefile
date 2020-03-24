##
## EPITECH PROJECT, 2020
## ARCADE
## File description:
## Makefile
##

NAME		=	arcade

SRC			=	main.cpp				\
				core/src/Core.cpp		\
				core/src/Dynlib.cpp		\

OBJ			=	$(SRC:.cpp=.o)

CXXFLAGS	+=	-W -Wall -Wextra -Werror

INC			=	-I./core/include

LIB			=	-ldl

RM			=	rm -f


all:		games graph core

%.o:		%.cpp
			$(CXX) $(CXXFLAGS) $(INC) $(LIB) -c -o $@ $^

core:		$(NAME)

$(NAME):	$(OBJ)
			$(CXX)	$(CXXFLAGS) $(INC) $(LIB) -o $(NAME) $(OBJ)

games:
			$(MAKE) -C ./games

graph:
			$(MAKE) -C ./lib

clean:
			$(RM) $(OBJ)
			$(MAKE) clean -C ./games
			$(MAKE) clean -C ./lib

fclean:		clean
			$(RM) $(NAME)
			$(MAKE) fclean -C ./games
			$(MAKE) fclean -C ./lib

re:			fclean all

.PHONY:		all games graph core clean fclean re
