/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_parsed2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iksaiz-m <iksaiz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 13:03:53 by iboiraza          #+#    #+#             */
/*   Updated: 2025/04/24 20:43:46 by iksaiz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_checkvar_value(char *var_value, t_prompt *env, int i)
{
	char	*new_value;

	new_value = NULL;
	while (env)
	{
		if (ft_strncmp(var_value, env->envp, ft_strlen(var_value)) == 0
			&& env->envp[ft_strlen(var_value)] == '=')
		{
			i = ft_strlen(var_value) + 1;
			new_value = env_split(env->envp, i);
			free(var_value);
			return (new_value);
		}
		env = env->next;
	}
	if ((var_value[0] == '$' || var_value[0] == '0' || var_value[0] == '?')
		&& ft_strlen(var_value) == 1)
		new_value = ft_asign_rare_value(var_value);
	else
	{
		free(var_value);
		return (ft_strdup("\"\""));
	}
	return (new_value);
}

char	*ft_asign_rare_value(char *var_value)
{
	char	*new_value;
	int		pid;

	pid = 0;
	new_value = NULL;
	if (var_value[0] == '$')
	{
		pid = getpid();
		new_value = ft_itoa(pid);
	}
	else if (var_value[0] == '0')
		new_value = ft_strdup("Minishell");
	else if (var_value[0] == '?')
		new_value = ft_itoa(g_status);
	free(var_value);
	return (new_value);
}

int	ft_check_dolar_length(char *line, int *j)
{
	int	length;
	int	i;

	length = 0;
	i = *j;
	while (line[i] && line [i] != '\"' && line [i] != '\'')
	{
		i++;
		if (line[i] == '?' || line[i] == '$' || line[i] == '0')
		{
			if (length == 0)
			{
				length++;
				break ;
			}
			break ;
		}
		else if (!line[i] || line [i] == '\"' || line [i] == '\'')
			break ;
		else
			length++;
	}
	return (length);
}

int	ft_check_dolars(char *line)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (line[i])
	{
		if (line[i] == '$')
			return (1);
		i++;
	}
	return (0);
}

int	ft_check_for_quotes(char c, int *single_q, int *double_q, int *j)
{
	if (c == '\"' && *single_q == 0)
	{
		*double_q = !*double_q;
		(*j)++;
		return (1);
	}
	else if (c == '\'' && *double_q == 0)
	{
		*single_q = !*single_q;
		(*j)++;
		return (1);
	}
	return (0);
}
