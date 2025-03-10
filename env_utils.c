/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboiraza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 00:14:43 by iboiraza          #+#    #+#             */
/*   Updated: 2025/03/09 00:15:20 by iboiraza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*find_env_var(t_env **env_var, char *name)
{
	t_env	*current;

	current = *env_var;
	while (current)
	{
		if (!ft_strcmp(current->name, name))
			return (current);
		current = current->next;
	}
	return (NULL);
}

void	set_bin_path(t_mini *data)
{
	t_env	*bin_path;

	bin_path = find_env_var(&(data->envp), "PATH");
	if (bin_path)
		data->bin_path = ft_split(bin_path->content, ':');
	else
		data->bin_path = NULL;
}
