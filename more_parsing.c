/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboiraza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 13:31:01 by iboiraza          #+#    #+#             */
/*   Updated: 2025/04/13 13:31:27 by iboiraza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_input(char *line)
{
	if (!detectopenquotes(line))
		return (g_status = 2, printf("syntax error: dquote\n"), 1);
	if (!check_pipe_redir(line, 0))
		return (g_status = 2, 1);
	return (0);
}

int	ft_more_checkers(char **commands)
{
	if (!check_wrong_redir(commands))
		return (printf("syntax error: redir\n"), g_status = 2, 1);
	else if (!check_wrong_pipes(commands))
		return (printf("syntax error: pipes\n"), g_status = 2, 1);
	else
		return (0);
}

char	*ft_repared_line(char *line, int j, int i, int x)
{
	int		len;
	char	*temp;

	temp = NULL;
	len = ft_strlen(line);
	temp = malloc(len + j + 1);
	if (!temp)
		return (NULL);
	while (line[++i])
	{
		temp[x++] = line[i];
		if ((line[i] == '<' || line[i] == '>') && line[i + 1]
			&& (line[i + 1] != '<' && line[i + 1] != '>' && line[i + 1] != '|'
				&& line[i + 1] != ' ' && line[i + 1] != '\0'
				&& line[i + 1] != '\t' && line[i + 1] != '\n'
				&& line[i + 1] != '\v'))
		{
			temp[x++] = ' ';
		}
	}
	temp[x] = '\0';
	free(line);
	return (temp);
}

char	*prepare_line(char *line, int i, int j)
{
	while (line[++i])
	{
		if ((line[i] == '<' || line[i] == '>') && line[i + 1]
			&& (line[i + 1] != '<' && line[i + 1] != '>' && line[i + 1] != '|'
				&& line[i + 1] != ' ' && line[i + 1] != '\0'
				&& line[i + 1] != '\t' && line[i + 1] != '\n'
				&& line[i + 1] != '\v'))
			j++;
	}
	if (j == 0)
		return (line);
	return (ft_repared_line(line, j, -1, 0));
}
