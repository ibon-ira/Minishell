/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_infile_outfile.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboiraza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 00:35:37 by iboiraza          #+#    #+#             */
/*   Updated: 2025/03/09 00:36:02 by iboiraza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_heredoc(char *limit, int *in_fd)
{
	char	*aux[2];
	char	*str[2];

	str[0] = NULL;
	str[1] = NULL;
	aux[1] = "minishell: warning: here-document delimited by end-of-file";
	aux[0] = limit;
	*in_fd = get_here_doc(str, aux);
	if (*in_fd == -1)
		*in_fd = STDIN_FILENO;
}

int	first_case_aux(char **commands, int *out_fd, int i)
{
	if (*out_fd != STDOUT_FILENO)
		close(*out_fd);
	*out_fd = open(commands[i], O_CREAT | O_WRONLY | O_TRUNC, 0666);
	if (*out_fd == -1)
	{
		printf("No such file or directory\n");
		return (-1);
	}
	return (1);
}

int	second_case_aux(char **commands, int *out_fd, int i)
{
	if (*out_fd != STDOUT_FILENO)
		close(*out_fd);
	*out_fd = open(commands[i], O_CREAT | O_WRONLY | O_APPEND, 0666);
	if (*out_fd == -1)
	{
		printf("No such file or directory\n");
		return (-1);
	}
	return (1);
}

int	third_case_aux(char **commands, int *in_fd, int i)
{
	if (!ft_strcmp(commands[i - 1], "<"))
	{
		if (*in_fd != STDIN_FILENO && *in_fd != -1)
			close(*in_fd);
		*in_fd = open(commands[i], O_RDONLY);
		if (*in_fd == -1)
		{
			print_error(11, commands[i]);
			*in_fd = STDIN_FILENO;
			return (-1);
		}
	}
	else
		check_heredoc(commands[i], in_fd);
	return (1);
}

int	set_infile_outfile(t_node *node, char **commands, int out_fd, int in_fd)
{
	int	i;

	i = -1;
	while (commands[++i] != NULL)
	{
		if (!ft_strcmp(commands[i], ">") && commands[i + 1])
		{
			if (first_case_aux(commands, &out_fd, ++i) == -1)
				return (-1);
		}
		else if (!ft_strcmp(commands[i], ">>") && commands[i + 1])
		{
			if (second_case_aux(commands, &out_fd, ++i) == -1)
				return (-1);
		}
		else if ((!ft_strcmp(commands[i], "<") || !ft_strcmp(commands[i], "<<"))
			&& commands[i + 1])
		{
			if (third_case_aux(commands, &in_fd, ++i) == -1)
				return (-1);
		}
	}
	node->infile = in_fd;
	node->outfile = out_fd;
	return (1);
}
