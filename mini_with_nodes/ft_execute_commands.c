#include "minishell.h"

void	child_execution(t_mini *data, t_node *node)
{
    int i;

    i = 0;
//	if (!is_builtin(node->full_cmd[0])
//		&& node->is_exec)
//	{
    while (node->full_cmd[i]){
        remove_quotes(node->full_cmd[i++], 0);
    }
	if (execve(node->full_path, node->full_cmd, data->envp) == -1)
	{
		printf("%s : comand not found\n", node->full_cmd[0]);
		exit (127);
	}
//	}
//	else if (is_builtin(node->full_cmd[0])
//		&& node->is_exec)
//	{
//		execute_builtin(node->full_cmd[0], min, aux);
//		exit (g_status);
//	}
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
		else if (data->nodes[aux[0]]->n_pid == 0)
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
		if (execve(node->full_path, node->full_cmd, data->envp) == -1)
		{
			printf("%s : command not found\n", node->full_cmd[0]);
			exit (127);
		}
	}
	else
		waitpid(pid, &g_status, 0);
}

void	ft_execute_commands(t_mini *data)
{
	pid_t	pid;
	int		pipefd[2];
    int     i;

	pid = 0;
    i = 0;
//	mini->signal = 1;
//	init_signals(&((*data).signal));
	if (data->nbr_nodes == 1)
	{
        while (data->nodes[0]->full_cmd[i])
		    remove_quotes(data->nodes[0]->full_cmd[i++], 0);
        if (execute_builtin(data->nodes[0]->full_cmd, data->envp))
            execute_simple_command(data, data->nodes[0], pid);
/*		if (is_builtin(data->nodes[0]->full_cmd[0])
			&& data->nodes[0]->is_set)
            execute_builtin(data->nodes[0]->full_cmd[0], data->commands, data->env, &data);
//			execute_builtin(data->nodes[0]->full_cmd[0], data, 0);
		else if (!is_builtin(data->nodes[0]->full_cmd[0])
			&& data->nodes[0]->is_set)
			execute_simple_command(data, data->nodes[0], pid);
//    printf("count->%i\n", data->ft_count_pipes);
//    printf("nbr_nodes->%i\n",data->nbr_nodes);
*/	}
	else if (data->nbr_nodes > 1)
		excecute_pipe_sequence(data, pipefd);
	if (TEMP_FILE)
		ft_clean(data);
}