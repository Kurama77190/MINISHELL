# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rbalazs <rbalazs@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/16 19:10:47 by sben-tay          #+#    #+#              #
#    Updated: 2024/12/17 15:19:55 by rbalazs          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

MAKEFLAGS += --no-print-directory

# Définitions de base

NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -g3
CPPFLAGS = -I./include -I./external/LIBFT/
LDFLAGS = -L$(LIBFT) -lft -lreadline -lhistory
PARS  = src/parsing/
EXEC  = src/exec/
BUILT = src/builtins/
BUILD = builder/
EXPAND = src/expand/
LIBFT = external/LIBFT/
# GNL = 
# CFLAGS += -fsanitize=address
# CFLAGS += -fsanitize=fork

#=================================================__SRC__OF__PROJECT__=============================================================================
SRC := src/main.c src/signal/signal.c src/errors.c \
		$(addprefix $(PARS), pars_shell.c pars_env.c pars_token.c pars_env_utils.c pars_token_utils.c \
		handle_prompt.c handle_redir.c handle_cmd.c handle_redir_utils.c handle_redir_utils2.c handle_redir_utils3.c checker_prompt.c \
		checker_prompt_utils.c checker_prompt_utils2.c checker_prompt_utils3.c ft_memory.c) \
		$(addprefix $(EXPAND), handle_expand.c ft_expand_redir.c ft_expand_redir_utils.c ft_expand_args.c) \
		$(addprefix $(EXEC), exec_cases.c exec_core.c utils.c utils_2.c exec_heredoc.c exec_redirs_process.c exec_redirs_read.c exec_start.c) \
		$(addprefix $(BUILT), cd.c echo.c env.c exit.c export.c pwd.c unset.c builtins_utils.c builtins_launch.c export_utils.c)
SRC_TEST = test/main.c

$(shell mkdir -p $(BUILD))

OBJ := $(SRC:%.c=$(BUILD)%.o)

OBJ_TEST := $(SRC_TEST:%.c=$(BUILD)%.o)
#OBJ_BNS = $(SRC_BNS:%.c=$(BUILD)%.o)
#==================================================================================================================================================

HEADER = ./include/minishell.h
DEP := $(OBJ:.o=.d)

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

test: $(OBJ_TEST)
	@$(MAKE) $(MAKEFLAGS) -C $(LIBFT) bonus
	@$(CC) $(OBJ_TEST) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) -L$(LIBFT) -lft -o $(NAME)

%.o:%.c
	@$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

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

.PHONY: all clean fclean re bonus test

-include $(DEP)