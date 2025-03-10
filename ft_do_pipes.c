/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_do_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboiraza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 11:53:06 by iboiraza          #+#    #+#             */
/*   Updated: 2025/03/06 11:55:00 by iboiraza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
void	ft_do_pipes(char *data, char **commands)
{
    int		fd[2]; // Pipe
	int		prev_fd; // Para almacenar el fd[0] del pipe anterior
	pid_t	pid;


}
*/

void	ft_do_pipes(char ***triple, t_mini *data)
{
	int		fd[2];     // Pipe actual
	int		prev_fd;   // Para el pipe anterior
	pid_t	pid;
	int		i;

	i = 0;
	prev_fd = -1; // No hay pipe previo al inicio

	while (triple[i] != NULL) // Iteramos sobre cada comando en triple
	{
		// Si no es el último comando, creamos un pipe
		if (triple[i + 1] != NULL)
		{
			if (pipe(fd) == -1)
			{
				perror("pipe");
				exit(EXIT_FAILURE);
			}
		}

		// Crear un proceso hijo
		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}

		if (pid == 0) // Proceso hijo
		{
			// Si hay un pipe previo, redirigir stdin a su extremo de lectura
			if (prev_fd != -1)
			{
				dup2(prev_fd, STDIN_FILENO);
				close(prev_fd);
			}

			// Si no es el último comando, redirigir stdout al pipe actual
			if (triple[i + 1] != NULL)
			{
				dup2(fd[1], STDOUT_FILENO);
				close(fd[0]); // Cerrar lectura en hijo
			}

			// Ejecutar el comando (init_shell lo hace en enter())
			if (init_shell(data->splits, triple[i], data->envp))
				not_builtin_command(triple[i], data->envp);

			exit(EXIT_SUCCESS); // Salir tras ejecutar el comando
		}
		else // Proceso padre
		{
			waitpid(pid, NULL, 0); // Espera a que el hijo termine

			// Cerrar el pipe previo si existía
			if (prev_fd != -1)
				close(prev_fd);

			// Si no es el último comando, actualizar prev_fd para el próximo
			if (triple[i + 1] != NULL)
			{
				close(fd[1]);  // Cerrar la escritura del pipe en el padre
				prev_fd = fd[0]; // Guardar el extremo de lectura para el siguiente comando
			}
			else
				prev_fd = -1; // Último comando, resetear
		}

		i++; // Siguiente comando
	}
}
