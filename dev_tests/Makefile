##
## EPITECH PROJECT, 2020
## OOP_arcade_2019
## File description:
## Makefile
##

SRC		=	./src/Class_A.cpp		\
			./src/Class_B.cpp		\
			./src/Class_C.cpp		\

OBJ		=	$(SRC:.cpp=.o)

NAME	=	a.out

INC		=	-I./include

RM		=	rm -rf

all:		$(NAME)

$(NAME):	$(OBJ)
			$(CXX) -shared $(OBJ) -o libtest.so $(INC)
			$(CXX) ./test.cpp -ldl $(INC)

%.o:		%.cpp
			$(CXX) $(INC) -c -o $@ $^ -fPIC

clean:
			$(RM) $(OBJ)

fclean:		clean
			$(RM) $(NAME)

re:			fclean all