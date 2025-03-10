/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_simple_or_pipes.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboiraza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 01:04:17 by iboiraza          #+#    #+#             */
/*   Updated: 2025/03/09 01:04:45 by iboiraza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	child_execution(t_mini *data, t_node *node, int aux)
{
	if (!is_builtin(node->full_cmd[0])
		&& node->all_ok)
	{
		if (execve(node->full_path, node->full_cmd, data->envp) == -1)
		{
			printf("%s: commands not found: \n", node->full_path);
			exit (127);
		}
	}
	else if (is_builtin(node->full_cmd[0])
		&& node->all_ok)
	{
		execute_builtin(node->full_cmd[0], data, aux);
		exit (g_status);
	}
}

void	child_process(t_mini *data, t_node *node, int aux[2], int fd[2])
{
	if (node->infile != STDIN_FILENO)
	{
		if (dup2(node->infile, STDIN_FILENO) == -1)
			print_error(13, NULL);
		close(node->infile);
	}
	else if (aux[1] != -1)
	{
		if (dup2(aux[1], STDIN_FILENO) == -1)
			print_error(13, NULL);
		close(aux[1]);
	}
	if (node->outfile != STDOUT_FILENO)
	{
		if (dup2(node->outfile, STDOUT_FILENO) == -1)
			print_error(14, NULL);
		close(node->outfile);
	}
	else if (aux[0] < data->nbr_nodes - 1)
		dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	close(fd[1]);
	child_execution(data, node, aux[0]);
}

void	excecute_pipe_sequence(t_mini *data, int fd[2])
{
	int	aux[2];

	aux[0] = -1;
	aux[1] = -1;
	while (data->nodes[++aux[0]])
	{
		if (pipe(fd) == -1)
			return ;
		data->nodes[aux[0]]->n_pid = fork();
		if (data->nodes[aux[0]]->n_pid == -1)
			return ;
		else if (data->nodes[aux[0]]->n_pid == 0)
			child_process(data, data->nodes[aux[0]], aux, fd);
		else
		{
			close(fd[1]);
			if (aux[1] != -1)
				close(aux[1]);
			aux[1] = fd[0];
		}
	}
	aux[0] = -1;
	while (++aux[0] < data->nbr_nodes)
		waitpid(data->nodes[aux[0]]->n_pid, &g_status, 0);
}

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
				print_error(13, NULL);
			close(node->infile);
		}
		if (node->outfile != STDOUT_FILENO)
		{
			if (dup2(node->outfile, STDOUT_FILENO) == -1)
				print_error(14, NULL);
			close(node->outfile);
		}
		if (execve(node->full_path, node->full_cmd, data->envp) == -1)
		{
			printf("%s: command not found\n", node->full_path);
			exit (127);
		}
	}
	else
		waitpid(pid, &g_status, 0);
}

void    ft_simple_or_pipes(t_mini *data)
{
    pid_t   pid;
    int     fd[2];

    pid = 0;
//  mini->signal = 1;
//  init_signals(&((*mini).signal));
    if (data->ft_count_pipes == 0 && data->nodes[0]->full_cmd)
    {
        if (is_builtin(data->nodes[0]->full_cmd[0])
			&& data->nodes[0]->all_ok)
			execute_builtin(data->nodes[0]->full_cmd[0], data, 0);
		else if (!is_builtin(data->nodes[0]->full_cmd[0])
			&& data->nodes[0]->all_ok)
			execute_one_command(data, data->nodes[0], pid);
    }
    else if (data->ft_count_pipes > 0)
		excecute_pipe_sequence(data, fd);
}