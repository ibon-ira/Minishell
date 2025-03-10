/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboiraza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 17:12:02 by iboiraza          #+#    #+#             */
/*   Updated: 2025/02/25 17:12:31 by iboiraza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strdup(const char *s1)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (s1[i])
		i++;
	str = (char *)malloc (sizeof (char) * (i + 1));
	if (str)
	{
		while (j < i)
		{
			str[j] = s1[j];
			j++;
		}
		str[i] = '\0';
		return (str);
	}
	return (NULL);
}

char    *clean_command(char *str)
{
    if (!str)
        return (NULL);
	else	if (str[0] == '.' && str[1] == '/')
		return (ft_strdup(str));
    else if (ft_strncmp(str, "/usr/bin/", 9) == 0)
        return ft_strdup(ft_strjoin("/usr/bin/", str + 9));
    else if (ft_strncmp(str, "/bin/", 5) == 0)
        return ft_strdup(ft_strjoin("/usr/bin/", str + 5));
	else
		return ft_strdup(ft_strjoin("/usr/bin/", str));
}

void	not_builtin_command(char **data, char **env)
{

	pid_t	pid;
	char    *little;
	int		i;

	i = 0;
	while (data[i])
		printf("a ejecutar-> %s\n", data[i++]);
    little = clean_command(data[0]);
	if (data[0])
	{
		pid = fork();
		if (pid == 0)
		{
			if (execve(little, &data[0], env) == -1)
				printf ("Command not found : %s\n", data[0]);
			exit(0);
		}
		wait(NULL);
	}
}

void	do_command(t_mini *data)
{
	int		i;
	char	**str;
//	t_mini *current = *data;
	
	i = 0;
	while (data->commands[i])
		remove_quotes(data->commands[i++], 0);
	str = ft_check_redirections(data->commands, i);
	i = 0;
	i = 0;
	if (init_shell(data->splits, str, data->envp))
		not_builtin_command(str, data->envp);
	free_split(data->commands);
	free(data);
}
/*i = 0;
	while (current->commands[i])
	{
		printf("%i: %s\n", i, current->commands[i]);
		i++;
	}*/