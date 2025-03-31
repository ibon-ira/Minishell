/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_pipes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboiraza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 08:37:47 by iboiraza          #+#    #+#             */
/*   Updated: 2025/02/27 08:40:05 by iboiraza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int find_start_index(char **commands, int first)
{
    int j = 0;
    int counter = 0;

    if (first != 0)
    {
        while (commands[j])
        {
            if (strncmp(commands[j], "|", 1) == 0)
            {
                counter++;
                if (counter == first)
                    break;
            }
            j++;
        }
        j++;
    }
    return j;
}

char **copy_strings(char **commands, int start, int len)
{
    char **str;
    int k = 0, i, v, j = start;

    str = (char **)malloc((len + 1) * sizeof(char *));
    if (!str)
        return NULL;

    while (k <= len && commands[j])
    {
        i = 0;
        while (commands[j][i])
            i++;
        
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
}

char **ft_strdup2(char **commands, int len, int first)
{
    int start_index;
	
	start_index = find_start_index(commands, first);
    return (copy_strings(commands, start_index, len));
}

int	ft_len_to_pipe (char **commands, int flag, int start, int  first)
{
	int	len;

	len = start;
	while (commands[len])
	{
		if (flag != 0 && ft_strncmp(commands[len], "|", 1) == 0)
			break;
		len++;
	}
	if (first == 0)
		return (len - start);
	return (len - start);
}

int	ft_count_pipes (char **commands)
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