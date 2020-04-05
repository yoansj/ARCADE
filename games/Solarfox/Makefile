##
## EPITECH PROJECT, 2020
## ARCADE
## File description:
## Makefile
##

NAME 		=	lib_arcade_solarfox.so

SRC			=	src/Solarfox.cpp

OBJ			=	$(SRC:.cpp=.o)

CXXFLAGS	+=	-W -Wall -Wextra -Werror -g3

INC			=	-I./include -I..

RM			=	rm -f

MV			=	mv


all:		$(NAME)

$(NAME):	$(OBJ)
			$(CXX) -shared -o $(NAME) $(OBJ)
			$(MV) $(NAME) ..

%.o:		%.cpp
			$(CXX) $(CXXFLAGS) $(INC) -fPIC -c -o $@ $^

clean:
			$(RM) $(OBJ)

fclean:		clean
			$(RM) ../$(NAME)

re:			fclean all

.PHONY:		all clean fclean re
