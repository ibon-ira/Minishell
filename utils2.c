/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboiraza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 21:42:05 by iboiraza          #+#    #+#             */
/*   Updated: 2025/04/12 21:42:26 by iboiraza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isalpha(int c)
{
	if ((c < 'a' || c > 'z')
		&& (c < 'A' || c > 'Z'))
		return (0);
	return (1);
}

t_prompt	*ft_lstlast(t_prompt *lst)
{
	t_prompt	*last;
	t_prompt	*first;
	int			i;
	int			t;

	i = 0;
	first = lst;
	while (lst != NULL)
	{
		i++;
		lst = lst->next;
	}
	t = i - 1;
	while (t > 0)
	{
		t--;
		first = first->next;
	}
	last = first;
	return (last);
}

void	ft_lstadd_back(t_prompt **lst, t_prompt *new)
{
	t_prompt	*temporal;

	temporal = ft_lstlast(*lst);
	if (!temporal)
		*lst = new;
	else
		temporal->next = new;
}

int	ft_is_equal_simbol(char *argv)
{
	int	i;
	int	x;

	i = 0;
	x = 0;
	while (argv[i])
	{
		if (argv[i] == '=')
			x = 1;
		i++;
	}
	return (x);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (src[j])
		j++;
	if (dstsize == 0)
		return (j);
	while (src[i] && i < dstsize - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (j);
}
