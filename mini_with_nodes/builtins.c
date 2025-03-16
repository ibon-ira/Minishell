/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iksaiz-m <iksaiz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 19:04:02 by iksaiz-m          #+#    #+#             */
/*   Updated: 2025/02/23 20:21:33 by iksaiz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
void	unset(char *argv)
{
	char *unset;
	unset = getenv(argv);
	unset = NULL;
	// getenv(argv) = NULL;
}*/

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
		perror("cd");
		return ;
	}
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
}

void	execute_builtin(char *s, t_mini *mini, int i)
{
	g_status = 0;
	if (!ft_strncmp(s, "echo") && mini->nbr_nodes != 1)
		ft_echo(mini->nodes[i], 1);
	else if (!ft_strncmp(s, "echo") && mini->nbr_nodes == 1)
		ft_echo(mini->nodes[i], mini->nodes[i]->outfile);
	else if (!ft_strncmp(s, "cd"))
		g_status = ft_cd(mini, mini->nodes[i], NULL, NULL);
	else if (!ft_strncmp(s, "pwd") && mini->nbr_nodes != 1)
		ft_pwd(1);
	else if (!ft_strncmp(s, "pwd") && mini->nbr_nodes == 1)
		ft_pwd(mini->nodes[i]->outfile);
	else if (!ft_strncmp(s, "export") && mini->nbr_nodes != 1)
		g_status = ft_export(mini, mini->nodes[i], 1);
	else if (!ft_strncmp(s, "export") && mini->nbr_nodes == 1)
		g_status = ft_export(mini, mini->nodes[i], mini->nodes[i]->outfile);
	else if (!ft_strncmp(s, "unset"))
		ft_unset(mini, mini->nodes[i], 1);
	else if (!ft_strncmp(s, "env") && mini->nbr_nodes != 1)
		g_status = ft_env(mini, mini->nodes[i], 1, 1);
	else if (!ft_strncmp(s, "env") && mini->nbr_nodes == 1)
		g_status = ft_env(mini, mini->nodes[i], 1, mini->nodes[i]->outfile);
	else if (!ft_strncmp(s, "exit"))
		g_status = ft_exit(mini, mini->nodes[i]);
}

//  Para la comprobacion del -n o cosas asi en vez de usar ft_strlen comprobar que no haya siguiente
//	while (av[i] && ft_strncmp(av[i], "-n", 2) == 0 && !av[i][3])