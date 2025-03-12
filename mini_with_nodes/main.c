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

	pwd = getcwd(NULL, 0);
	username = getenv("USER");
	simbol = " \n> ";
	userwithpwd = ft_strjoin(username, pwd);
	prompt = ft_strjoin(userwithpwd, simbol);
	free(pwd);
	free(userwithpwd);
	// printf("\033[37;44m%s\033[0m", username);
	// printf("\033[32m %s\033[0m\n", pwd);
	return (prompt);
}

// void	enter(char *line, char **envp, t_mini **data)
// {
// 	char	**commands;
// 	int		splits;
// 	t_mini *adddata;

// 	// adddata = NULL;
// 	adddata = malloc(sizeof (struct s_mini));
// 	add_history(line);
// 	adddata->envp = envp;
// 	adddata->full_cmd = ft_split(line, ' ');
// 	commands = ft_split(line, ' ');
// 	adddata->splits = ft_count_splits(line, ' ');
// 	splits = ft_count_splits(line, ' ');
// 	init_shell(splits, commands, envp);
// 	*data = adddata;
// 	//init_shell(adddata->splits, adddata->full_cmd, adddata->envp);
// 	free_split(commands);
// 	//free_split(adddata->full_cmd);
// }
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
void	enter(t_mini *data)
{
	int		i;
	char	**str;
	int		len;
	int		first;
	int		fd[2]; // Pipe
	int		prev_fd; // Para almacenar el fd[0] del pipe anterior
	pid_t	pid;
	
	i = 0;
	len = 0;
	first = 0;
	prev_fd = -1;
	while (data->commands[i])
		remove_quotes(data->commands[i++], 0);
	i = 0;
	while (data->ft_count_pipes >= 0)
	{
		len = ft_len_to_pipe(data->commands, data->ft_count_pipes, i, first);
		str = ft_strdup2(data->commands, len, first);
		
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
			if (init_shell(data->splits, str, data->envp))
				not_builtin_command(str, data->envp);
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
//		set_bin_path(data);
		adddata->envp = envp;
		adddata->commands = ft_split(line, ' ');
//		adddata->commands = look_for_expansion(adddata->commands);
		adddata->ft_count_pipes = ft_count_pipes (adddata->commands);
		adddata->splits = ft_count_splits(line, ' ');
		*data = adddata;
		ft_prepare_nodes(*data);
//		ft_execute_commands(*data);
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
/*char c;
  char t;
  
  t = '\''; un character es comilla simple sin que te pete
  c = '\"'; un character es comillas doble sin que te pete */
