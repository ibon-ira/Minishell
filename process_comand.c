/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_comand.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboiraza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 10:11:29 by iboiraza          #+#    #+#             */
/*   Updated: 2025/02/12 10:11:51 by iboiraza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_multiples_command(t_mini *mini)
{
	int		last_fd;
	int		pipefd[2];
	int		status;
	t_mini	*current;

	last_fd = STDIN_FILENO;
	current = mini;
	while (current)
	{
		if (current->next)
		{
			waitpid(mini->pid, &status, 0);
			if (create_pipes(pipefd) == -1)
				return ;
		}
		h_m_c(pipefd, last_fd, current, current->next);
		close_pipe(pipefd, last_fd);
		if (current->next)
			last_fd = pipefd[0];
		current = current->next;
	}
	while (waitpid(-1, &status, 0) > 0)
		update_exit_status(status);
}

void	reset_mini_state(t_mini *mini)
{
	mini->is_builtin = 0;
	mini->next = NULL;
	if (mini->infile != STDIN_FILENO)
	{
		close(mini->infile);
		mini->infile = STDIN_FILENO;
	}
	if (mini->outfile != STDOUT_FILENO)
	{
		close(mini->outfile);
		mini->outfile = STDOUT_FILENO;
	}
	if (mini->full_path)
	{
		free(mini->full_path);
		mini->full_path = NULL;
	}
	if (mini->full_cmd)
	{
		ft_free_array(mini->full_cmd);
		mini->full_cmd = NULL;
	}
}

void	process_command2(t_mini *mini)
{
	//if (ft_strncmp(mini->full_cmd[0], "./minishell", 11) == 0)
	//	ft_increment_shlvl(mini);
	if (mini->is_builtin)
		g_exit_status = management_builtins(mini);
	else if (mini->next == NULL)
		execute_one_command(mini);
	else
		execute_multiples_command(mini);
	reset_mini_state(mini);
}
