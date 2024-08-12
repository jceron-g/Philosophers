# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jceron-g <jceron-g@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/28 15:54:56 by jceron-g          #+#    #+#              #
#    Updated: 2024/08/12 09:52:18 by jceron-g         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
USER = jceron-g
CC = clang -g
CFLAGS = -Wextra -Wall -Werror
SRC_DIR = src/
OBJ_DIR = obj/

DEF_COLOR = \033[0;39m
MAGENTA   = \033[35;1m
YELLOW    = \033[33;1m
GREEN     = \033[32;1m
WHITE     = \033[37;1m
RESET     = \033[0m
GRAY 	  = \033[0;90m
BLUE      = \033[34;1m
CYAN      = \033[37;1m
RED		  = \033[31;1m

SRC_FILES = dinner get_and_set init main monitoring \
		parse protected_functions routine synchro_utils \
		tools utils

SRC = $(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJ = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES)))

OBJF = .cache_exists

all: $(NAME)

$(NAME):	$(OBJ)
			@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
			@echo "$(GREEN)Compilation successful!$(RESET)"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c | $(OBJF)
			@echo "$(BLUE)Compiling, please wait.: $(RESET) $(notdir $<)"
			@$(CC) $(CFLAGS) -c $< -o $@

$(OBJF):
			@mkdir -p $(OBJ_DIR)
			
$(OBJ_DIR)%.o: $(SRC_DIR_BONUS)%.c | $(OBJF)
			@echo "$(BLUE)Compiling: $(RESET)$(notdir $<)"
			@$(CC) $(CFLAGS) -c $< -o $@

clean:
			@rm -frf $(OBJ_DIR)
			@echo "$(RED)Cleaning program executables, please wait.$(RESET)"

fclean:
			@rm -rf $(OBJ_DIR)
			@rm -rf $(NAME)
			@echo "$(YELLOW)Cleaning program objects.$(RESET)"

re: fclean all
			@echo "$(MAGENTA)Program recompiled$(RESET)"

norm:
			@norminette $(SRC) $(SRC_BONUS)
						
.PHONY: all clean fclean re norm