/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iksaiz-m <iksaiz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 20:48:06 by iksaiz-m          #+#    #+#             */
/*   Updated: 2025/02/23 20:17:11 by iksaiz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exit(t_mini *data, int flag)
{
	int	i;
	
	i = 0;
	if (flag == 1)
	{	
		printf("\033[31mFin.\033[0m\n");
		exit(EXIT_SUCCESS);
	}
	while (data->commands[i])
	{
		printf("%i: %s\n", i, data->commands[i]);
		i++;
	}
	if (data->splits <= 2)
	{
		if (ft_strncmp(data->commands[0], "exit", 4) == 0
			&& !data->commands[0][4])
		{
			printf("free %p\n", data->commands);
			free_split(data->commands);
			free(data);
			exit(EXIT_SUCCESS);
		}
	}
	return (0);
}

void ft_clean(t_mini *data)
{
	char *args[3];
	pid_t	pid;
	
	args[0] = "rm";
	args[1] = TEMP_FILE;
	args[2] = NULL;
	open(TEMP_FILE, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	pid = fork();
	if (pid == -1)
		return ;
	else if (pid == 0)
	{
		execve("/bin/rm", args, data->envp);
	}
	wait(NULL);
}
