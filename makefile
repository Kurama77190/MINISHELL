# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sben-tay <sben-tay@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/16 19:10:47 by sben-tay          #+#    #+#              #
#    Updated: 2024/10/18 22:05:04 by sben-tay         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

MAKEFLAGS += --no-print-directory

# Définitions de base

NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror 
CPPFLAGS = -g3 -I./include -I./external/LIBFT/
LDFLAGS = -L$(LIBFT) -lft -lreadline -lhistory
PARS  = src/parsing/
EXEC  = src/exec/
BUILT = src/built/
BUILD = builder/

LIBFT = external/LIBFT/
# GNL = 
# CFLAGS += -fsanitize=address
# CFLAGS += -fsanitize=fork

#=================================================__SRC__OF__PROJECT__=============================================================================
SRC = src/main.c \
		$(addprefix $(PARS), pars_shell.c pars_env.c pars_shell_utils.c pars_env_utils.c )

$(shell mkdir -p $(BUILD))

OBJ = $(SRC:%.c=$(BUILD)%.o)
#OBJ_BNS = $(SRC_BNS:%.c=$(BUILD)%.o)
#==================================================================================================================================================

HEADER = ./include/minishell.h
DEP = $(OBJ:.o=.d)

GREEN = \033[0;32m
RED = \033[0;31m
NC = \033[0m
CYAN = \033[0;36m
YELLOW = \033[0;33m
MAGENTA = \033[0;35m
BLANC = \033[0;37m

all:	$(NAME)

$(NAME): $(OBJ)


#==================================ASCII_MOD_COMPILATION==================================

	@echo "$(GREEN)"

	@echo -n "Compilation progress: ["
	@for i in $$(seq 0.1 50); do \
		sleep 0.02; \
		echo -n "#"; \
	done
	@echo "] 100 %"
	@echo "Starting external projects $(MAGENTA)LIBFT$(CYAN) and $(MAGENTA)GNL$(CYAN) compilations..."
	@$(MAKE) $(MAKEFLAGS) -C $(LIBFT) bonus
	@echo "$(CYAN)Starting $(MAGENTA)MINISHELL$(CYAN) compilations..."
	@sleep 1
	@$(CC) $(OBJ) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) -L$(LIBFT) -lft -o $(NAME)
	@echo "Done !$(BLANC)"

#=============================================================================================

%.o:%.c
	@$(CC) $(CFLAGS) $(CPPFLAGS) -g3 -c $< -o $@

$(BUILD)%.o: %.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@ -MMD -MP


 # Règle pour créer l'exécutable bonus

bonus:


clean: # Règles pour nettoyer les fichiers objets

	@echo "$(RED)Cleaning up...$(NC)"
	@printf "$(CYAN)configure$(NC) [$(GREEN)info$(NC)] : Execute make clean from Projet of minishell.\n"
	@$(MAKE) $(MAKEFLAGS) -C $(LIBFT) clean
	@printf "$(CYAN)configure$(NC) [$(GREEN)info$(NC)] : Execute make clean from Projet of libft.\n"
	@rm -rf $(BUILD)

fclean: clean # Règles pour nettoyer les fichiers objets et l'exécutable

	@rm -f $(NAME)
	@rm -f $(LIBFT)libft.a
#	@rm -f $(NAME_BNS)


re: fclean all # Règle pour recompiler

.PHONY: all clean fclean re bonus

-include $(DEP)