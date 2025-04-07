/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_pipes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboiraza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 08:37:47 by iboiraza          #+#    #+#             */
/*   Updated: 2025/04/07 14:31:59 by iboiraza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_start_index(char **commands, int first)
{
	int	j;
	int	counter;

	counter = 0;
	j = 0;
	if (first != 0)
	{
		while (commands[j])
		{
			if (strncmp(commands[j], "|", 1) == 0)
			{
				counter++;
				if (counter == first)
					break ;
			}
			j++;
		}
		j++;
	}
	return (j);
}

char	**copy_strings(char **commands, int start, int len, int k)
{
	char	**str;
	int		i;
	int		v;
	int		j;

	j = start;
	str = (char **)malloc((len + 1) * sizeof(char *));
	while (k <= len && commands[j])
	{
		i = 0;
		while (commands[j][i])
			i++;
		str[k] = (char *)malloc((i + 1) * sizeof(char));
		if (str[k])
		{
			v = -1;
			while (++v < i)
				str[k][v] = commands[j][v];
			str[k][v] = '\0';
		}
		k++;
		j++;
	}
	str[len] = NULL;
	return (str);
}

/*char **copy_strings(char **commands, int start, int len, int k)
{
    char **str;
    int i, v, j = start;

    str = (char **)malloc((len + 1) * sizeof(char *));
    if (!str)
        return NULL;
    while (k <= len && commands[j])
    {
        i = 0;
        while (commands[j][i++])
        str[k] = (char *)malloc((i + 1) * sizeof(char));
        if (str[k])
        {
            v = 0;
            while (v < i)
            {
                str[k][v] = commands[j][v];
                v++;
            }
            str[k][v] = '\0';
        }
        k++;
        j++;
    }
    str[len] = NULL;
    return str;
}*/

char	**ft_strdup2(char **commands, int len, int first)
{
	int	start_index;

	start_index = find_start_index(commands, first);
	return (copy_strings(commands, start_index, len, 0));
}

int	ft_len_to_pipe(char **commands, int flag, int start, int first)
{
	int	len;

	len = start;
	while (commands[len])
	{
		if (flag != 0 && ft_strncmp(commands[len], "|", 1) == 0)
			break ;
		len++;
	}
	if (first == 0)
		return (len - start);
	return (len - start);
}

int	ft_count_pipes(char **commands)
{
	int			i;
	int			count_pipes;

	i = 0;
	count_pipes = 0;
	while (commands[i])
	{
		if (ft_strncmp(commands[i], "|", 1) == 0)
			count_pipes++;
		i++;
	}
	return (count_pipes);
}
