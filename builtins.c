/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iksaiz-m <iksaiz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 19:04:02 by iksaiz-m          #+#    #+#             */
/*   Updated: 2025/03/30 19:40:39 by iksaiz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_env(char *argv, t_prompt **data)
{
	t_prompt	*tmp;
	t_prompt	*var;

	var = NULL;
	tmp = *data;
	while (tmp)
	{
		if (ft_strncmp(argv, tmp->envp, ft_strlen(argv)) == 0
			&& tmp->envp[ft_strlen(argv)] == '=')
		{
			if (var == NULL)
			{
				*data = tmp->next;
			}
			else
				var->next = tmp->next;
			free(tmp->envp);
			free(tmp);
			return ;
		}
		var = tmp;
		tmp = tmp->next;
	}
}

void	unset(char **argv, t_prompt **data)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		remove_env(argv[i], data);
		i++;
	}
	g_status = 0;
}

void	pwd(int argc)
{
	char	*pwd;

	if (argc > 1)
	{
		printf("pwd: too many arguments\n");
		return ;
	}
	pwd = getcwd(NULL, 0);
	printf("%s\n", pwd);
	free(pwd);
	g_status = 0;
}

void	cd(int argc, char *av)
{
	char	*path;

	if (argc == 1)
		path = getenv("HOME");
	else
		path = av;
	if (chdir(path) == -1)
	{
		g_status = 1;
		perror("cd");
		return ;
	}
	g_status = 0;
}

void	echo(char **av, int flag)
{
	int	i;

	i = 1;
	if (flag == 2)
		i = 2;
	while (av[i] && ft_strncmp(av[i], "-n", 2) == 0 && !av[i][2])
		i++;
	while (av[i])
	{
		printf("%s", av[i]);
		i++;
		if (av[i])
			printf(" ");
	}
	if (flag == 1)
		printf("\n");
	g_status = 0;
}
