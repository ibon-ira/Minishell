#include "minishell.h"

char	**get_next_node(char **tmp, char ***next)
{
	int		count;
	int		i;
	char	**elements;

	count = 0;
	i = 0;
	while (tmp[count] && ft_strncmp(tmp[count], "|", 1))
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
	if (*tmp && !ft_strncmp(*tmp, "|", 1))
		tmp++;
	*next = tmp;
	return (elements);
}

t_node	*ft_create_nodes_aux(char **commands)
{
	t_node	*new;

	new = malloc(sizeof(t_node));
	if (!new)
		return (NULL);
	new->infile = STDIN_FILENO;
	new->outfile = STDOUT_FILENO;
	new->full_cmd = set_full_cmd(commands, 0, 0);
    new->full_path = set_full_path(new);
    //	new->full_path = set_full_path(new, mini->bin_path);
	if (!set_infile_outfile(new, commands, STDOUT_FILENO, STDIN_FILENO))
		new->is_set = 0;
	else
		new->is_set = 1;
	new->n_pid = -1;
	free(commands);
	return (new);
}

t_node	**ft_create_nodes(t_mini *data)
{
	t_node	**nodes;
	int		i;
	char	**tmp;
	char	**next;

	i = 0;
	nodes = malloc(sizeof(t_node *) * (data->ft_count_pipes + 2));
	if (nodes == NULL)
		return (NULL);
	tmp = data->commands;
	while (data->ft_count_pipes >= 0)
	{
		tmp = get_next_node(tmp, &next);
		nodes[i] = ft_create_nodes_aux(tmp);
		tmp = next;
		i++;
		data->ft_count_pipes--;
	}
	nodes[i] = NULL;
	return (nodes);
}

int	ft_prepare_nodes(t_mini *data)
{
	if (!check_wrong_redir(data->commands))
        return(printf("syntax error: redirection\n"), 1);
    else if (!check_wrong_pipes(data->commands))
        return(printf("syntax error: pipes\n"), 1);
    else
        data->nodes = ft_create_nodes(data);
//    execve(data->nodes[0]->full_path, data->nodes[0]->full_cmd, data->envp);
    return (0);
}