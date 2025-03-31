/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iksaiz-m <iksaiz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 10:00:58 by iboiraza          #+#    #+#             */
/*   Updated: 2025/03/30 19:36:50 by iksaiz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_status = 0;

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
	simbol = " \n-> ";
	a = ft_strjoin(username, a);
	userwithpwd = ft_strjoin(username, pwd);
	prompt = ft_strjoin(userwithpwd, simbol);
	free(a);
	free(pwd);
	free(userwithpwd);
	return (prompt);
}

int	ft_check_input(char *line)
{
	if (!detectopenquotes(line))
		return (printf("syntax error: dquote\n"), 1);
	if (!check_pipe_redir(line, 0))
		return (1);
	if (line[0] == '<' || line[0] == '>' || (line[0] == '>' && line[1] == '>'))
		return (1);
	return (0);
}

void	enterdata(char *line, t_mini *data)
{
	add_history(line);
	if (!ft_check_input(line))
	{
		set_bin_path(data);
		data->commands = ft_split(line, ' ');
//		adddata->commands = look_for_expansion(adddata->commands);
		data->ft_count_pipes = ft_count_pipes(data->commands);
		data->splits = ft_count_splits(line, ' ');
		data->nbr_nodes = ft_count_pipes (data->commands) + 1;
		ft_exit (data, 0);
		if(!ft_prepare_nodes(data))
			ft_execute_commands(data);
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

void handle_sigint(int sig)
{
    (void)sig;
    printf("\n");          // Nueva línea
    rl_on_new_line();      // Actualiza la línea de readline
    rl_replace_line("", 0);// Borra el contenido actual
    rl_redisplay();        // Redibuja el prompt
}

void setup_signals(void)
{
    signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}

void	asignenvp(char **envp, t_prompt **data)
{
	t_prompt	*new;
	t_prompt	*last;
	int			i;

	new = NULL;
	last = NULL;
	i = 0;
	while (envp[i])
	{
		new = malloc(sizeof(t_prompt));
		if (!new)
			return ;
		new->envp = ft_strdup(envp[i]);
		new->next = NULL;
		if (last == NULL)
			*data = new;
		else
			last->next = new;
		last = new;
		i++;
	}
}

void	init_data(t_mini **data, char **envp)
{
	t_mini	*addata;

	addata = malloc(sizeof (struct s_mini));
	if (!addata)
		return ;
	addata->env = NULL; //initialize structure
	addata->execute_envp = envp;
	asignenvp(envp, &addata->env); //asign env to structure
	*data = addata; //asign data to estructure
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_mini	*data;
	char	*prompt;

	data = NULL;
	print_logo();
	setup_signals();
	// signal(SIGUSR1, signal_received);
	// signal(SIGUSR2, signal_received);
	init_data(&data, envp);
	while (argc && argv)
	{
		prompt = ft_print_user();
		line = readline(prompt);
		free(prompt);
		if (!line)  // Si readline devuelve NULL, usuario presionó Ctrl+D
			ft_exit (NULL, 1);
//        {
//            printf("exit\n");
//            exit(0);
//        }
		if (exist(line) == 0)
			write(1, "\0", 1);
		if (exist(line))
			enterdata(line, data);
		printf("$->%d\n", g_status);
	}
	return (0);
}
/*char c;
  char t;
  
  t = '\''; un character es comilla simple sin que te pete
  c = '\"'; un character es comillas doble sin que te pete */
