# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sben-tay <sben-tay@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/24 21:36:43 by sben-tay          #+#    #+#              #
#    Updated: 2024/04/16 18:01:46 by sben-tay         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

MAKEFLAGS += --no-print-directory

SRCS            =   ft_dprintf.c ft_put.c ft_put2.c \
					ft_strdup.c	ft_strlcpy.c ft_strlen.c 
					 
OBJS            = $(SRCS:.c=.o)

CC                = cc
RM                = rm -f
CFLAGS            = -Wall -Wextra -Werror

NAME            = libftprintf.a


all:		$(NAME) 

$(NAME):	$(OBJS)
	@ar rcs $(NAME) $(OBJS)
%.o:%.c            
	@$(CC) $(CFLAGS) -c $< -o $@
clean:
	@$(RM) $(OBJS)

fclean:		clean
	@$(RM) $(NAME)

re:			fclean $(NAME)


.PHONY:            all clean fclean re