NAME	=	testBluetooth

FLAG	=	-Wall -Wextra -Werror \
			-I./include -g -g3 -std=c++11 -lbluetooth -pthread

SRC		=	source/*.cpp main.cpp

all:		$(NAME)

$(NAME):
			g++ $(SRC) $(FLAG) -o $(NAME)
fclean:
			rm -f $(NAME)

re:			fclean all

.cpp.o:
			g++ $(FLAG) -c $< -o $@