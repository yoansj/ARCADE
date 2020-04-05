##
## EPITECH PROJECT, 2020
## ARCADE
## File description:
## Makefile
##

NAME		=	lib_arcade_sfml.so

SRC			=	src/Sfml.cpp

OBJ			=	$(SRC:.cpp=.o)

INC			=	-I./include -I..

LIB			=	-l sfml-window -l sfml-graphics -l sfml-system

CXXFLAGS	+=	-W -Wall -Wextra

RM			=	rm -f

MV			=	mv


all:		$(NAME)

$(NAME):	$(OBJ)
			$(CXX) -shared -o $(NAME) $(OBJ) $(LIB)
			$(MV) $(NAME) ..

%.o:		%.cpp
			$(CXX) $(CXXFLAGS) $(INC) -fPIC $(LIB) -c -o $@ $^

clean:
			$(RM) $(OBJ)

fclean:		clean
			$(RM) ../$(NAME)

re:			fclean all

.PHONY:		all clean fclean re
