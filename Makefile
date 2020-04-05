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

CXXFLAGS	+=	-W -Wall -Wextra -Werror -std=c++17 -g3

INC			=	-I./core/include -I./lib -I./games

LIB			=	-ldl -lstdc++fs

RM			=	rm -f


all:		games graphicals core

%.o:		%.cpp
			$(CXX) $(CXXFLAGS) $(INC) $(LIB) -c -o $@ $^

core:		$(NAME)

$(NAME):	$(OBJ)
			$(CXX) $(CXXFLAGS) $(INC) -o $(NAME) $(OBJ) $(LIB)

games:
			$(MAKE) -C ./games

graphicals:
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
