/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iksaiz-m <iksaiz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 19:00:22 by iksaiz-m          #+#    #+#             */
/*   Updated: 2025/01/25 18:50:47 by iksaiz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n <= 0)
		return (0);
	while (s1[i] == s2[i])
	{
		if (s1[i] == '\0' || i == n - 1)
			return ((unsigned char) s1[i] - (unsigned char) s2[i]);
		i++;
	}
	return ((unsigned char) s1[i] - (unsigned char) s2[i]);
}

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t				i;
	unsigned char		*a;
	const unsigned char	*b;

	i = 0;
	a = (unsigned char *) dst;
	b = (unsigned char *) src;
	if (!a && !b)
		return (dst);
	while (i < n)
	{
		a[i] = b[i];
		i++;
	}
	return (dst);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*joinstring;
	size_t	i;
	size_t	k;

	i = ft_strlen(s1);
	k = ft_strlen(s2);
	joinstring = (char *)malloc((i + k + 1) * sizeof(char));
	if (!joinstring)
		return (NULL);
	ft_memcpy(joinstring, s1, i);
	ft_memcpy(joinstring + i, s2, k);
	joinstring[i + k] = '\0';
	return (joinstring);
}

char	*ft_strdup(const char *s1)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (s1[i])
		i++;
	str = (char *)malloc (sizeof (char) * (i + 1));
	if (str)
	{
		while (j < i)
		{
			str[j] = s1[j];
			j++;
		}
		str[i] = '\0';
		return (str);
	}
	return (NULL);
}