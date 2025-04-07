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
	char	**temp;
	char	*path;

	path = find_env_var((data->env), "PATH=");
	if (path != NULL)
	{
		temp = ft_split(path, '=');
		path = temp[1];
		if (temp)
			data->bin_path = ft_split(path, ':');
		free (temp[0]);
		free (temp[1]);
		free (temp);
	}
	else
		data->bin_path = NULL;
}
