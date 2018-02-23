# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: qhonore <qhonore@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/30 11:30:21 by qhonore           #+#    #+#              #
#    Updated: 2018/02/23 17:31:11 by qhonore          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_PATH = ./src/
OBJ_PATH = ./obj/
INC_PATH = ./inc/ ~/.brew/include
LIB_PATH = ~/.brew/lib

SRC_NAME1 = learn.cpp Learn.class.cpp
OBJ_NAME1 = $(SRC_NAME1:.cpp=.o)
SRC1 = $(addprefix $(SRC_PATH),$(SRC_NAME1))
OBJ1 = $(addprefix $(OBJ_PATH),$(OBJ_NAME1))
NAME1 = learn

SRC_NAME2 = estimate.cpp
OBJ_NAME2 = $(SRC_NAME2:.cpp=.o)
SRC2 = $(addprefix $(SRC_PATH),$(SRC_NAME2))
OBJ2 = $(addprefix $(OBJ_PATH),$(OBJ_NAME2))
NAME2 = estimate

INC = $(addprefix -I ,$(INC_PATH))
LIB = $(addprefix -L ,$(LIB_PATH))
LIB_NAME = -lm
FRAMEWORK = -lsfml-system -lsfml-window -lsfml-graphics -lsfml-network -lsfml-audio -Wl,-rpath,$$HOME/.brew/lib

THETA = theta_data

CC = g++
CFLAGS = -MMD -pedantic -Wuninitialized -std=c++11

all:
	@echo "\033[32;44m Make $(NAME1) \033[0m"
	@make $(NAME1)
	@echo "\033[32;44m Make $(NAME2) \033[0m"
	@make $(NAME2)

install:
	# rm -rf ~/.brew
	brew update
	brew upgrade
	brew install sfml

$(NAME1): $(OBJ1)
	$(CC) $(CFLAGS) $^ -o $@ $(INC) $(LIB) $(LIB_NAME) $(FRAMEWORK)

$(NAME2): $(OBJ2)
	$(CC) $(CFLAGS) $^ -o $@

$(OBJ_PATH)%.o: $(SRC_PATH)%.cpp
	@mkdir -p $(OBJ_PATH)
	$(CC) $(CFLAGS) $(INC) -o $@ -c $<

clean:
	@echo "\033[31;44m Make clean $(NAME1) & $(NAME2) \033[0m"
	rm -rf $(OBJ1) $(OBJ2) $(OBJ_PATH)

fclean: clean
	@echo "\033[31;44m Make fclean $(NAME1) & $(NAME2) \033[0m"
	rm -f $(NAME1) $(NAME2) $(THETA)

re: fclean all

-include $(OBJ1:.o=.d)
-include $(OBJ2:.o=.d)

.PHONY: lib clean fclean re
