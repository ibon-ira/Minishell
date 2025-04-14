/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_parsed.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iksaiz-m <iksaiz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 22:29:18 by iboiraza          #+#    #+#             */
/*   Updated: 2025/04/13 18:51:05 by iksaiz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	getnums(int n)
{
	size_t	count;

	count = 0;
	if (n <= 0)
		count += 1;
	while (n)
	{
		n = n / 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	size_t	i;
	size_t	nums;
	char	*str;

	i = 0;
	if (n == 0)
		return (ft_strdup("0"));
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	nums = getnums(n);
	str = ft_calloc(nums + 1, (sizeof(char)));
	if (!str)
		return (NULL);
	if (n < 0)
	{
		str[0] = '-';
		n = (-1) * n;
		i++;
	}
	while (n)
	{
		str[--nums] = n % 10 + '0';
		n /= 10;
	}
	return (str);
}

char	*ft_get_var_value(char *line, int length, int *j)
{
	char	*var_value;
	int		x;
	int		i;

	x = 0;
	i = *j;
	var_value = ft_calloc(length + 1, (sizeof(char)));
	if (!var_value)
		return (NULL);
	while (length-- > 0)
	{
		i++;
		var_value[x] = line[i];
		x++;
	}
	return (var_value);
}

char	*ft_reasign(char *var_value, char *commands, int *i, int vname_len)
{
	char	*new_command;
	int		new_len;
	int		len;

	(*i)++;
	new_command = NULL;
	if (var_value == NULL)
		return (new_command);
	new_len = ft_strlen(commands) - vname_len + ft_strlen(var_value);
	new_command = ft_calloc(new_len + 1, (sizeof(char)));
	if (!new_command)
		return (NULL);
	ft_strlcpy(new_command, commands, *i);
	ft_strlcpy(new_command + (*i -1), var_value, new_len +1);
	len = ft_strlen(var_value);
	ft_strlcpy(new_command + (len + *i -1), commands + (*i -1) + vname_len,
		ft_strlen(commands) - (*i -1) - vname_len +1);
	*i = *i - 1;
	free(var_value);
	free(commands);
	return (new_command);
}

char	*vars(char *commands, t_prompt *env, int i, int x)
{
	int		s_quote;
	int		d_quote;
	char	*var_value;

	s_quote = 0;
	d_quote = 0;
	while (commands[i] != '\0')
	{
		if (ft_check_for_quotes(commands[i], &s_quote, &d_quote, &i) == 1)
			continue ;
		if (commands[i] == '$' && s_quote == 0)
			x = ft_check_dolar_length(commands, &i);
		if (x != 0 && commands[i])
		{
			var_value = ft_get_var_value(commands, x, &i);
			var_value = ft_checkvar_value(var_value, env, 0);
			commands = ft_reasign(var_value, commands, &i, (x + 1));
		}
		i++;
		x = 0;
	}
	return (commands);
}
