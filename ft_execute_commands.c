/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute_commands.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iksaiz-m <iksaiz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 11:35:08 by iboiraza          #+#    #+#             */
/*   Updated: 2025/03/30 19:17:35 by iksaiz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	child_execution(t_mini *data, t_node *node)
{
	t_mini	*temp_data;
	int		i;

	i = 0;
	temp_data = data;
	if (node->full_cmd == NULL)
		exit (0);
	while (node->full_cmd[i])
	{
		remove_quotes(node->full_cmd[i++], 0);
	}
	if (is_builtin(node->full_cmd[0]))
	{
		execute_builtin(node->full_cmd, data->env, &temp_data);
		exit (0);
	}
	else if (execve(node->full_path, node->full_cmd, data->execute_envp) == -1)
	{
		write(1, node->full_cmd[0], ft_strlen(node->full_cmd[0]));
		write(1, " : comand not found\n", 20);
		exit (127);
	}
}

void	child_process(t_mini *data, t_node *node, int aux[2], int pipefd[2])
{
	if (node->infile != STDIN_FILENO)
	{
		if (dup2(node->infile, STDIN_FILENO) == -1)
			printf("Error with input file or pipe output\n");
		close(node->infile);
	}
	else if (aux[1] != -1)
	{
		if (dup2(aux[1], STDIN_FILENO) == -1)
			printf("Error with input file or pipe output\n");
		close(aux[1]);
	}
	if (node->outfile != STDOUT_FILENO)
	{
		if (dup2(node->outfile, STDOUT_FILENO) == -1)
			printf("Error withoutput file\n");
		close(node->outfile);
	}
	else if (aux[0] < data->nbr_nodes - 1)
		dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[0]);
	close(pipefd[1]);
	child_execution(data, node);
}

void	excecute_pipe_sequence(t_mini *data, int pipefd[2])
{
	int	aux[2];

	aux[0] = -1;
	aux[1] = -1;
	while (data->nodes[++aux[0]])
	{
		if (pipe(pipefd) == -1)
			return ;
		data->nodes[aux[0]]->n_pid = fork();
		if (data->nodes[aux[0]]->n_pid == -1)
			return ;
		else if (data->nodes[aux[0]]->n_pid == 0
			&& data->nodes[aux[0]]->is_set == 1)
			child_process(data, data->nodes[aux[0]], aux, pipefd);
		else
		{
			close(pipefd[1]);
			if (aux[1] != -1)
				close(aux[1]);
			aux[1] = pipefd[0];
		}
	}
	aux[0] = -1;
	while (++aux[0] < data->nbr_nodes)
		waitpid(data->nodes[aux[0]]->n_pid, &g_status, 0);
}

void	ft_execute_commands(t_mini *data)
{
	pid_t	pid;
	int		pipefd[2];
	int		i;

	pid = 0;
	i = 0;
	if (data->nbr_nodes == 1 && data->nodes[0]->full_cmd != NULL)
	{
		while (data->nodes[0]->full_cmd[i])
			remove_quotes(data->nodes[0]->full_cmd[i++], 0);
		if (is_builtin(data->nodes[0]->full_cmd[0])
			&& data->nodes[0]->is_set)
			prepare_builtin(data, data->nodes[0]);
		else
		{
			if (data->nodes[0]->is_set == 1)
				execute_simple_command(data, data->nodes[0], pid);
		}
	}
	else if (data->nbr_nodes > 1)
		excecute_pipe_sequence(data, pipefd);
	if (TEMP_FILE)
		ft_clean(data);
	if (g_status == 32512)
		g_status = 127;
}
