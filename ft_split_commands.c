/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_commands.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboiraza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 18:23:47 by iboiraza          #+#    #+#             */
/*   Updated: 2025/03/05 18:23:49 by iboiraza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char    ***ft_split_commands (int count_pipes, char **commands)
{
    int     j;
    int     i;
    char	***str;
	int		len;
	int		first;

    i = 0;
    len = 0;
    first = 0;
    j = 0;
    str = (char ***)malloc((count_pipes + 1) * sizeof(char *));
    while (commands[i])
		remove_quotes(commands[i++], 0);
	i = 0;
    if (count_pipes == 0)
        return (NULL); 
    while (j < count_pipes)
    {
	    len = ft_len_to_pipe(commands, count_pipes, i, first);
	    str[j] = ft_strdup2(commands, len, first);
        i = i + len + 1;
        first++;
        j++;
    }
    str[j] = NULL;
    return (str);
}