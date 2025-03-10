/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iksaiz-m <iksaiz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 20:48:06 by iksaiz-m          #+#    #+#             */
/*   Updated: 2025/02/23 20:17:11 by iksaiz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exit(t_mini *data)
{
	int	i;
	
	i = 0;
	while (data->commands[i])
	{
		printf("%i: %s\n", i, data->commands[i]);
		i++;
	}
	if (data->splits <= 2)
	{
		if (ft_strncmp(data->commands[0], "exit", 4) == 0
			&& !data->commands[0][4])
		{
			printf("free %p\n", data->commands);
			free_split(data->commands);
			printf("\033[31mFin.\033[0m\n");
			free(data);
			exit(EXIT_SUCCESS);
		}
	}
	return (0);
}
