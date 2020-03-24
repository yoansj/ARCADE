##
## EPITECH PROJECT, 2020
## ARCADE
## File description:
## Makefile
##

NAME 		=	lib_arcade_nibbler.so

SRC			=	src/Snake.cpp

OBJ			=	$(SRC:.cpp=.o)

CXXFLAGS	+=	-lsfml-graphics -lsfml-window -lsfml-system -g3

INC			=	-I../../include -I./../include

CC			=	g++

RM			=	rm -f

all:		$(NAME)
			echo -e "Nibbler"

%.o:		%.cpp
			$(CXX) $(CXXFLAGS) $(INC) -c -o $@ $^

$(NAME):	$(OBJ)
			$(CXX) $(OBJ) $(CXXFLAGS) $(INC) $(LIB) -o $(NAME)

clean:
			$(RM) $(OBJ)

fclean:		clean
			$(RM) $(NAME)

re:			fclean all