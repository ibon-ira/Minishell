/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iksaiz-m <iksaiz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 10:00:58 by iboiraza          #+#    #+#             */
/*   Updated: 2025/04/13 19:57:53 by iksaiz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_status = 0;

void	enterdata(char *line, t_mini *data, int i)
{
	add_history(line);
	line = prepare_line(line, -1, 0);
	if (!ft_check_input(line))
	{
		data->commands = ft_split(line, ' ');
		if (!ft_more_checkers(data->commands))
		{
			while (data->commands[++i])
			{
				if (ft_check_dolars(data->commands[i]) == 1)
					data->commands[i] = vars(data->commands[i],
							data->env, 0, 0);
			}
			data->ft_count_pipes = ft_count_pipes(data->commands);
			data->splits = ft_count_splits(line, ' ');
			data->nbr_nodes = ft_count_pipes (data->commands) + 1;
			ft_exit (&data, 0);
			set_bin_path(data);
			if (!ft_prepare_nodes(data))
				ft_execute_commands(data);
			ft_free_nodes(&data, -1);
		}
	}
	free(line);
}

int	exist(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\0')
			return (1);
		i++;
	}
	return (0);
}

void	asignenvp(char **envp, t_prompt **data)
{
	t_prompt	*new;
	t_prompt	*last;
	int			i;

	new = NULL;
	last = NULL;
	i = 0;
	while (envp[i])
	{
		new = malloc(sizeof(t_prompt));
		if (!new)
			return ;
		new->envp = ft_strdup(envp[i]);
		new->next = NULL;
		if (last == NULL)
			*data = new;
		else
			last->next = new;
		last = new;
		i++;
	}
}

void	init_data(t_mini **data, char **envp)
{
	t_mini	*addata;

	addata = malloc(sizeof (struct s_mini));
	if (!addata)
		return ;
	addata->env = NULL;
	addata->execute_envp = envp;
	asignenvp(envp, &addata->env);
	*data = addata;
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_mini	*data;
	char	*prompt;

	data = NULL;
	print_logo();
	setup_signals();
	init_data(&data, envp);
	while (argc && argv)
	{
		prompt = ft_print_user();
		line = readline(prompt);
		free(prompt);
		if (!line)
			ft_exit (NULL, 1);
		if (exist(line) == 0)
			write(1, "\0", 1);
		if (exist(line))
			enterdata(line, data, -1);
		if (g_status != 2 && g_status != 1)
			g_status = (g_status >> 8) & 0xFF;
	}
	return (0);
}
