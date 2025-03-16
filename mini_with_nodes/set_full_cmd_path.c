#include "minishell.h"
/*
int	is_builtin(char *str)
{
	if (!ft_strncmp(str, "echo") || !ft_strncmp(str, "cd") || \
	!ft_strncmp(str, "pwd") || !ft_strncmp(str, "export") || \
	!ft_strncmp(str, "unset") || !ft_strncmp(str, "env") || \
	!ft_strcmp(str, "exit"))
		return (1);
	return (0);
}
*/
//char	*set_full_path(t_node *node, char **bin_path)
char	*set_full_path(t_node *node)
{
	char	*path;

    path = ft_strjoin("/usr/bin/", node->full_cmd[0]);
    if (access(path, X_OK) == 0)
        return (path);
/*	int		i;

	i = 0;
	if (bin_path && node->full_cmd && !is_builtin(node->full_cmd[0]))
	{
		while (bin_path[i] != NULL)
		{
			path = ft_strjoin(ft_strjoin(bin_path[i], "/", 2), node->full_cmd[0], 3);
			if (access(path, X_OK) == 0)
				return (path);
			free(path);
			i++;
		}
		return (ft_strdup(node->full_cmd[0], 0));
	}
	return (NULL);
*/  return (NULL);
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