/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_full_cmd_path.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iksaiz-m <iksaiz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 11:35:40 by iboiraza          #+#    #+#             */
/*   Updated: 2025/04/13 19:54:03 by iksaiz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char *str)
{
	if (!ft_strncmp(str, "echo", 4) || !ft_strncmp(str, "cd", 2) || \
	!ft_strncmp(str, "pwd", 3) || !ft_strncmp(str, "export", 6) || \
	!ft_strncmp(str, "unset", 5) || !ft_strncmp(str, "env", 3) || \
	!ft_strncmp(str, "exit", 4))
		return (1);
	return (0);
}

char	*set_full_path(t_node *node, char **bin_path)
{
	char	*path;
	int		i;
	char	*temp;

	i = 0;
	if (access(node->full_cmd[0], X_OK) == 0 && !is_builtin(node->full_cmd[0]))
		return (ft_strdup(node->full_cmd[0]));
	if (bin_path && node->full_cmd && !is_builtin(node->full_cmd[0]))
	{
		while (bin_path[i] != NULL)
		{
			temp = ft_strjoin(bin_path[i], "/");
			path = ft_strjoin(temp, node->full_cmd[0]);
			free (temp);
			if (access(path, X_OK) == 0)
				return (path);
			free(path);
			i++;
		}
		return (ft_strdup(node->full_cmd[0]));
	}
	return (NULL);
}

int	is_redirection(char *str)
{
	if (!ft_strncmp(str, "<<", 2) || !ft_strncmp(str, "<", 1) || \
	!ft_strncmp(str, ">>", 2) || !ft_strncmp(str, ">", 1))
		return (1);
	return (0);
}

int	count_cmd(char **commands)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (commands[i] != NULL)
	{
		if (is_redirection(commands[i]))
			i++;
		else
			count++;
		i++;
	}
	return (count);
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
	if (!full_cmd)
		return (NULL);
	cmd = 0;
	while (commands[i] != NULL)
	{
		if (is_redirection(commands[i]))
			i++;
		else
			full_cmd[cmd++] = commands[i];
		i++;
	}
	full_cmd[cmd] = NULL;
	return (full_cmd);
}
