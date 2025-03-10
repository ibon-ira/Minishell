/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iksaiz-m <iksaiz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 08:38:25 by iboiraza          #+#    #+#             */
/*   Updated: 2025/02/21 19:03:56 by iksaiz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <signal.h>
#define COLOR_AZUL "\033[34m"
#define GREEN "\033[32m"
#define MAGENTA "\033[1;35m"
#define RST "\033[0m"
/*
typedef struct s_prompt
{
	va_list *cmds;
	char **envp;
	pid_t pid;
}		t_prompt;

typedef struct s_node
{
	char	**full_cmd;
	char	*full_path;
	int		infile;
	int		outfile;
	int		all_ok;
	pid_t	n_pid;
}			t_node;

typedef struct s_mini
{	//t_env		*env;
	char **envp;
	char		**argenv;
	char		**bin_path;
	char		*input;
	char		**tokens;
	t_node		**nodes;
	int			nbr_nodes;
	int			signal;
}					t_mini;
*/
typedef struct s_env
{
	char			*name;
	char			*content;
	int				is_env;
	int				is_exp;
	int				is_pri;
	struct s_env	*next;
}					t_env;

typedef struct s_node
{
	char	**full_cmd;
	char	*full_path;
	int		infile;
	int		outfile;
	int		all_ok;
	pid_t	n_pid;
}			t_node;

typedef struct s_mini
{
	char	***total_cmd;
	char	**full_cmd;
	char	**commands;
	char	*full_path;
	int		infile;
	int		outfile;
	int		splits;
	int		ft_count_pipes;
	int		nbr_nodes;
	t_node	**nodes;
	char	**envp;
	char		**bin_path;
	char	*limit;
}	t_mini;

//utils.c
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_strlen(char *s);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
char	*ft_strjoin(char *s1, char *s2);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	*ft_memset(void *b, int c, size_t len);
int	ft_strcmp(char *s1, char *s2);

//split.c
char	**ft_split(char const *s, char c);
void	free_split(char **argv);
int		ft_count_splits(char const *s, char c);
char	**ft_splitquotes(char const *s, char c, char s_quote, char d_quote);
size_t	ft_num_word(char const *s, char c, size_t i, size_t num_word);

//builtins.c
void	echo(char **av, int flag);
void	pwd(int argc);
void	cd(int argc, char *av);
void	unset(char *argv);

//init_shell.c
int		export_action(int argc, char **argv);
int		fork_actions(int argc, char **argv, char **envp, int flag);
int		other_actions(int argc, char **argv);
int	init_shell(int argc, char **argv, char **envp);
//exit.c
int		ft_exit(t_mini *data);
//parse_imput.c
/* int		parsequotes(t_mini *data);*/
void	remove_quotes(char *imput, int i);
int		detectopenquotes(char *line);

//commands.c
void	not_builtin_command(char **data, char **env);
void	do_command(t_mini *data);
char	*ft_strdup(const char *s1);

//ft_count_pipes.c
int	ft_count_pipes (char **commands);
char	**ft_strdup2(char **commands, int	len, int first);
int	ft_len_to_pipe (char **commands, int flag, int start, int first);

//ft_split_commands.c
//char    ***ft_split_commands (int count_pipes, char **commands);

//ft_check_redirections.c
char	**ft_check_redirections (char **commands, int total);

//ft_do_pipes.c
void	ft_do_pipes(char ***triple, t_mini *data);

//ft_check_redir_and_pipes.c
int ft_check_redir_and_pipes(t_mini *data);
t_node  **ft_create_nodes(t_mini *data);
void    ft_simple_or_pipes(t_mini *data);

extern int g_status;

#endif
