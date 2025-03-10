/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_nodes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboiraza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 22:49:49 by iboiraza          #+#    #+#             */
/*   Updated: 2025/03/08 22:50:04 by iboiraza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


char	**get_next_node(char **tmp, char ***next)
{
	int		count;
	int		i;
	char	**elements;

	count = 0;
	i = 0;
	while (tmp[count] && ft_strcmp(tmp[count], "|"))
		count++;
	elements = malloc(sizeof(char *) * (count + 1));
	if (!elements)
		return (NULL);
	while (i < count)
	{
		elements[i] = tmp[i];
		i++;
	}
	elements[i] = NULL;
	tmp += count;
	if (*tmp && !ft_strcmp(*tmp, "|"))
		tmp++;
	*next = tmp;
	return (elements);
}

t_node	*create_exec_nodes_aux(t_mini *data, char **commands)
{
	t_node	*new;

	new = malloc(sizeof(t_node));
	if (!new)
		return (NULL);
	new->infile = STDIN_FILENO;
	new->outfile = STDOUT_FILENO;
	new->full_cmd = set_full_cmd(commands, 0, 0);
	new->full_path = set_full_path(new);
	if (set_infile_outfile(new, commands, STDOUT_FILENO, STDIN_FILENO) == -1)
		new->all_ok = 0;
	else
		new->all_ok = 1;
	new->n_pid = -1;
	free(commands);
	return (new);
}
/*
t_node	**create_exec_nodes(t_mini *data, int nbr)
{
	t_node	**nodes;
	int		i;
	char	**tmp;
	char	**next;

	i = 0;
	nodes = malloc(sizeof(t_node *) * (nbr + 1));
	if (nodes == NULL)
		return (NULL);
	mini->nbr_nodes = nbr;
	tmp = mini->tokens;
	while (nbr > 0)
	{
		tmp = get_next_node(tmp, &next);
		nodes[i] = create_exec_nodes_aux(data, tmp);
		tmp = next;
		i++;
		nbr--;
	}
	nodes[i] = NULL;
	return (nodes);
}
*/
t_node  **ft_create_nodes(t_mini *data)
{
    t_node  **nodes;
    int     i;
    char    **temp;
    char    **next;

    i = 0;
    nodes = malloc(sizeof(t_node *) * (data->ft_count_pipes + 2));
    data->nbr_nodes = data->ft_count_pipes + 2;
    while (data->commands[i])
		remove_quotes(data->commands[i++], 0);
	i = 0;
	while (data->nbr_nodes > 0)
	{
		temp = get_next_node(temp, &next);
		nodes[i] = create_exec_nodes_aux(data, temp);
		temp = next;
		i++;
		data->nbr_nodes--;
    }
    nodes[i] = NULL;
	return (nodes);
}