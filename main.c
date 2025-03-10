/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iksaiz-m <iksaiz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 10:00:58 by iboiraza          #+#    #+#             */
/*   Updated: 2025/02/23 20:18:29 by iksaiz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_logo(void)
{
	printf(GREEN "\n==== Welcome to minishell by Ibon & Iker ====\n");
	printf("A minimal shell implementation | 42 School Project\n\n");
	printf(MAGENTA "███╗   ███╗██╗███╗   ██╗██╗██╗██╗██╗\n" \
			"████╗ ████║██║████╗  ██║██║██║██║██║\n" \
			"██╔████╔██║██║██╔██╗ ██║██║██║██║██║\n" \
			"██║╚██╔╝██║██║██║╚██╗██║██║██║██║██║\n" \
			"██║ ╚═╝ ██║██║██║ ╚████║██║██║██║██║\n" \
			"╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝╚═╝╚═╝╚═╝\n" \
			"                                      \n" RST);
}

char	*ft_print_user(void)
{
	char	*pwd;
	char	*username;
	char	*simbol;
	char	*userwithpwd;
	char	*prompt;
	char	*a;

	a = "->";
	pwd = getcwd(NULL, 0);
	username = getenv("USER");
	simbol = " \n> ";
	a = ft_strjoin(username, a);
	userwithpwd = ft_strjoin(a, pwd);
	prompt = ft_strjoin(userwithpwd, simbol);
	free(pwd);
	free(userwithpwd);
	// printf("\033[37;44m%s\033[0m", username);
	// printf("\033[32m %s\033[0m\n", pwd);
	return (prompt);
}

/*void	enter(t_mini *data)
{
	int		i;
	char	**str;
	int		len;
	int		first;
//	t_mini *current = *data;
	
	i = 0;
	len = 0;
	first = 0;
	while (data->commands[i])
		remove_quotes(data->commands[i++], 0);
	i = 0;
	while (data->ft_count_pipes >= 0)
	{
		printf("i calculado: %d\n", i);
		len = ft_len_to_pipe(data->commands, data->ft_count_pipes, i, first);
		printf("len calculado: %d\n", len);
		str = ft_strdup2(data->commands, len, first);
		if (init_shell(data->splits, str, data->envp))
			not_builtin_command(str);
		first++;
		data->ft_count_pipes--;
		i = i + len + 1;
	}
	free_split(data->commands);
	free(data);
}*/
/*
void	enter(t_mini *data)
{
	int		i;
	int		len;
	int		first;
	char	***triple;
	
	i = 0;
	len = 0;
	first = 0;
	triple = (char ***)malloc((data->ft_count_pipes + 2) * sizeof(char *));
	while (data->commands[i])
		remove_quotes(data->commands[i++], 0);
	i = 0;
	while (data->ft_count_pipes >= 0)
	{
		len = ft_len_to_pipe(data->commands, data->ft_count_pipes, i, first);
		triple[first] = ft_strdup2(data->commands, len, first);
		//str = ft_check_redirections(str, len);
		first++;
		data->ft_count_pipes--;
		i = i + len + 1;
	}
	ft_do_pipes(triple, data);
	free_split(data->commands);
	free(data);
}
*/
void	enter(t_mini *data)
{
	int		i;
//	char	**str;
	int		len;
	int		first;
	int		fd[2]; // Pipe
	int		prev_fd; // Para almacenar el fd[0] del pipe anterior
	pid_t	pid;
	char	***triple;
	
	i = 0;
	len = 0;
	first = 0;
	prev_fd = -1;
	triple = (char ***)malloc((data->ft_count_pipes + 2) * sizeof(char *));
	while (data->commands[i])
		remove_quotes(data->commands[i++], 0);
	i = 0;
	while (data->ft_count_pipes >= 0)
	{
		len = ft_len_to_pipe(data->commands, data->ft_count_pipes, i, first);
		triple[first] = ft_strdup2(data->commands, len, first);
		triple[first] = ft_check_redirections(triple[first], len);
	// Crear un pipe si hay más comandos
		if (data->ft_count_pipes > 0 && pipe(fd) == -1)
		{
			perror("pipe");
			exit(1);
		}
		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			exit(1);
		}
		if (pid == 0) // Proceso hijo
		{
			if (prev_fd != -1)
			{
				dup2(prev_fd, STDIN_FILENO); // Leer de la salida del comando anterior
				close(prev_fd);
			}
			if (data->ft_count_pipes > 0)
			{
				dup2(fd[1], STDOUT_FILENO); // Escribir en el pipe
				close(fd[0]); // Cerrar lectura en hijo
			}
			if (init_shell(data->splits, triple[first], data->envp))
				not_builtin_command(triple[first], data->envp);
			exit(0);
		}
		else // Proceso padre
		{
			wait(NULL); // Espera a que termine el hijo
			if (prev_fd != -1)
				close(prev_fd); // Cierra la lectura del pipe anterior
			if (data->ft_count_pipes > 0)
			{
				close(fd[1]); // Cierra la escritura del pipe actual
				prev_fd = fd[0]; // Guarda la lectura para el siguiente comando
			}
		}
		first++;
		data->ft_count_pipes--;
		i = i + len + 1;
	}
	free_split(data->commands);
	free(data);
}
void	ft_execute_commands(t_mini *data)
{
	if (!ft_check_redir_and_pipes(data))
	{
		data->nodes = ft_create_nodes(data);
		ft_simple_or_pipes(data);
	}
}

int	ft_check_input(char *line)
{
	if (!detectopenquotes(line))
		return (printf("syntax error: dquote\n"), 1);
	return (0);
}

void	enterdata(char *line, char **envp, t_mini **data)
{
	t_mini	*adddata;

	add_history(line);
	if (!ft_check_input(line))
	{
		adddata = malloc(sizeof (struct s_mini));
		set_bin_path(data);
		adddata->envp = envp;
		adddata->commands = ft_split(line, ' ');
//		adddata->commands = look_for_expansion(adddata->commands);
		adddata->ft_count_pipes = ft_count_pipes (adddata->commands);
		adddata->splits = ft_count_splits(line, ' ');
		*data = adddata;
		ft_execute_commands(*data);
	}
}

int	exist(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\0')
			return (1);
		i++;
	}
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_mini	*data;
	char	*prompt;

	data = NULL;
	print_logo();
//	ft_memset(&data, 0, sizeof(data));
	// signal(SIGUSR1, signal_received);
	// signal(SIGUSR2, signal_received);
	while (argc && argv)
	{
		prompt = ft_print_user();
		line = readline(prompt);
		free(prompt);
		if (exist(line) == 0)
			write(1, "\0", 1);
		if (exist(line))
			enterdata(line, envp, &data);
	}
	return (0);
}