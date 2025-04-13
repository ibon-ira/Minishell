/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_infile_outfile.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboiraza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 11:35:47 by iboiraza          #+#    #+#             */
/*   Updated: 2025/03/28 11:35:49 by iboiraza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_heredoc(char *limit, int *infile)
{
	int		fd;
	char	*line;

	fd = open(TEMP_FILE, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	while (1)
	{
		line = readline(">");
		if (!line || (!ft_strncmp(line, limit, ft_strlen(limit))
				&& !line [ft_strlen(limit)]))
			break ;
		write(fd, line, strlen(line));
		write(fd, "\n", 1);
	}
	close(fd);
	*infile = open(TEMP_FILE, O_RDONLY);
}

int	create_outfile(char **commands, int *outfile, int i)
{
	if (*outfile != STDOUT_FILENO)
		close(*outfile);
	*outfile = open(commands[i], O_CREAT | O_WRONLY | O_TRUNC, 0666);
	if (*outfile == -1)
	{
		printf(" : No such file or directory\n");
		return (0);
	}
	return (1);
}

int	append_outfile(char **commands, int *outfile, int i)
{
	if (*outfile != STDOUT_FILENO)
		close(*outfile);
	*outfile = open(commands[i], O_CREAT | O_WRONLY | O_APPEND, 0666);
	if (*outfile == -1)
	{
		printf(" : No such file or directory\n");
		return (0);
	}
	return (1);
}

int	outfile_options(char **commands, int *infile, int i)
{
	if (ft_strncmp(commands[i - 1], "<<", 2))
	{
		if (*infile != STDIN_FILENO && *infile != -1)
			close(*infile);
		*infile = open(commands[i], O_RDONLY);
		if (*infile == -1)
		{
			printf("%s : No such file or directory\n", commands[i]);
			*infile = STDIN_FILENO;
			return (0);
		}
	}
	else
	{
		check_heredoc(commands[i], infile);
		*infile = open(".\vtemp\th", O_RDONLY);
		if (*infile == -1)
			return (printf("Error with heredoc\n"), 0);
	}
	return (1);
}

int	set_infile_outfile(t_node *node, char **commands, int outfile, int infile)
{
	int	i;

	i = -1;
	while (commands[++i] != NULL)
	{
		if (!ft_strncmp(commands[i], ">>", 2) && commands[i + 1])
		{
			if (append_outfile(commands, &outfile, ++i) == 0)
				return (0);
		}
		else if (!ft_strncmp(commands[i], ">", 1) && commands[i + 1])
		{
			if (create_outfile(commands, &outfile, ++i) == 0)
				return (0);
		}
		else if ((!ft_strncmp(commands[i], "<", 1)
				|| !ft_strncmp(commands[i], "<<", 2)) && commands[i + 1])
		{
			if (outfile_options(commands, &infile, ++i) == 0)
				return (0);
		}
	}
	node->infile = infile;
	node->outfile = outfile;
	return (1);
}
