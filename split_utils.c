/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboiraza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 12:55:02 by iboiraza          #+#    #+#             */
/*   Updated: 2025/04/13 12:57:03 by iboiraza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_split(char **argv)
{
	char	**pos;

	if (argv == NULL)
		return ;
	pos = argv;
	while (*pos != NULL)
		free(*(pos++));
	free(argv);
}

int	ft_count_splits(char const *s, char c)
{
	int	count;
	int	first_letter;

	count = 0;
	first_letter = 0;
	while (*s)
	{
		if (*s != c)
		{
			if (first_letter == 0)
			{
				count++;
				first_letter = 1;
			}
		}
		else
			first_letter = 0;
		s++;
	}
	return (count);
}

char	*env_split(char const *s, int start)
{
	int		i;
	int		len;
	char	*result;

	i = 0;
	len = start;
	while (s[start])
	{
		start++;
		i++;
	}
	result = ft_calloc(i + 1, (sizeof(char)));
	if (!result)
		return (NULL);
	i = 0;
	while (s[len])
	{
		result[i] = s[len];
		i++;
		len++;
	}
	return (result);
}
