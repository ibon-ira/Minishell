/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboiraza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 18:06:52 by iboiraza          #+#    #+#             */
/*   Updated: 2025/02/25 18:07:06 by iboiraza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void execute_pipeline(t_token *tokens)
{
    int pipe_fd[2];  // Para manejar el pipe
    int prev_fd = -1; // Guardará el extremo de lectura del pipe anterior
    pid_t pid;

    while (tokens)
    {
        if (tokens->next) // Si hay más comandos, crear pipe
        {
            if (pipe(pipe_fd) == -1)
            {
                perror("pipe");
                exit(1);
            }
        }

        pid = fork();
        if (pid == -1)
        {
            perror("fork");
            exit(1);
        }
        
        if (pid == 0) // Proceso hijo
        {
            if (prev_fd != -1) // Si hay un pipe antes, usarlo como entrada
            {
                dup2(prev_fd, STDIN_FILENO);
                close(prev_fd);
            }
            if (tokens->next) // Si hay un pipe después, redirigir salida
            {
                dup2(pipe_fd[1], STDOUT_FILENO);
                close(pipe_fd[1]);
            }

            close(pipe_fd[0]); // No se usa en el hijo
            execute_command(tokens); // Función que ejecuta el comando
            exit(0);
        }

        if (prev_fd != -1)
            close(prev_fd); // Cerrar el extremo de lectura anterior
        if (tokens->next)
            close(pipe_fd[1]); // Cerrar el extremo de escritura

        prev_fd = pipe_fd[0]; // Guardar extremo de lectura para el siguiente comando
        tokens = tokens->next;
    }

    while (wait(NULL) > 0); // Esperar a todos los hijos
}
