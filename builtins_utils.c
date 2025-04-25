/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iksaiz-m <iksaiz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 17:44:06 by iksaiz-m          #+#    #+#             */
/*   Updated: 2025/04/24 20:11:28 by iksaiz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_lscopy(t_prompt **list, char *content)
{
	t_prompt	*new_list;
	t_prompt	*tmp;

	new_list = (t_prompt *)malloc(sizeof(t_prompt));
	new_list->envp = content;
	new_list->next = NULL;
	if (*list == NULL)
		*list = new_list;
	else
	{
		tmp = *list;
		while (tmp->next != NULL)
		{
			tmp = tmp->next;
		}
		tmp->next = new_list;
	}
}

void	ft_lstsort(t_prompt *lst, int swapped)
{
	t_prompt	*current;
	char		*temp;
	t_prompt	*last;

	last = NULL;
	if (lst == NULL)
		return ;
	while (swapped)
	{
		swapped = 0;
		current = lst;
		while (current->next != last)
		{
			if (strcmp(current->envp, current->next->envp) > 0)
			{
				temp = current->envp;
				current->envp = current->next->envp;
				current->next->envp = temp;
				swapped = 1;
			}
			current = current->next;
		}
		last = current;
	}
}

t_prompt	*dup_env(t_prompt *original_env)
{
	t_prompt	*env_dup;
	t_prompt	*temp;

	temp = original_env;
	env_dup = NULL;
	while (temp != NULL)
	{
		ft_lscopy(&env_dup, temp->envp);
		temp = temp->next;
	}
	return (env_dup);
}

int	check_env_name(char *argv, int x)
{
	int		i;
	char	**var_name;

	i = 0;
	if (argv[0] == '=')
		return (-1);
	var_name = ft_split(argv, '=');
	x = ft_is_equal_simbol(argv);
	if (var_name[0] == NULL)
		return (-1);
	while (var_name[0][i])
	{
		if (!ft_isalpha(var_name[0][i]))
		{
			printf("not valid in this context:\n");
			ft_free(var_name);
			return (-1);
		}
		i++;
	}
	if (x == 1 && !var_name[1])
		x = 2;
	ft_free(var_name);
	return (x);
}

void	asign_env_value(char *argv, t_prompt **data)
{
	t_prompt	*tmp;
	t_prompt	*var;
	char		**var_name;

	tmp = *data;
	var_name = ft_split(argv, '=');
	while (tmp)
	{
		if (ft_strncmp(var_name[0], tmp->envp, ft_strlen(var_name[0])) == 0
			&& tmp->envp[ft_strlen(var_name[0])] == '=')
		{
			free(tmp->envp);
			tmp->envp = ft_strdup(argv);
			ft_free(var_name);
			return ;
		}
		tmp = tmp->next;
	}
	var = malloc(sizeof(t_prompt));
	if (!var)
		return ;
	var->envp = ft_strdup(argv);
	var->next = NULL;
	ft_free(var_name);
	ft_lstadd_back(data, var);
}
