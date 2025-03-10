/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_full_cmd_and_path.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboiraza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 23:35:45 by iboiraza          #+#    #+#             */
/*   Updated: 2025/03/08 23:36:01 by iboiraza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char *s)
{
	if (!ft_strcmp(s, "echo") || !ft_strcmp(s, "cd") || \
	!ft_strcmp(s, "pwd") || !ft_strcmp(s, "export") || \
	!ft_strcmp(s, "unset") || !ft_strcmp(s, "env") || \
	!ft_strcmp(s, "exit"))
		return (1);
	return (0);
}

char	*set_full_path(t_node *node, char **bin_path)
{
	char	*path;
	int		i;

	i = 0;
	if (!is_builtin(node->full_cmd[0]))
	{
		while (bin_path[i] != NULL)
		{
			path = ft_strjoin(ft_strjoin(bin_path[i], "/"), node->full_cmd[0]);
			if (access(path, X_OK) == 0)
				return (path);
			free(path);
			i++;
		}
		return (ft_strdup(node->full_cmd[0]));
	}
	return (NULL);
}

int	is_redirection(char *s)
{
	if (!ft_strcmp(s, "<<") || !ft_strcmp(s, "<") || \
	!ft_strcmp(s, ">>") || !ft_strcmp(s, ">"))
		return (1);
	return (0);
}

int	count_cmd(char **commands)
{
	int	i;
	int	cmd;

	cmd = 0;
	i = 0;
	while (commands[i] != NULL)
	{
		if (is_redirection(commands[i]))
			i++;
		else
			cmd++;
		i++;
	}
	return (cmd);
}

char	**set_full_cmd(char **commands, int i, int cmd)
{
	char	**full_cmd;

	cmd = count_cmd(commands);
	i = 0;
	if (cmd > 0)
		full_cmd = malloc(sizeof(char *) * (cmd + 1));
	else
		return (NULL);
	cmd = 0;
	while (commands[i] != NULL)
	{
		if (is_redirection(commands[i]))
			i++;
		else
			full_cmd[cmd++] = commands[i++];

	}
	full_cmd[cmd] = NULL;
	return (full_cmd);
}
