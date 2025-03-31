/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_bin_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboiraza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 19:50:32 by iboiraza          #+#    #+#             */
/*   Updated: 2025/03/30 19:50:51 by iboiraza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_env_var(t_prompt *env_var, char *name)
{
	while (env_var)
	{
		if (!ft_strncmp(env_var->envp, name, 5))
			return (env_var->envp);
		env_var = env_var->next;
	}
	return (NULL);
}

void	set_bin_path(t_mini *data)
{
	char	**bin_path;
	char	*path;

	path = find_env_var((data->env), "PATH=");
	if (path != NULL)
	{
		bin_path = ft_split(path, '=');
		path = bin_path[1];
		free(bin_path);
		if (bin_path)
			data->bin_path = ft_split(path, ':');
	}
	else
		data->bin_path = NULL;
}

