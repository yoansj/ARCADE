##
## EPITECH PROJECT, 2020
## ARCADE
## File description:
## Makefile for libcaca
##

NAME		=	lib_arcade_libcaca.so

SRC			=	src/Caca.cpp

OBJ			=	$(SRC:.cpp=.o)

INC			=	-I./include -I..

LIB			=	`pkg-config --cflags caca` -lcaca

CXXFLAGS	+=	-W -Wall -Wextra -g3

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
