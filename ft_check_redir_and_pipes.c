/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_redir_and_pipes.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboiraza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 19:28:09 by iboiraza          #+#    #+#             */
/*   Updated: 2025/03/08 19:28:28 by iboiraza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_redir(char **tok)
{
	int	i;

	i = 0;
	while (tok[i] != NULL)
	{
		if (tok[i + 1] && (!ft_strcmp(tok[i], "<") || !ft_strcmp(tok[i], "<<")
				|| !ft_strcmp(tok[i], ">") || !ft_strcmp(tok[i], ">>"))
			&& (!ft_strcmp(tok[i + 1], "<") || !ft_strcmp(tok[i + 1], "<<")
				|| !ft_strcmp(tok[i + 1], ">") || !ft_strcmp(tok[i + 1], ">>")))
			return (1);
		i++;
	}
	if (i != 0 && (!ft_strcmp(tok[i - 1], "<") || \
	!ft_strcmp(tok[i - 1], "<<") || !ft_strcmp(tok[i - 1], ">") || \
	!ft_strcmp(tok[i - 1], ">>")))
		return (1);
	return (0);
}

int	ft_check_pipes(char **tokens)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (tokens[i] != NULL)
	{
		if (!ft_strcmp(tokens[i], "|"))
		{
			count++;
			if (i == 0 || tokens[i + 1] == NULL || \
				!ft_strcmp(tokens[i - 1], "<") || \
				!ft_strcmp(tokens[i - 1], "<<") || \
				!ft_strcmp(tokens[i - 1], ">") || \
				!ft_strcmp(tokens[i - 1], ">>") || \
				!ft_strcmp(tokens[i - 1], "|"))
				return (1);
		}
		i++;
	}
	return (0);
}

int ft_check_redir_and_pipes(t_mini *data)
{
    if (ft_check_redir(data->commands))
        return (printf("Syntax error: Redirections\n"), 1);
    if (ft_check_pipes(data->commands))
        return (printf("Syntax error: Pipes\n"), 1);
    return (0);
}