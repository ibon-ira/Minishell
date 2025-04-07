/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iksaiz-m <iksaiz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 20:48:06 by iksaiz-m          #+#    #+#             */
/*   Updated: 2025/03/30 19:26:06 by iksaiz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_nodes(t_mini **data, int i)
{
	while ((*data)->commands[++i] != NULL)
	{
		if ((*data)->commands[i] != NULL)
			free((*data)->commands[i]);
	}
	free((*data)->commands);
	i = -1;
	while ((*data)->nodes[++i] != NULL)
	{
		if ((*data)->nodes[i]->full_cmd != NULL)
			free((*data)->nodes[i]->full_cmd);
		if ((*data)->nodes[i]->full_path != NULL)
			free((*data)->nodes[i]->full_path);
		free((*data)->nodes[i]);
	}
	free((*data)->nodes);
	i = -1;
	if ((*data)->bin_path != NULL)
	{
		while ((*data)->bin_path[++i] != NULL)
			free ((*data)->bin_path[i]);
		free ((*data)->bin_path);
	}
}

int	ft_exit(t_mini **data, int flag)
{
	int	i;

	i = 0;
	if (flag == 1)
	{
		printf("\033[31mExit\033[0m\n");
		exit(EXIT_SUCCESS);
	}
	if ((*data)->splits <= 2)
	{
		if (ft_strncmp((*data)->commands[0], "exit", 4) == 0
			&& !(*data)->commands[0][4])
		{
			printf("\033[31mExit\033[0m\n");
			exit(EXIT_SUCCESS);
		}
	}
	return (0);
}

void	ft_clean(t_mini *data)
{
	char	*args[3];
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
		execve("/bin/rm", args, data->execute_envp);
	}
	wait(NULL);
}
