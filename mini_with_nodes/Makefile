# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: iksaiz-m <iksaiz-m@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/21 11:25:51 by iboiraza          #+#    #+#              #
#    Updated: 2025/02/16 20:26:25 by iksaiz-m         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			= cc
CFLAGS		= -Wall -Wextra -Werror -g
READLINE	= -lreadline
NAME		= minishell
RM			= rm -rf

CFILES = main.c builtins.c init_shell.c split.c utils.c exit.c parse_imput.c\
			commands.c ft_count_pipes.c ft_prepare_nodes.c

OFILES = $(CFILES:.c=.o)

all: $(NAME)

$(NAME) : $(OFILES)
	$(CC) $(CFLAGS) $(OFILES) -o $(NAME) $(READLINE)


clean:
	$(RM) $(OFILES)

fclean: clean
	$(RM) $(NAME)

re: fclean $(NAME)

.PHONY: all clean fclean re
