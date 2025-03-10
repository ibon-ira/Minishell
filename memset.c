/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memset.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboiraza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 09:10:00 by iboiraza          #+#    #+#             */
/*   Updated: 2025/03/07 09:13:55 by iboiraza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <stdio.h>
#include <string.h>

void	*ft_memset(void *b, int c, size_t len)
{
	size_t	i;
	char	*var;

	i = 0;
	var = b;
	while (i < len)
	{
		var[i] = c;
		i++;
	}
	return (b);
}

int main(void)
{
	char	str[20];

	printf("String: %s\n", str);
	printf("My function: %s\n", (char *)ft_memset(str, 60, 10));
	printf("Original function: %s\n", (char *)memset(str, 60, 10));
	return (0);
}
