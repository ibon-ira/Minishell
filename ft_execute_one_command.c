/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute_one_command.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboiraza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 13:13:18 by iboiraza          #+#    #+#             */
/*   Updated: 2025/04/13 13:13:50 by iboiraza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_simple_command(t_mini *data, t_node *node, pid_t pid)
{
	pid = fork();
	if (pid == -1)
		return ;
	else if (pid == 0)
	{
		if (node->infile != STDIN_FILENO)
		{
			if (dup2(node->infile, STDIN_FILENO) == -1)
				printf("Error with input file\n");
			close(node->infile);
		}
		if (node->outfile != STDOUT_FILENO)
		{
			if (dup2(node->outfile, STDOUT_FILENO) == -1)
				printf("Error with output file\n");
			close(node->outfile);
		}
		if (execve(node->full_path, node->full_cmd, data->execute_envp) == -1)
		{
			printf("%s : command not found\n", node->full_cmd[0]);
			exit (127);
		}
	}
	else
		waitpid(pid, &g_status, 0);
}

void	prepare_builtin(t_mini *data, t_node *node)
{
	int	original_in;
	int	original_out;

	original_in = dup(STDIN_FILENO);
	original_out = dup(STDOUT_FILENO);
	if (node->infile != STDIN_FILENO)
	{
		if (dup2(node->infile, STDIN_FILENO) == -1)
			printf("Error with input file\n");
		close(node->infile);
	}
	if (node->outfile != STDOUT_FILENO)
	{
		if (dup2(node->outfile, STDOUT_FILENO) == -1)
			printf("Error with output file\n");
		close(node->outfile);
	}
	execute_builtin(data->nodes[0]->full_cmd, data->env, &data);
	dup2(original_in, STDIN_FILENO);
	dup2(original_out, STDOUT_FILENO);
	close(original_in);
	close(original_out);
}
