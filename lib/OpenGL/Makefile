##
## EPITECH PROJECT, 2020
## ARCADE
## File description:
## Makefile
##

NAME		=	lib_arcade_opengl.so

SRC			=	playground.cpp

OBJ			=	$(SRC:.cpp=.o)

CXXFLAGS	+=	-W -Wall -Wextra -Werror -fPIC

LIB			=	-lglfw -lGLEW -lGLU -lGL

RM			=	rm -f

all:		$(NAME)

$(NAME):	$(OBJ)
			$(CXX) $(OBJ) -shared -o $(NAME)

%.o:		%.cpp
			$(CXX) $(CXXFLAGS) $(LIB) -c -o $@ $^

clean:
			$(RM) $(OBJ)

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
