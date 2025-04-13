/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iksaiz-m <iksaiz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 19:11:59 by iksaiz-m          #+#    #+#             */
/*   Updated: 2025/04/13 18:54:31 by iksaiz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	printaddata(t_prompt *adddata, int flag)
{
	if (flag == 1)
	{
		while (adddata)
		{
			printf("declare -x %s\n", adddata->envp);
			adddata = adddata->next;
		}
	}
	else if (flag == 0)
	{
		while (adddata)
		{
			printf("%s\n", adddata->envp);
			adddata = adddata->next;
		}
	}
}

int	export(int argc, char **argv, int flag, t_prompt *env)
{
	int			i;
	int			x;
	char		*true_env;

	i = 0;
	if ((ft_strncmp(argv[0], "export", 6) == 0 && !argv[0][6]) && argc > 1)
	{
		while (argv[i + 1])
		{
			x = check_env_name(argv[i + 1], 0);
			if (x == 0)
			{
				true_env = ft_strjoin(argv[i + 1], "=");
				asign_env_value(true_env, &env);
				free(true_env);
			}
			else if (x == -1)
				return (g_status = 1, flag);
			else
				asign_env_value(argv[i + 1], &env);
			i++;
		}
		g_status = 0;
	}
	return (flag);
}

int	fork_actions(int argc, char **argv, int flag, t_prompt *env)
{
	t_prompt	*tmp;

	if (argc == 1 && ft_strncmp(argv[0], "env", 3) == 0 && !argv[0][3])
	{
		printaddata(env, 0);
		g_status = 0;
	}
	else if ((argc != 1 && ft_strncmp(argv[0], "env", 3) == 0 && !argv[0][3]))
	{
		printf("env: ‘%s’: not accepted\n", argv[1]);
		g_status = 127;
	}
	else if (ft_strncmp(argv[0], "export", 6) == 0 && !argv[0][6] && !argv[1])
	{
		tmp = dup_env(env);
		ft_lstsort(tmp, 1);
		printaddata(tmp, 1);
		ft_free_stack(tmp);
		g_status = 0;
	}
	else if ((ft_strncmp(argv[0], "export", 6) == 0 && !argv[0][6]) && argc > 1)
		flag = export(argc, argv, flag, env);
	else
		flag = 1;
	return (flag);
}

int	other_actions(int argc, char **argv, t_mini **data)
{
	int		flag;
	t_mini	*env;

	env = *data;
	flag = 0;
	if (argc > 1 && ft_strncmp(argv[0], "echo", 4) == 0 && !argv[0][4]
		&& ft_strncmp(argv[1], "-n", 2) == 0 && !argv[1][2])
		echo(argv, 2);
	else if (argc >= 1 && ft_strncmp(argv[0], "echo", 4) == 0 && !argv[0][4])
		echo(argv, 1);
	else if (ft_strncmp(argv[0], "pwd", 3) == 0 && !argv[0][3])
		pwd(argc);
	else if (ft_strncmp(argv[0], "unset", 5) == 0 && !argv[0][5])
		unset(argv, &env->env);
	else if (argc == 1 && ft_strncmp(argv[0], "cd", 2) == 0 && !argv[0][2])
		cd(argc, argv[0]);
	else if (argc == 2 && ft_strncmp(argv[0], "cd", 2) == 0 && !argv[0][2])
		cd(argc, argv[1]);
	else
		flag = 1;
	return (flag);
}

int	execute_builtin(char **argv, t_prompt *env, t_mini **data)
{
	int	flag;
	int	argc;

	argc = 0;
	while (argv[argc] != NULL)
		argc++;
	flag = 0;
	flag += fork_actions(argc, argv, flag, env);
	flag += other_actions(argc, argv, data);
	if (flag == 2)
		return (printf("%s : command not found\n", argv[0]), g_status = 127, 1);
	return (0);
}
