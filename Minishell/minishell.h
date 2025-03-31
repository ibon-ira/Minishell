/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iksaiz-m <iksaiz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 08:38:25 by iboiraza          #+#    #+#             */
/*   Updated: 2025/03/30 18:57:25 by iksaiz-m         ###   ########.fr       */
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

#define TEMP_FILE ".\vtemp\th"

// typedef struct s_prompt
// {
// 	va_list *cmds;
// 	char **envp;
// 	pid_t pid;
// }		t_prompt;

typedef struct s_prompt
{
	char *envp;
	struct s_prompt *next;
}		t_prompt;

typedef struct s_node
{
	char	**full_cmd;
	char	*full_path;
	int		infile;
	int		outfile;
	int		is_set;
	pid_t	n_pid;
}	t_node;

typedef struct s_mini
{
	char ***total_cmd;
	char **full_cmd;
	char **commands;
	char *full_path;
	int infile;
	int outfile;
	int splits;
	int	ft_count_pipes;
	char **execute_envp;
	t_node	**nodes;
	int	nbr_nodes;
	char	**bin_path;
	t_prompt	*env;
}	t_mini;

//utils.c
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_strlen(char *s);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
char	*ft_strjoin(char *s1, char *s2);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void ft_lstsort(t_prompt *lst, int swapped);
void	ft_lstadd_back(t_prompt **lst, t_prompt *new);
t_prompt	*ft_lstlast(t_prompt *lst);
t_prompt	*ft_lstnew(t_prompt *content);
int	ft_isalpha(int c);
int	ft_is_equal_simbol(char *argv);


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
void	unset(char **argv, t_prompt **data);

//init_shell.c
int	fork_actions(int argc, char **argv, int flag, t_prompt *env);
int		other_actions(int argc, char **argv, t_mini **data);
int	execute_builtin(char **argv, t_prompt *env, t_mini **data);
//exit.c
int		ft_exit(t_mini *data, int flag);
//parse_imput.c
/* int		parsequotes(t_mini *data);*/
void	remove_quotes(char *imput, int i);
int		detectopenquotes(char *line);
int	check_wrong_pipes(char **commands);
int	check_wrong_redir(char **commands);

//commands.c
void	not_builtin_command(char **data, char **env);
void	do_command(t_mini *data);

//ft_count_pipes.c
int	ft_count_pipes (char **commands);
char	**ft_strdup2(char **commands, int	len, int first);
int	ft_len_to_pipe (char **commands, int flag, int start, int first);

int	ft_prepare_nodes(t_mini *data);
void	ft_execute_commands(t_mini *data);
char	*set_full_path(t_node *node, char **bin_path);
char	**set_full_cmd(char **commands, int i, int cmd);
int	set_infile_outfile(t_node *node, char **commands, int outfile, int infile);
int	get_here_doc(char *str[2], char *aux[2]);
void ft_clean(t_mini *data);
int	check_pipe_redir(char *s, int i);
char	*ft_strdup(const char *s1);
void	set_bin_path(t_mini *data);
int	is_builtin(char *str);

extern int	g_status;

#endif
