# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: qhonore <qhonore@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/30 11:30:21 by qhonore           #+#    #+#              #
#    Updated: 2018/02/21 20:37:37 by qhonore          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_PATH = ./src/
OBJ_PATH = ./obj/
INC_PATH = ./inc/

SRC_NAME = main.cpp
OBJ_NAME = $(SRC_NAME:.cpp=.o)
NAME = learning

SRC = $(addprefix $(SRC_PATH),$(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH),$(OBJ_NAME))
INC = $(addprefix -I,$(INC_PATH))

CC = g++
CFLAGS = -MMD -pedantic -Wuninitialized -std=c++11

all:
	@echo "\033[32;44m Make $(NAME) \033[0m"
	@make $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@

$(OBJ_PATH)%.o: $(SRC_PATH)%.cpp
	@mkdir -p $(OBJ_PATH)
	$(CC) $(CFLAGS) $(INC) -o $@ -c $<

clean:
	@echo "\033[31;44m Make clean $(NAME) \033[0m"
	rm -rf $(OBJ) $(OBJ_PATH)

fclean: clean
	@echo "\033[31;44m Make fclean $(NAME) \033[0m"
	rm -f $(NAME)

re: fclean all

-include $(OBJ:.o=.d)

.PHONY: lib clean fclean re
