# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: iksaiz-m <iksaiz-m@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/21 11:25:51 by iboiraza          #+#    #+#              #
#    Updated: 2025/04/13 17:46:36 by iksaiz-m         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			= cc
CFLAGS		= -Wall -Wextra -Werror -g
READLINE	= -lreadline
NAME		= minishell
RM			= rm -rf

CFILES = main.c split.c utils.c utils2.c builtins.c builtins_utils.c exit.c\
			parse_imput.c ft_count_pipes.c ft_prepare_nodes.c\
			ft_execute_commands.c set_full_cmd_path.c set_infile_outfile.c\
			init_shell.c set_bin_path.c env_parsed.c split_utils.c\
			env_parsed2.c utils3.c ft_execute_one_command.c signals.c\
			more_parsing.c ft_print_prompt.c

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
